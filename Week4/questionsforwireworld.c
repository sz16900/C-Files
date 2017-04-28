#include <stdio.h>
#include <stdlib.h>

#define SIZE 40

int main(int argc, char **argv){

  FILE *fp;
  int i, j;
  int generations = 0;
  int sum = 0;
  char **board;
  char **board_copy;

  if( argc==2 ){
    if((fp = fopen(argv[1], "r")) == NULL){
      printf("Cannot open file\n");
      return(1);
    }

    board = (char **) malloc(SIZE * sizeof(char*));
    for (i = 0; i<SIZE; i++) {
      board[i] = (char *) malloc(SIZE * sizeof(char));
    }

    board_copy = (char **) malloc(SIZE * sizeof(char*));
    for (i = 0; i<SIZE; i++) {
      board_copy[i] = (char *) malloc(SIZE * sizeof(char));
    }

    for(i = 0; i < SIZE; i++){
      for(j = 0; j < SIZE; j++){
      fscanf(fp, "%c", &board[i][j]);
      }
    }

    for(i = 0; i < SIZE; i++){
      for(j = 0; j < SIZE; j++){
      board_copy[i][j] = board[i][j];
      }
    }
    do{
      for(i = 0; i<SIZE; i++){
        for(j = 0; j < SIZE; j++){
        fprintf(stdout, "%c", board_copy[i][j]);
        }
      }
      for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
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
      for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
        board[i][j] = board_copy[i][j];
        }
      }
      generations++;
    }while(generations != 32);

    free(board);
    free(board_copy);
    fclose(fp);
  }

  else{
  printf("ERROR: Incorrect usage, try e.g. %s wiretext.txt\n", argv[0]);
  }

  return 0;
}
