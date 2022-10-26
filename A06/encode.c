#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

void cleanup(struct ppm_pixel** img, int width, int height) {
  for (int i = 0; i < height; i++) {
    free(img[i]);
  }
  free(img);
}
int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  int w, h=0;
  const char* filename = argv[1];
  struct ppm_pixel** pixels=read_ppm_2d(filename,&w,&h);
  int max = w*h*3/8;
  printf("Reading %s with width %d and height %d\n",filename,w,h);
  printf("Max number of characters in the image: %d\n",max-1);
  printf("Enter a phrase: \n");
  char input[1000];
  scanf("%[^\n]%*c",input);
  unsigned char mask;
  int index =0;
  unsigned char newChar;
  for(int i =0;i<h;i++){
    for(int j =0;j<w;j++){
      mask = pixels[i][j].red & 1;
      if(index>(8*strlen(input))){newChar = 0;}
      else{
        newChar = (input[index/8]>>(7-index%8))& 1;
      }
      index++;
      unsigned char newRed = (pixels[i][j].red ^ mask) |newChar;
      mask = pixels[i][j].green & 1;
      if(index>(8*strlen(input))){newChar = 0;}
      else{
        newChar = (input[index/8]>>(7-index%8))& 1;
      }
      index ++;
      unsigned char newGreen = (pixels[i][j].green ^ mask) |newChar;    
      mask = pixels[i][j].blue & 1;
      if(index>(8*strlen(input))){newChar = 0;}
      else{
        newChar = (input[index/8]>>(7-index%8))& 1;
      }
      index ++;
      unsigned char newBlue = (pixels[i][j].blue ^ mask)|newChar; 
      pixels[i][j].red = newRed;
      pixels[i][j].green = newGreen;
      pixels[i][j].blue = newBlue;
    }
  }
  char newName[64]="";
  for(int i=0;filename[i]!='.';i++){
    newName[i]=filename[i];
  }
  strcat(newName,"-encoded.ppm");
  write_ppm_2d(newName, pixels, w, h);
  cleanup(pixels, w, h);
  return 0;
}

