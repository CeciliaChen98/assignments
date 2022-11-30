#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <string.h>

struct thread_data{
  int size;
  float xmin;
  float xmax;
  float ymin;
  float ymax;
  int maxIterations;
  int start_i;
  int end_i;
  int start_j;
  int end_j;
  struct ppm_pixel **paletteData;
  struct ppm_pixel *colorsData;
};

void* generate_palette(void *userdata){
  struct thread_data *data = (struct thread_data *)userdata;
  printf("Thread %ld)sub-image block: cols (%d,%d) to rows(%d,%d)\n",pthread_self(),data->start_i,data->end_i,data->start_j,data->end_j);
  struct ppm_pixel black = {0,0,0};
  for(int i = data->start_i ; i < data->end_i ; i++){
    for(int j = data->start_j ; j < data->end_j ; j++){
      float xfrac = j / (float)data->size;
      float yfrac = i / (float)data->size;
      float x0 = data->xmin + xfrac * (data->xmax - data->xmin);
      float y0 = data->ymin + yfrac * (data->ymax - data->ymin);

      float x = 0;
      float y = 0;
      int iter = 0;
      while (iter < data->maxIterations && x*x + y*y < 2*2){
        float xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter++;
      }
      if (iter < data->maxIterations){ // escaped
        data->paletteData[i][j] = data->colorsData[iter];
      }
      else{
        data->paletteData[i][j] = black;
      }
    }
  }
  printf("Thread %ld)finished\n",pthread_self());
  return (void*)NULL;
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;
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

  struct ppm_pixel** palette;
  palette = malloc (sizeof(struct ppm_pixel*)*size);
  for(int i = 0 ; i < size ; i++){
    palette[i] = malloc(sizeof(struct ppm_pixel)*size);
  }

  double timer;
  struct timeval tstart, tend;

  srand(time(0));
  //generate colors

  struct ppm_pixel *colors=malloc(sizeof(struct ppm_pixel)*maxIterations);
  struct ppm_pixel *temp = malloc(sizeof(struct ppm_pixel));
  for(int i = 0 ; i < maxIterations ; i++){
    temp->red = rand() % 255;
    temp->green = rand() % 255;
    temp->blue = rand() % 255;
    colors[i]= *temp;
  }
  free(temp);

  pthread_t threads[4];
  struct thread_data data[4];

  gettimeofday(&tstart, NULL);

  for(int i=0;i<2;i++){
    for(int j=0;j<2;j++){
      data[2*i+j].paletteData = palette;
      data[2*i+j].size = size;
      data[2*i+j].xmax = xmax;
      data[2*i+j].xmin = xmin;
      data[2*i+j].ymax = ymax;
      data[2*i+j].ymin = ymin;
      data[2*i+j].maxIterations = maxIterations;
      data[2*i+j].colorsData = colors;
      data[2*i+j].start_i = i*size/2;
      data[2*i+j].end_i = (i+1)*size/2;
      data[2*i+j].start_j = j*size/2;
      data[2*i+j].end_j = (j+1)*size/2;

      pthread_create(&threads[2*i+j],NULL,generate_palette,(void*)&data[2*i+j]);
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
    free(palette[i]);
  }
  free(colors);
  free(palette);
}
