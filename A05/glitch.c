#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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
    printf("usage: glitch <file.ppm>\n");
    return 0;
  }
  srand(time(0));
  int w= 0;
  int h= 0;
  const char* filename = argv[1];
  struct ppm_pixel** pixels=read_ppm_2d(filename,&w,&h);
  for(int i=0;i<h;i++){
    for(int j =0;j<w;j++){
      unsigned char newRed = pixels[i][j].red <<(rand() % 2);
      unsigned char newGreen = pixels[i][j].green <<(rand() % 2);
      unsigned char newBlue = pixels[i][j].blue <<(rand() % 2);      
      pixels[i][j].red = newRed;
      pixels[i][j].green = newGreen;
      pixels[i][j].blue = newBlue;
    }
  }

  char newName[64]="";
  for(int i=0;filename[i]!='.';i++){
    newName[i]=filename[i];
  }
  strcat(newName,"-glitch.ppm");
  write_ppm_2d(newName, pixels, w, h);
  cleanup(pixels, w, h);



  // todo: your code here

  return 0;
}
