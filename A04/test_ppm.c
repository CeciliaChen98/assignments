#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "read_ppm.c"

int main() {
  // load feep-raw and print out the grid of pixels
  int w= 0;
  int h= 0;
  const char* filename = "feep-raw.ppm";
  struct ppm_pixel** array=read_ppm_2d(filename,&w,&h);

  printf("Testing file %s: %d %d\n",filename,w,h);
  for(int i =0;i<h;i++){
    for(int j =0;j<w;j++){
      printf("(%d,%d,%d) ",array[i][j].red,array[i][j].green,array[i][j].blue);
    }
    printf("\n");
  }

  for(int i=0;i<h;i++){
    free(array[i]);
  }

  free(array);
  return 0;
}

