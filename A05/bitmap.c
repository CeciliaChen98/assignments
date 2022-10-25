#include <stdio.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);

  for(int i =63;i>=0;i--){
    unsigned long mask =0x1ul << i;
    unsigned long result =(mask&img);
    if(result==0){
      printf("  ");
    }else{
      printf("@ ");
    }
    if(i%8==0){
      printf("\n");
    }
  }

  return 0;
}
