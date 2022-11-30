#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <math.h>
#include <string.h>

pthread_barrier_t mybarrier;
int size = 480;
float xmin = -2.0;
float xmax = 0.47;
float ymin = -1.12;
float ymax = 1.12;
int maxIterations = 1000;
int numProcesses = 4;

struct thread_data{
  int start_i;
  int end_i;
  int start_j;
  int end_j;
  int **membershipint;
  int **membershipCount;
  int maxCount;
  struct ppm_pixel **paletteData;
};

void* determine_membership(void *userdata){
  struct thread_data *data = (struct thread_data *)userdata;
  printf("Thread %ld)sub-image block: cols (%d,%d) to rows(%d,%d)\n",pthread_self(),data->start_i,data->end_i,data->start_j,data->end_j);
  for(int i = data->start_i ; i < data->end_i ; i++){
    for(int j = data->start_j ; j < data->end_j ; j++){
      float xfrac = j / (float)size;
      float yfrac = i / (float)size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);

      float x = 0;
      float y = 0;
      int iter = 0;
      while (iter < maxIterations && x*x + y*y < 2*2){
        float xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter++;
      }
      if (iter < maxIterations){ // escaped
        data->membershipint[i][j] = 0;
      }
      else{
        data->membershipint[i][j] = 1;
      }
    }
  }
  return (void*)NULL;
}

void* compute_counts(void *userdata){
  struct thread_data *data = (struct thread_data *)userdata;
  for(int i = data->start_i ; i < data->end_i ; i++){
    for(int j = data->start_j ; j < data->end_j ; j++){
      data->membershipCount[i][j]=0;
      if(data->membershipint[i][j])continue;

      float xfrac = j / (float)size;
      float yfrac = i / (float)size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);

      float x = 0;
      float y = 0;
      int count = 0;
      while (x*x + y*y < 2*2){
        float xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        
        float yrow = round(size * (y - ymin)/(ymax - ymin));
        float xcol = round(size * (x - xmin)/(xmax - xmin));

        if (yrow < 0 || yrow >= size) continue;
        if (xcol < 0 || xcol >= size) continue;
        data->membershipCount[i][j]++;
        if(data->membershipCount[i][j]>data->maxCount) data->maxCount=data->membershipCount[i][j];
      }
    }
  }
  return (void*)NULL;
}


void* compute_color(void *userdata){
  struct thread_data *data = (struct thread_data *)userdata;
  float gamma = 0.681;
  float factor = 1.0/gamma;
  struct ppm_pixel *temp = malloc(sizeof(struct ppm_pixel));
  for(int i = data->start_i ; i < data->end_i ; i++){
    for(int j = data->start_j ; j < data->end_j ; j++){
      float value = 0.0;

      if(data->membershipCount[i][j]>0){
        value = log(data->membershipCount[i][j]) / log(data->maxCount);
        value = pow(value, factor);
      }
      temp->red = value*255;
      temp->green = value*255;
      temp->blue = value*255;
      data->paletteData[i][j] = *temp;
    }
  }
  free(temp);
  printf("Thread %ld)finished\n",pthread_self());
  return (void*)NULL;
}

void* start(void* data){
  determine_membership(data);
  compute_counts(data);
  pthread_barrier_wait(&mybarrier);
  compute_color(data);
  return (void*)NULL;
}


int main(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  int** membership;
  membership = malloc (sizeof(int*)*size);
  for(int i = 0 ; i < size ; i++){
    membership[i] = malloc(sizeof(int)*size);
  }

  int** counts;
  counts = malloc (sizeof(int*)*size);
  for(int i = 0 ; i < size ; i++){
    counts[i] = malloc(sizeof(int)*size);
  }

  struct ppm_pixel** palette;
  palette = malloc (sizeof(struct ppm_pixel*)*size);
  for(int i = 0 ; i < size ; i++){
    palette[i] = malloc(sizeof(struct ppm_pixel)*size);
  }


  double timer;
  struct timeval tstart, tend;

  srand(time(0));
  //generate colors


  pthread_barrier_init(&mybarrier,NULL,4);

  pthread_t threads[4];
  struct thread_data data[4];

  gettimeofday(&tstart, NULL);

  for(int i=0;i<2;i++){
    for(int j=0;j<2;j++){
      data[2*i+j].membershipint = membership;
      data[2*i+j].paletteData = palette;
      data[2*i+j].membershipCount = counts;
      data[2*i+j].start_i = i*size/2;
      data[2*i+j].end_i = (i+1)*size/2;
      data[2*i+j].start_j = j*size/2;
      data[2*i+j].end_j = (j+1)*size/2;
      data[2*i+j].maxCount = 0;
      pthread_create(&threads[2*i+j],NULL,start,(void*)&data[2*i+j]);
    }
  }

  for(int i=0;i<4;i++){
    pthread_join(threads[i],NULL);
  }

  
  gettimeofday(&tend, NULL);

  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%d x %d)in %g seconds\n",size,size, timer);

  char size_str[64];
  sprintf(size_str,"%d",size);
  char time_str[64];
  sprintf(time_str,"%ld",time(0));
  char filename[64] ="mandelbrot-";
  strcat(filename,size_str);
  strcat(filename,"-");
  strcat(filename,time_str);
  strcat(filename,".ppm");
  write_ppm_2d(filename,palette,size,size);

  for(int i =0;i<size;i++){
    free(membership[i]);
  }
  free(membership);
  for(int i =0;i<size;i++){
    free(counts[i]);
  }
  free(counts);
  for(int i =0;i<size;i++){
    free(palette[i]);
  }
  free(palette);
}
