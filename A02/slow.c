#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int pause;
  char str[32];
  printf("Pause length: " );
  scanf("%d",&pause);
  printf("Text: ");
  scanf("%s",str);

  int n =strlen(str);
  int size = (pause+1)*n +1;


  char* result;
  result= malloc(size);

  int index = 0;
  for(int i = 0;i<n;i++){
    result[index]=str[i];
    index++;
    for(int j=0;j<pause;j++){
      result[index]='.' ;
      index++;
    }
  }
  result[index]='\0';
  printf("%s\n",result);
  free(result);
  return 0;
}
