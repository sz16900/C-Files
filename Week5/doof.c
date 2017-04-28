#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3
#define BLANK ' '

void printPath(char a[SIZE][SIZE], int x, int y, int n);
int valid(char a[SIZE][SIZE], int x, int y);
void print(char a[SIZE][SIZE]);

int main(void)
{


   char a[SIZE][SIZE];
   memset(a, BLANK, SIZE*SIZE);

   printPath(a, 0, 0, 9);

   return 0;

}

void printPath(char a[SIZE][SIZE], int x, int y, int n)
{

   static int cnt = 0;
   if(n==1){
      print(a);
      printf("%d\n\n", ++cnt);
   }

   if(valid(a,x-1,y)){
      a[y][x] = '<';
      printPath(a, x-1, y, n-1);
      a[y][x] = BLANK; // backtrack
   }
   if(valid(a,x,y+1)){
      a[y][x] = 'v';
      printPath(a, x, y+1, n-1);
      a[y][x] = BLANK; // backtrack
   }
   if(valid(a,x,y-1)){
      a[y][x] = '^';
      printPath(a, x, y-1, n-1);
      a[y][x] = BLANK; // backtrack
   }
   if(valid(a,x+1,y)){
      a[y][x] = '>';
      printPath(a, x+1, y, n-1);
      a[y][x] = BLANK; // backtrack
   }

}

void print(char a[SIZE][SIZE])
{

   int i,j;
   for(j=0; j<SIZE; j++){
      for(i=0; i<SIZE; i++){
         printf("%c", a[j][i]);
      }
      printf("\n");
   }

}

int valid(char a[SIZE][SIZE], int x, int y)
{

   if((x<0)||(y<0)){
      return 0;
   }
   if((x>=SIZE)||(y>=SIZE)){
      return 0;
   }
   if(a[y][x] != BLANK){
      return 0;
   }
   return 1;

}
