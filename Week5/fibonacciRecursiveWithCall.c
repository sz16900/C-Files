#include <stdio.h>

int fibon(int n);

int main(void){

  fibon(4);

  return 0;
}

int fibon(int n){

  printf("Fibonacci: %d\n", n);

  if(n < 2){
    return n;
  }
  else{
    return ( fibon(n-1) + fibon(n-2) );
  }
}
