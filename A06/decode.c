#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

void cleanup(struct ppm_pixel** img, int width, int height) {
  for (int i = 0; i < height; i++) {
    free(img[i]);
  }
  free(img);
}


int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: denewChar <file.ppm>\n");
    return 0;
  }
  int w, h;
  const char* filename = argv[1];
  struct ppm_pixel** pixels=read_ppm_2d(filename,&w,&h);
  int max = w*h*3/8;
  printf("Reading %s with width %d and height %d\n",filename,w,h);
  printf("Max number of characters in the image: %d\n",max);
  char* result = malloc(sizeof(char)*max*8);
  unsigned char temp;
  unsigned char mask=0b1;
  unsigned char newChar;
  int index=0;
  for(int i=0;i<h;i++){
    for(int j =0;j<w;j++){
      newChar= pixels[i][j].red & mask;
      index++;
      if(index%8==0){
        temp = (temp<<1)|newChar;
        int num = index/8-1;
        result[num]=temp;
        if(temp=='\0'){
          break;
        }
        temp = 0;
      }else{
        temp = (temp<<1)|newChar;
      }
      newChar = pixels[i][j].green & mask;
      result[index]=newChar;
      index++;
      if(index%8==0){
        temp = (temp<<1)|newChar;
        int num = index/8-1;
        result[num]=temp;
        if(temp=='\0'){
          break;
        }
        temp = 0;
      }else{
        temp = (temp<<1)|newChar;
      }      
      newChar = pixels[i][j].blue & mask;
      result[index]=newChar;      
      index++;
      if(index%8==0){
        temp = (temp<<1)|newChar;        
        int num = index/8-1;
        result[num]=temp;
        if(temp=='\0'){
          break;
        }
        temp = 0;
      }else{
        temp = (temp<<1)|newChar;
      }
    }
  }
  printf("%s\n",result);
  free(result);
  cleanup(pixels,w,h);
  return 0;
}

