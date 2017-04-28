#include <stdio.h>

#define MYSIZE 40

void wireworld(char board[MYSIZE][MYSIZE], char board_copy[MYSIZE][MYSIZE]);

int main(int argc, char **argv){

  FILE *fp;
  char board[MYSIZE][MYSIZE];
  char board_copy[MYSIZE][MYSIZE];
  int i, j;
  int generations = 0;

  if( argc==2 ){
    if((fp = fopen(argv[1], "r")) == NULL){
      printf("Cannot open file\n");
      return(1);
    }
    for(i = 0; i < MYSIZE; i++){
      for(j = 0; j < MYSIZE; j++){
        if((fscanf(fp, "%c", &board[i][j])) == 'o'){ /*How to solve this problem*/
          printf("ERROR, I cannot go on.\n");
          return(1);
        }
      }
    }
    for(i = 0; i < MYSIZE; i++){
      for(j = 0; j < MYSIZE; j++){
      board_copy[i][j] = board[i][j];
      }
    }
    do{
      wireworld(board, board_copy);
      generations++;
    }while(generations != 3);
    fclose(fp);
  }
  else{
  printf("ERROR: Incorrect usage, try e.g. %s wiretext.txt\n", argv[0]);
  }
  return 0;
}

void wireworld(char board[MYSIZE][MYSIZE], char board_copy[MYSIZE][MYSIZE]){

  int i, j, sum = 0;

    for(i = 0; i < MYSIZE; i++){
      for(j = 0; j < MYSIZE; j++){
      fprintf(stdout, "%c", board_copy[i][j]);
      }
    }
    for(i = 0; i < MYSIZE; i++){
      for(j = 0; j < MYSIZE; j++){
        switch(board[i][j]){
          case ' ': board_copy[i][j] = ' '; break;
          case 't': board_copy[i][j] = 'c'; break;
          case 'H': board_copy[i][j] = 't'; break;
          case 'c': {
              sum = (board[i - 1][j - 1] == 'H') + (board[i - 1][j] == 'H') + (board[i - 1][j + 1] == 'H') +
              (board[i][j - 1]   == 'H') + (board[i][j + 1]   == 'H') + (board[i + 1][j - 1] == 'H') +
              (board[i + 1][j] == 'H') + (board[i + 1][j + 1] == 'H');
              board_copy[i][j] = (sum == 1 || sum == 2) ? 'H' : 'c';
              break;
          }
          default:
          board[i][j] = board_copy[i][j];
          
        }
      }
    }
    for(i = 0; i < MYSIZE; i++){
      for(j = 0; j < MYSIZE; j++){
      board[i][j] = board_copy[i][j];
      }
    }
}
