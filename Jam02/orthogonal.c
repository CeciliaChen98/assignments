#include <stdio.h>



int main() {
  float x;
  float y;
  float z;
  printf("Please enter the values for the first vector: ");
  scanf("%f %f %f",&x,&y,&z);
  float a,b,c;
  printf("Please enter the values for the second vector: ");
  scanf("%f %f %f",&a,&b,&c);
  float dotProduct= x*a+y*b+z*c;
  float epsilon = 0.00001;
  printf("The dot product is %.2f\n",dotProduct);
  if(dotProduct>-epsilon&&dotProduct<epsilon){
    printf("The vectors are perpendicular\n");
  }
  else{
    printf("The vectors are not perpendicular\n");
  }
  return 0;
}
