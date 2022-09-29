#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

int findBomb(char** matrix,int a,int b,int m,int n){
  int tempA;
  int tempB;
  int amount = 0;
  for(tempA=a-1;tempA<=a+1;tempA++){
    for(tempB=b-1;tempB<=b+1;tempB++){
      if(tempB>=0&&tempB<n&&tempA<m&&tempA>=0){
        if(matrix[tempA][tempB]=='X'){
          amount++;
        }
      }
    }
  }
  return amount;
}


int main(int argc, char** argv) {
  srand(time(0));
  if (argc != 4) {
    printf("usage: %s m n p\n", argv[0]);
  }
  int m = (int)atoi(argv[1]);
  int n = (int)atoi(argv[2]);
  float p = atof(argv[3]);

  //create the 2-D dynamic array
  char ** matrix;
  matrix = malloc(sizeof(char*)*m);
  for(int i =0;i<m;i++){
    matrix[i] = malloc(sizeof(char)*n);
  }

  //set the content in the matrix
  int x;
  for(int i =0;i<m;i++){
    for(int j =0;j<n;j++){
      x=rand()%10+1;
      if(x>(p*10)){
        matrix[i][j]='.';
      }
      else{
        matrix[i][j]='X';
      }
      printf("%c ",matrix[i][j]);
    }
    printf("\n");
  }
  int tempAmount;
  for(int i =0;i<m;i++){
    for(int j =0;j<n;j++){
      if(matrix[i][j]=='.'){
        tempAmount = findBomb(matrix,i,j,m,n);
        printf("%d ",tempAmount);
      }
      else{
        printf("%c ",matrix[i][j]);
      }
    }
    printf("\n");
  }



  //free the array
  for(int i =0;i<m;i++){
    free(matrix[i]);
  }
  free(matrix);
  return 0;
}
