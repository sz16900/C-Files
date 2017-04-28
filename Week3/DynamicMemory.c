#include <stdio.h>
#include <stdlib.h>

int main(void){

  int *p;

  p = (int *)malloc(256);

  if(p == NULL){
    printf("Allocation Failed...\n");
    return 1;
  }

  return 0;
}
