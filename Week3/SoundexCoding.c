#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void soundexCoding(char *lastName);

int main(int argc, char **argv){ /*Is it the same as *argv[]?*/

  if( argc==2 ){
  soundexCoding(argv[1]);
  }
  else{
  printf("ERROR: Incorrect usage, try e.g. %s CHURCHILL\n", argv[0]);
  }

  return 0;
}

void soundexCoding(char *lastName){

  int i, j = 1;
  char code [256] = {0};
  char x = '0';
  char tmp_code[4];

  for(i = 0; i <= 3 ; i++){
    tmp_code[i] += '0';
  }

  tmp_code[0] = lastName[0];
  code[0] = lastName[0];

  for (i = 1; lastName[i] != '\0'; i++){
    if(lastName[i] == 'A' || (lastName[i] == 'E') || (lastName[i] == 'H') || (lastName[i] == 'I') || (lastName[i] == 'O') || (lastName[i] == 'U') || (lastName[i] == 'W') || (lastName[i] == 'Y')){
      code[i] = x + 0;
    }
    if((lastName[i] == 'B') || (lastName[i] == 'F') || (lastName[i] == 'P') || (lastName[i] == 'V')){
      code[i] = x + 1;
    }
    else if(lastName[i] == 'C' || (lastName[i] == 'G') || (lastName[i] == 'J') || (lastName[i] == 'K') || (lastName[i] == 'Q') || (lastName[i] == 'S') || (lastName[i] == 'X') || (lastName[i] == 'Z')){
      code[i] = x + 2;
    }
    else if(lastName[i] == 'D' || (lastName[i] == 'T')){
      code[i] = x + 3;
    }
    else if(lastName[i] == 'L'){
      code[i] = x + 4;
    }
    else if(lastName[i] == 'M' || (lastName[i] == 'N')){
      code[i] = x + 5;
    }
    else if(lastName[i] == 'R'){
      code[i] = x + 6;
    }
  }

  for (i = 1; code[i] != '\0'; i++){
    if(code[i] == code[i + 1]){
      code[i] = code[i + 1];
    }
  }

  for (i = 1; code[i] != '\0'; i++){
    if(code[i] != '0'){
      tmp_code[j] = code[i];
      j++;
    }
  }

  printf("%s\n", tmp_code);
}
