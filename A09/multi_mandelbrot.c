#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <string.h>

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

  double timer;
  struct timeval tstart, tend;

  srand(time(0));
  //generate colors
  struct ppm_pixel black = {0,0,0};

  struct ppm_pixel *colors=malloc(sizeof(struct ppm_pixel)*maxIterations);
  struct ppm_pixel *temp = malloc(sizeof(struct ppm_pixel));
  for(int i = 0 ; i < maxIterations ; i++){
    temp->red = rand() % 255;
    temp->green = rand() % 255;
    temp->blue = rand() % 255;
    colors[i]= *temp;
  }
  free(temp);
  
  int shmid;
  shmid =  shmget(IPC_PRIVATE, sizeof(struct ppm_pixel)*size*size, 0644|IPC_CREAT);
  struct ppm_pixel *palette = shmat(shmid,NULL,0);

  gettimeofday(&tstart, NULL);

  for(int a=0;a<2;a++){
    for(int b=0;b<2;b++){
      int pid =fork();
      if(pid == 0){
        printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n",getpid(),a*size/2,(a+1)*size/2,b*size/2,(b+1)*size/2);
        for(int i = a*size/2 ; i < ((a+1)*size/2); i++){
          for(int j = b*size/2 ; j < ((b+1)*size/2) ; j++){
            float xfrac = j / (float)size;;
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
              palette[i*size+j] = colors[iter];
            }
            else{
              palette[i*size+j] = black;
            }
          }
        }
        exit(0);
      }
      else{
        printf("Launched child process: %d\n", pid);
      }
    }
  }
  for (int i = 0; i < numProcesses; i++) {
    int status;
    int pid = wait(&status);
    printf("Child process complete: %d\n", pid);
  }

  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%d x %d)in %g seconds\n",size,size, timer);

  char size_str[64];
  sprintf(size_str,"%d",size);
  char time_str[64];
  sprintf(time_str,"%ld",time(0));
  char filename[64] ="multi-mandelbrot-";
  strcat(filename,size_str);
  strcat(filename,"-");
  strcat(filename,time_str);
  strcat(filename,".ppm");
  write_ppm(filename,palette,size,size);

  free(colors);
}
