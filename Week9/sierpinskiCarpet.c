#include <stdio.h>
#define MYSIZE 81
#define BLANK ' '


void printBoard(char board[MYSIZE][MYSIZE]);
int fillUpArray(char board[MYSIZE][MYSIZE], FILE *fp);

int main(int argc, char **argv){

  FILE *fp;
  char board[MYSIZE][MYSIZE];
  int level;

  if( argc==2 ){
    if((fp = fopen(argv[1], "r")) == NULL){
      printf("ERROR: Incorrect usage, try e.g. %s wirecircuit1.txt\n", argv[0]);
      return 1;
    }
    else if(fillUpArray(board, fp) == 1){
      return 1;
    }

    level = MYSIZE/3;




    printBoard(board);

  }

  return 0;
}


int fillUpArray(char board[MYSIZE][MYSIZE], FILE *fp){

  int i, j;
  char c;

  for(i = 0; i < MYSIZE; i++){
    for(j = 0; j < MYSIZE; j++){
      /*Checks whether the file is corrupted*/
      if(fscanf(fp, "%c", &c) != 1 ){
        printf("ERROR. There seems to be a problem with your file.\n");
        return 1;
      }
      if(c == '\n'){
        j--;
      }
      else{
        board[i][j] = c;
      }
    }
  }

  return 0;
}

void printBoard(char board[MYSIZE][MYSIZE]){
  int i, j;

  for(i=0; i<MYSIZE; i++){
    for(j=0; j<MYSIZE; j++){
        printf("%c", board[i][j]);
    }
    printf("\n");
  }
}


void sierpinski(char board[MYSIZE][MYSIZE], int level){
  int i,j;

  if(level < 9){

  }
  else{
    for(i=0; i<level; i++){
      for(j=0; j<level; j++){

      }
    }
  }

}
