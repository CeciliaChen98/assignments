#include <string.h>
#include <stdio.h>
struct Restaurant{
  char name[40];
  int openingHour;
  int closingHour;
  float stars;
};





int main() {
  struct Restaurant sushi;
  strcpy(sushi.name,"Sushi Land            ");
  sushi.openingHour = 14;
  sushi.closingHour = 22;
  sushi.stars = 4.3;
  struct Restaurant cheese;
  strcpy(cheese.name,"The Cheesecake Factory");
  cheese.openingHour = 11;
  cheese.closingHour = 22;
  cheese.stars = 4.1;
  struct Restaurant burger;
  strcpy(burger.name,"Shake Shack           ");
  burger.openingHour = 11;
  burger.closingHour = 21;
  burger.stars = 4.0;
  struct Restaurant thirsty;
  strcpy(thirsty.name,"The Thirsty Horse    ");
  thirsty.openingHour = 17;
  thirsty.closingHour = 2;
  thirsty.stars = 4.5;

  struct Restaurant list[4]={sushi,cheese,burger,thirsty};

  int time;
  printf("Welcome to Steven Struct's Restarant List.\n\nWhat hour is it (24 hr clock)?");
  scanf("%d",&time);
  printf("\n");

  for(int i = 0;i<4;i++){
    char name[40];
    strcpy(name,list[i].name);
    int openingHour = list[i].openingHour;
    int closingHour = list[i].closingHour;
    float stars = list[i].stars;
    printf("(%d) %s\t open: %d:00\tclose: %d:00\tstars: %.1f\n",i,name,openingHour,closingHour,stars);
  }

  int index;
  printf("\nWhat restaurant do you want to visit? [0,1,2] ");
  scanf("%d",&index);
  int openingHour = list[index].openingHour;
  int closingHour = list[index].closingHour;

  int remainingHour;
  if(openingHour<closingHour){
    if(time>=openingHour&&time<=closingHour){
      remainingHour = closingHour-time;
      printf("Excellent choice. %s will be open for %d more hours",list[index].name,remainingHour);
    }
    else if(time<openingHour){
      printf("%s isn't open until %d o'clock!!",list[index].name,openingHour);
    }
    else{
      printf("%s closed at %d o'clock!!",list[index].name,closingHour);
    }
  }else{
    if(time<=openingHour&&time<=closingHour){
      remainingHour = closingHour-time;
      printf("Excellent choice. %s will be open for %d more hours",list[index].name,remainingHour);
    }
    else if(time>=openingHour&&time<=closingHour+24){
      remainingHour = 24-time+closingHour;
      printf("Excellent choice. %s will be open for %d more hours",list[index].name,remainingHour);
    }
    else{
        if((time-closingHour)>(openingHour-time)){
          printf("%s isn't open until %d o'clock!!",list[index].name,openingHour);
        }
        else{
           printf("%s closed at %d o'clock!!",list[index].name,closingHour);
        }
    }
  }
  return 0;
}
