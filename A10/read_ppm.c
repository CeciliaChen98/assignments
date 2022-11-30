#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {

  return NULL;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {

   FILE *file;
  file = fopen(filename, "r");  
  if (file == NULL) {
    printf("Error: unable to open file %s\n", filename);
    fclose(file);
  }
  char isImage[4];
  fgets(isImage,4,file);
  if(isImage[0]!='P'||isImage[1]!='6'){
    printf("Error: isn't image data\n");
    fclose(file);
    return NULL;
  }

  char c;
  c = fgetc(file);
  if(c == '#') {
    do{
      c=fgetc(file);
    }while(c!= '\n');
    c=fgetc(file);
  }
  ungetc(c,file);

  int maximum=0;
  fscanf(file,"%d %d\n%d",w,h,&maximum);


  struct ppm_pixel** array;
  array = malloc (sizeof(struct ppm_pixel*)**h);
  if(!array){
    printf("Unable to allocate memory\n");
    return NULL;
  }
  for(int i =0;i<*h;i++){
    array[i] = malloc(sizeof(struct ppm_pixel)**w);
    if(!array[i]){
      printf("Unable to allocate memory\n");
      return NULL;
    }
  }
  while(fgetc(file)!='\n'){}
  struct ppm_pixel *temp = malloc(sizeof(struct ppm_pixel));
  for(int i =0;i<*h;i++){
    for(int j = 0;j<*w;j++){
      temp->red = fgetc(file);
      temp->green = fgetc(file);
      temp->blue = fgetc(file);
      array[i][j]= *temp;
    }
  }
  free(temp);
  fclose(file);
  return array;
}
