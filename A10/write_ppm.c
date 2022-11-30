#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {
    FILE *file;
    file = fopen(filename,"wr");
    fprintf(file,"P6\n# created by Yue\n%d %d\n255\n",w,h);
    for(int i=0;i<h*w;i++){
        unsigned char pixel[3]={pxs[i].red,pxs[i].green,pxs[i].blue};
        fwrite(pixel,sizeof(unsigned char),sizeof(pixel),file);
    }
    fclose(file);
}

void write_ppm_2d(const char* filename, struct ppm_pixel** pxs, int w, int h) {
    FILE *file;
    file = fopen(filename,"wr");
    fprintf(file,"P6\n# created by Yue\n%d %d\n255\n",w,h);
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            unsigned char pixel[3]={pxs[i][j].red,pxs[i][j].green,pxs[i][j].blue};
            fwrite(pixel,sizeof(unsigned char),sizeof(pixel),file);
        }
    }
    fclose(file);
}
