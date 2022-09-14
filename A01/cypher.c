#include <stdio.h>
int main() {
    char word[20];
    int shift;
    printf("Enter a word: ");
    scanf("%s",word);
    printf("Enter a shift: ");
    scanf("%d",&shift);
    for(int i =0; i<19;i++){
        if(word[i]<='z'&&word[i]>='a'){
            word[i]=word[i]+shift;
            if(word[i]>'z'){
                word[i]=word[i]-26;
            }
        }
    }
    printf("Your cypher is %s \n", word);
    return 0;
}
