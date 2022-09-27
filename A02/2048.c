#include <stdio.h>

int main() {

  //initialize the board
  int matrix[4][4];
  for(int i=0;i<4;i++){
    for(int j =0;j<4;j++){
      scanf(" %d",&matrix[i][j]);
    }
  }

  //find the largest value after any possible shifting
  int max=0;
  int tempI;
  int tempJ;
  int hasShift=0;
  for(int i = 0;i<4;i++){
    for(int j =0;j<4;j++){
      int value = matrix[i][j];

      //shifting up or down
      tempI = i+1;
      while(tempI<3){
        if(matrix[tempI][j]==0){
          tempI++;
        }else{
          break;
        }
      }
      if(value==matrix[tempI][j]){
        hasShift=1;
        if(2*value>max){
          max=2*value;
        }
      }

      //shifting left or right
      tempJ = j+1;
       while(tempJ<3){
        if(matrix[i][tempJ]==0){
          tempJ++;
        }else{
          break;
        }
      }
      if(value==matrix[i][tempJ]){
        hasShift=1;
        if(2*value>max){
          max=2*value;
        }
      }

      //if there is no combo on the board, it ouputs the largest value on the board
      if(!hasShift){
        for(int i = 0;i<4;i++){
          for(int j =0;j<4;j++){
            int value = matrix[i][j];
            if(value > max){
              max = value;
            }
          }
        }
      }
    }
  }
  printf("The largest value is %d\n",max);
  return 0;
}
