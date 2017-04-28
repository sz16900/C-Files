#include <stdio.h>
#include <stdlib.h>

#define N 90

void rules(int a[], int b[], int l, int c, int r);

int main (void){
  int i, j, leftchar, rightchar, currentchar;
  int the_array[N] = {0};
  int tmp_the_array[N] = {0};

  the_array[80] = 1;
  for (i = 0; i < N; i++){
    printf("%d", the_array[i]);
  }
  printf("\n");


  do {
    for (i = 0; i < N; i++){
      leftchar = i - 1;
      rightchar = i + 1;
      rules(tmp_the_array, the_array, leftchar, i, rightchar);
    }
    for (i = 0; i < N; i++){
    printf("%d",tmp_the_array[i]);
    }
    printf("\n");
    for (i = 0; i < N; i++){ /*how can I reset or copy the array so i can continue on the next line? */
        the_array[i] = tmp_the_array[i];
    }

    j++;
  } while (j < 61);


return 0;
}

void rules(int a[], int b[], int l, int c, int r){
  if ((b[l] == 0) && (b[c] == 0) && (b[r] == 0)){
    a[c] = 0;
  }
  else if ((b[l] == 0) && (b[c] == 0) && (b[r] == 1)){
    a[c] = 1;
  }
  else if ((b[l] == 0) && (b[c] == 1) && (b[r] == 0)){
    a[c] = 1;
  }
  else if ((b[l] == 0) && (b[c] == 1) && (b[r] == 1)){
    a[c] = 1;
  }
  else if ((b[l] == 1) && (b[c] == 0) && (b[r] == 0)){
    a[c] = 0;
  }
  else if ((b[l] == 1) && (b[c] == 0) && (b[r] == 1)){
    a[c] = 1;
  }
  else if ((b[l] == 1) && (b[c] == 1) && (b[r] == 0)){
    a[c] = 1;
  }
  else if ((b[l] == 1) && (b[c] == 1) && (b[r] == 1)){
    a[c] = 0;
  }
}
