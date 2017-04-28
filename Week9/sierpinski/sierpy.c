#include <stdio.h>

#define SIZE 81

int rules(int x, int y);
void sierpinski();

int main(void){

sierpinski();

  return 0;
}

int rules(int x, int y){

    while(1){
      if(x == 0 || y == 0){
        return 1;
      }
      else if(x%3==1 && y%3==1){
        return 0;
      }
      x = x/3;
      y = y/3;
    }

}

void sierpinski(){
  int i, j;

  for(i=0; i<SIZE; i++){
    for(j=0; j<SIZE; j++){
      if(rules(i,j)){
        printf("#");
      }
      else{
        printf(" ");
      }
    }
    printf("\n");
  }

}
