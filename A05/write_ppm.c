#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement one

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
    FILE *file;
    file = fopen(filename,"wr");
    fprintf(file,"P6\n# created by Yue\n%d %d\n255\n",w,h);
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            unsigned char pixel[3]={pixels[i][j].red,pixels[i][j].green,pixels[i][j].blue};
            fwrite(pixel,sizeof(unsigned char),sizeof(pixel),file);
        }
    }
    fclose(file);
}
