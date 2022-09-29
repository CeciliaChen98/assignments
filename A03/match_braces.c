#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct charInfo{
  char val;
  int line;
  int column;
};
struct node{
  struct charInfo data;
  struct node* next;
};

void print1(struct charInfo* oldChar,int c,int d){
  int a = oldChar->line;
  int b = oldChar->column;
  printf("Found matching braces:(%d,%d) -> ( %d,%d )\n",a,b,c,d);
}

void print2(int a,int b){
  printf("Unmatched brace on Line %d and Column %d\n",a,b);
}
struct charInfo* getTop(struct node* top){
  if(top!=NULL){
    struct charInfo* topChar = &(top->data);
    return topChar;
  }
  return NULL;
}

struct node* pop(struct node* top){
  if(top ==NULL){
    return NULL;
  }
  top = top->next;
  return top;
}


struct node* push(struct node* top, struct charInfo* temp){
  struct node* newNode = malloc(sizeof(struct node));
  newNode->data = *temp;
  newNode ->next = top;
  return newNode;
}


int main(int argc, char** argv) {
  if (argc!= 2) {
    printf("usage: %s ", argv[0]);
  }
  char* fileName= argv[1];
  FILE *infile;
  infile = fopen(fileName, "r");  
    if (infile == NULL) {
    printf("Error: unable to open file %s\n", "input.txt");
    exit(1);
  }
  int ch;

  ch = fgetc(infile);
  int i = 1;
  int j = 1;
  struct node* top= malloc(sizeof(struct node));
  top = NULL;
  
  struct charInfo* temp=malloc(sizeof(struct charInfo));
  struct charInfo* topChar = malloc(sizeof(struct charInfo));
  while(ch !=EOF){
    if(ch == '{'){
      temp->val = '{';
      temp->line = i;
      temp->column = j;
      top=push(top,temp);
    }
    else if(ch=='}'){
      topChar = getTop(top);
      top=pop(top);
      if(topChar==NULL){
        print2(i,j);
      }
      else if(topChar->val=='{'){
        print1(topChar,i,j);
      }
    
      
    }
    else if(ch == '\n'){
      i++;
      j=0;
    }
    j++;
    ch = fgetc(infile);
  }
  while(top!=NULL){
    topChar=getTop(top);
    top=pop(top); 
    print2(topChar->line,topChar->column);
  }
  free(top);

  fclose(infile);
  return 0;
}
