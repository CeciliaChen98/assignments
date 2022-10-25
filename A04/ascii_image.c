#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"


char pixelToChar(struct ppm_pixel pixel){
  float i = (pixel.blue+pixel.red+pixel.green)/3.0;
  if(i<=25){
    return '@';
  }
  else if(i<=50){
    return '#';
  }
  else if(i<=75){
    return '%';
  }
  else if(i<=100){
    return '*';
  }
  else if(i<=125){
    return 'o';
  }
  else if(i<=150){
    return ';';
  }
  else if(i<=175){
    return ':';
  }
  else if(i<=200){
    return ',';
  }
  else if(i<=225){
    return '.';
  }
  else{
    return ' ';
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: ascii_image <file.ppm>\n");
    return 0;
  }
  int w= 0;
  int h= 0;
  const char* filename = argv[1];
  struct ppm_pixel** array=read_ppm_2d(filename,&w,&h);

  printf("Reading %s with width %d and height %d\n",filename,w,h);
  char temp;
  for(int i =0;i<h;i++){
    for(int j =0;j<w;j++){
      temp=pixelToChar(array[i][j]);
      printf("%c",temp);
    }
    printf("\n");
  }
  for(int i=0;i<h;i++){
    free(array[i]);
  }

  free(array);
  return 0;
}

