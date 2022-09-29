#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Restaurant{
  char name[32];
  int openingHour;
  int closingHour;
  float stars;
};

struct node{
  struct Restaurant data;
  struct node* next;
};

struct node* insert_sorted(struct node* head, struct Restaurant* newRestaurant){
  struct node* newNode = malloc(sizeof(struct node));
  if(head==NULL){
    newNode->data = *newRestaurant;
    newNode->next = NULL;
    return newNode;
  }
  else if(newRestaurant->stars>head->data.stars){
    newNode->data = *newRestaurant;
    newNode->next = head;
    return newNode;
  }
  else{
    struct node* temp = head;
    while(temp!=NULL){
      if(newRestaurant->stars<temp->data.stars){
        temp=temp->next;
      }else{
        break;
      }
    }
  newNode->data = *newRestaurant;
  newNode->next = temp->next;
  temp-> next = newNode;
  }
  return head;

}

int main() {
  int num;
  printf("Enter a number of restaurants: ");
  scanf("%d",&num);
  struct node* list;
  list = malloc(sizeof(struct node));
  list = NULL;
  char tempName[32];
  int tempOpen;
  int tempClose;
  float tempStars;
  struct Restaurant* tempRestaurant= malloc(sizeof(struct Restaurant));
  for(int i =0;i<num;i++){
    printf("Enter a name: ");
    scanf(" %[^\n]%*c", tempName);
    strcpy(tempRestaurant->name,tempName);
    printf("Open time: ");
    scanf("%d",&tempOpen);   
    tempRestaurant->openingHour=tempOpen;
    printf("Close time: ");
    scanf("%d",&tempClose);
    tempRestaurant->closingHour=tempClose;
    printf("Stars: ");
    scanf("%f",&tempStars);    
    tempRestaurant->stars = tempStars;
    list = insert_sorted(list,tempRestaurant);
  }
  printf("Welcome to Steven Struct's Restarant List.\n");


  //print the sorted list
  struct node* temp = list;
  for(int i = 0;i<num;i++){
    char name[32];
    strcpy(name,(temp->data).name);
    int openingHour = (temp->data).openingHour;
    int closingHour = (temp->data).closingHour;
    float stars = (temp->data).stars;
    printf("(%d) %s\t open: %d:00\tclose: %d:00\tstars: %.1f\n",i,name,openingHour,closingHour,stars);
    temp = temp->next;
  }

  //free linked list
  while(list !=NULL){
    temp = list;
    list = temp->next;
    free(temp);
  }

  free(tempRestaurant);
  return 0;
}
