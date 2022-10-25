#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

int main(){
    printf("please enter a phrase: \n");
    char input[100];
    scanf("%[^\n]%*c",input);
    printf("Input is %s, length is %ld\n",input,strlen(input));
    for(int i =0;i<strlen(input);i++){
        if(strcmp(&input[i]," ")==0){
            continue;
        }
        unsigned int thirdShift = input[i]>>2 & 0x01;
        unsigned int forthShift = input[i]>>3 & 0x01;
        unsigned int newShift = thirdShift ^ forthShift;
        newShift = newShift<<3|newShift<<2;
        input[i] = newShift^input[i];
    }

    printf("scramble: %s\n",input);
}