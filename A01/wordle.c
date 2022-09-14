#include <stdio.h>
#include <string.h>
#include <time.h>
#include "words.h" // header that defined chooseWord()

int letterInWord(char letter,const char* word){
  for(int i = 0;i<5;i++){
    if(letter==word[i]){
      return 1;
    }
  }
  return 0;
}

int analyzeWord(char guess[],const char* word){
  int ifRight = 1;
  for(int i =0;i<5;i++){
    if(guess[i]==word[i]){
      printf("%c is in the word AND in the correct spot!\n",guess[i]);
    }
    else if(letterInWord(guess[i],word)){
      printf("%c is in the word (but not in the correct spot)!\n",guess[i]);
      ifRight = 0;
    }
    else{
      printf("%c is NOT in the word.\n",guess[i]);
      ifRight = 0;
    }
  }
  return ifRight;
}


int main() {
  srand(time(0));
  const char* word = chooseWord();

  printf("Welcome to Wordle!\n");

  int guessTime=0;
  int trueWord = 0;
  char guess[6];
  while(!trueWord && guessTime<6){
    guessTime++;
    printf("Please enter a 5-letter word: ");
    scanf("%s",guess);
    trueWord = analyzeWord(guess,word);
  }
  if(trueWord){
    printf("You guessed it! The word is %s\n", word);
  }
  if(guessTime >=6){
    printf("Sorry, you ran out of tries. The word is %s\n", word);
  }
  return 0;
}
