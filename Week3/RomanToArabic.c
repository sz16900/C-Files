#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int romanToArabic(char *roman);

int main(int argc, char **argv){ /*Is it the same as *argv[]?*/

  if( argc==2 ){
  printf("The roman numeral %s is equal to %d\n", argv[1], romanToArabic(argv[1]));
  }
  else{
  printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
  }

  return 0;
}

int romanToArabic(char *roman){

  int j, sum = 0;
  int I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000;

  for (j = strlen(roman); j >= 0; j--){
    if(roman[j] == 'V' && roman[j - 1] == 'I'){
      sum += 4;
      j--;
    }
    else if(roman[j] == 'X' && roman[j - 1] == 'I'){
      sum += 9;
      j--;
    }
    else if(roman[j] == 'L' && roman[j - 1] == 'X'){
      sum += 40;
      j--;
    }
    else if(roman[j] == 'C' && roman[j - 1] == 'X'){
      sum += 90;
      j--;
    }
    else if(roman[j] == 'D' && roman[j - 1] == 'C'){
      sum += 400;
      j--;
    }
    else if(roman[j] == 'M' && roman[j - 1] == 'C'){
      sum += 900;
      j--;
    }
    else if(roman[j] == 'I'){
      sum += I;
    }
    else if(roman[j] == 'V'){
      sum += V;
    }
    else if(roman[j] == 'X'){
      sum += X;
    }
    else if(roman[j] == 'L'){
      sum += L;
    }
    else if(roman[j] == 'C'){
      sum += C;
    }
    else if(roman[j] == 'D'){
      sum += D;
    }
    else if(roman[j] == 'M'){
      sum += M;
    }
  }

  return sum;
}
