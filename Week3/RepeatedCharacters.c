#include <stdio.h>
#include <ctype.h>

#define N 26

int main(void){

  char s[100] = "The Quick Brown Fox Leaps Over The Lazy Dog";
  short used[N] = {0};
  char c;
  int i = 0;

  while (s[i] != '\0'){
    c = tolower(s[i]);
    if(islower(c)){
      used[c - 'a'] = 1;
    }
    i++;
  }

  for(i = 0; i < N; i++){
    if(used[i] == 0 /*Or u can say !used[i]*/){
      printf("%c has not been used yet.\n", i + 'a');
    }
  }

  return 0;
}
