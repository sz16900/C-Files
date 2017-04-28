#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3
#define BLANK ' '

void printPath(char a[SIZE][SIZE], int x, int y, int n);
int

int main(void){

  char a [SIZE][SIZE];

  memset(a, BLANK, SIZE*SIZE);

  printPath(a, 0, 1, 9);
}


void printPath(char a[SIZE][SIZE], int x, int y, int n){

  static int cnt = 0;

  if(n == 1){
    print(a);
    printf("%d\n\n", ++cnt);
  }
}
