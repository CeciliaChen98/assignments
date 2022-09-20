#include <stdio.h>

int main() {
  int matrix[4][4];
  for(int i=0;i<4;i++){
    for(int j =0;j<4;j++){
      scanf(" %d",&matrix[i][j]);
    }
  }
  int max=0;
  int tempI;
  int tempJ;
  for(int i = 0;i<4;i++){
    for(int j =0;j<4;j++){
      int value = matrix[i][j];
      if(value>max){
        max = value;
      }
      tempI = i+1;
      while(matrix[tempI][j]==0&&tempI<3){
        tempI++;
      }
      if(value==matrix[tempI][j]&&2*value>max){
        max=2*value;
      }
      tempJ = j+1;
      while(matrix[i][tempJ]==0&&tempJ<3){
        tempJ++;
      }
      if(value==matrix[i][tempJ]&&2*value>max){
        max=2*value;
      }
    }
  }
  printf("The largest value is %d\n",max);
  return 0;
}
