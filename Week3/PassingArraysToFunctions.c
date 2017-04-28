#include <stdio.h>

void zero_array(int b[], int s);
void zero_array2(int *b, int s);

int main(void) {

  int a[5], i;

  zero_array(a, 5);

  zero_array(&a[1], 3); /* To Initiliaze the middle three, we use this */

  return 0;
}

void zero_array(int b[], int s){

  int i;
  for(i = 0; i<s; i++){
    b[i] = 0;
  }
}

void zero_array2(int *b, int s){

  int i;
  for(i = 0; i<s; i++){
    *b++ = 0;
  }
}
