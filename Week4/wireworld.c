#include <stdio.h>
#include "neillncurses.h"
#define MYSIZE 40

int isValidFile(char c);
int checkSize(FILE *fp);
char bCheck(char board[MYSIZE][MYSIZE], int i, int j); /* Checks for boundaries */
int fillUpArray(char board[MYSIZE][MYSIZE], FILE *fp);
void copyArray(char board[MYSIZE][MYSIZE], char board_copy[MYSIZE][MYSIZE]);
void wireworld(char board[MYSIZE][MYSIZE], char board_copy[MYSIZE][MYSIZE]);


int main(int argc, char **argv){

  FILE *fp;
  char board[MYSIZE][MYSIZE];
  char board_copy[MYSIZE][MYSIZE];

  if( argc==2 ){
    if((fp = fopen(argv[1], "r")) == NULL){
      printf("ERROR: Incorrect usage, try e.g. %s wirecircuit1.txt\n", argv[0]);
      return 1;
    }
    else if(fillUpArray(board, fp) == 1 || checkSize(fp) == 1){
      return 1;
    }

    copyArray(board, board_copy);
    wireworld(board, board_copy);
    fclose(fp);
  }

  return 0;
}

void wireworld(char board[MYSIZE][MYSIZE], char board_copy[MYSIZE][MYSIZE]){

  int i, j, sum = 0;
  NCURS_Simplewin sw;

  Neill_NCURS_Init(&sw);
  Neill_NCURS_CharStyle(&sw, "H", COLOR_BLUE, COLOR_BLUE, A_NORMAL);
  Neill_NCURS_CharStyle(&sw, "c", COLOR_YELLOW, COLOR_YELLOW, A_NORMAL);
  Neill_NCURS_CharStyle(&sw, "t", COLOR_RED, COLOR_RED, A_NORMAL);
  Neill_NCURS_CharStyle(&sw, " ", COLOR_BLACK, COLOR_BLACK, A_NORMAL);

  do{
    Neill_NCURS_PrintArray(&board[0][0], MYSIZE, MYSIZE, &sw);
    for(i = 0; i < MYSIZE; i++){
      for(j = 0; j < MYSIZE; j++){
        switch(board[i][j]){
          case ' ': board_copy[i][j] = ' '; break;
          case 't': board_copy[i][j] = 'c'; break;
          case 'H': board_copy[i][j] = 't'; break;
          case 'c': {
              sum = (bCheck(board, i-1, j-1) == 'H') + (bCheck(board, i - 1, j) == 'H') +
              (bCheck(board, i - 1, j + 1) == 'H') + (bCheck(board, i, j - 1)   == 'H') +
              (bCheck(board, i, j + 1) == 'H') + (bCheck(board, i + 1, j - 1) == 'H') +
              (bCheck(board, i + 1, j) == 'H') + (bCheck(board, i + 1, j + 1) == 'H');
              board_copy[i][j] = (sum == 1 || sum == 2) ? 'H' : 'c';
              break;
          }
          default:
          board[i][j] = board_copy[i][j];
        }
      }
    }
    /* Copying array to be checked against*/
    for(i = 0; i < MYSIZE; i++){
      for(j = 0; j < MYSIZE; j++){
        board[i][j] = board_copy[i][j];
      }
    }

    Neill_NCURS_Delay(100);
    Neill_NCURS_Events(&sw);

    }while(!sw.finished);

    atexit(Neill_NCURS_Done);
    exit(EXIT_SUCCESS);
}

int isValidFile(char c){

  if(c != 't' && c != 'H' && c != 'c' && c != ' ' && c != '\n'){
    return 1;
  }
  else{
    return 0;
  }

}

int fillUpArray(char board[MYSIZE][MYSIZE], FILE *fp){

  int i, j;
  char c;

  for(i = 0; i < MYSIZE; i++){
    for(j = 0; j < MYSIZE; j++){
      /*Checks whether the file is corrupted*/
      if(fscanf(fp, "%c", &c) != 1  || isValidFile(c) == 1){
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

void copyArray(char board[MYSIZE][MYSIZE], char board_copy[MYSIZE][MYSIZE]){

  int i, j;

  for(i = 0; i < MYSIZE; i++){
    for(j = 0; j < MYSIZE; j++){
      board_copy[i][j] = board[i][j];
    }
  }
}

int checkSize(FILE *fp){

  int size = 0;

  fseek(fp, 0L, SEEK_END);
  size = ftell(fp);
  rewind(fp);
  if(size != 1640 /*this is the number of bytes in a file we should care for*/){
    printf("ERROR. Your file is too large.\n");
    return 1;
  }

  return 0;
}

char bCheck(char board[MYSIZE][MYSIZE], int i, int j){
  if(i < 0 || i > MYSIZE - 1 || j < 0 || j > MYSIZE){
    return 0;
  }
  else{
    return board[i][j];
  }

}
