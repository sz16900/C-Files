#include <stdio.h>

int main(void) {

  int a[] = {10, 12, 6, 7, 2};
  int i;
  int sum = 0;

  for (i=0; i<5; i++){
    sum += a[i];
  }
  printf("%d\n", sum );

  return 0;
}
