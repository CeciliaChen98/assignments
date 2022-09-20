#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Restaurant{
  char name[32];
  int openingHour;
  int closingHour;
  float stars;
};

int main() {
  int num;
  printf("Enter a number of restaurants: ");
  scanf("%d",&num);
  struct Restaurant* list;
  list = malloc(sizeof(struct Restaurant)*num);
  char tempName[32];
  int tempOpen;
  int tempClose;
  float tempStars;
  for(int i =0;i<num;i++){
    printf("Enter a name: ");
    scanf(" %[^\n]%*c", tempName);
    strcpy(list[i].name,tempName);
    printf("Open time: ");
    scanf("%d",&tempOpen);   
    list[i].openingHour=tempOpen;
    printf("Close time: ");
    scanf("%d",&tempClose);
    list[i].closingHour=tempClose;
    printf("Stars: ");
    scanf("%f",&tempStars);    
    list[i].stars = tempStars;
  }
  printf("Welcome to Steven Struct's Restarant List.\n");

  for(int i = 0;i<num;i++){
    char name[32];
    strcpy(name,list[i].name);
    int openingHour = list[i].openingHour;
    int closingHour = list[i].closingHour;
    float stars = list[i].stars;
    printf("(%d) %s\t open: %d:00\tclose: %d:00\tstars: %.1f\n",i,name,openingHour,closingHour,stars);
  }
  free(list);
  return 0;
}
