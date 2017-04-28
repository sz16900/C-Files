#include <stdio.h>

int main(int argc, char **argv){

  FILE *fp;
  char board[41][41];
  char board_copy[41][41];
  int i, j;
  int generations = 0;

  if( argc==2 ){
    if((fp = fopen(argv[1], "r")) == NULL){
      printf("Cannot open file\n");
      return(1);
    }

    for(i = 0; i < 40; i++){
      for(j = 0; j < 41; j++){
      fscanf(fp, "%c", &board[i][j]);
      }
    }

    for(i = 0; i < 40; i++){
      for(j = 0; j < 41; j++){
      board_copy[i][j] = board[i][j];
      }
    }

    for(i = 0; i<40; i++){
      for(j = 0; j < 41; j++){
      fprintf(stdout, "%c", board_copy[i][j]);
      }
    }



    do{
      for(i = 0; i < 40; i++){
        for(j = 0; j < 41; j++){
          if( (board[i][j] == 'c') && ((board[i - 1][j - 1] == 'H') ||
            (board[i][j - 1] == 'H') || (board[i + 1][j - 1] == 'H') ||
            (board[i + 1][j] == 'H') || (board[i + 1][j + 1] == 'H') ||
            (board[i][j + 1] == 'H') || (board[i - 1][j + 1] == 'H') ||
            (board[i - 1][j] == 'H')) ){
            board_copy[i][j] = 'H';
          }
          if(board[i][j] == 'H' && board[i][j - 1] == 'H'){
            board_copy[i][j] = 'c';
          }
          if(board[i][j] == 't'){
            board_copy[i][j] = 'c';
          }
          if(board[i][j] == 'H'){
            board_copy[i][j] = 't';
          }
          /*this is to stop the electron from flowing after three. WHAT IF ITS FOUR, OR FIVE OR...?*/
          if( ((board[i][j] == 'c') && (board[i - 1][j - 1] == 'H') && /*from the right*/
            (board[i][j - 1] == 'H') && (board[i + 1][j - 1] == 'H')) ||
            ((board[i][j] == 'c') && (board[i - 1][j - 1] == 'H') && /*from the top*/
              (board[i - 1][j] == 'H') && (board[i - 1][j + 1] == 'H')) ||
            ((board[i][j] == 'c') && (board[i - 1][j + 1] == 'H') && /*from the left*/
              (board[i][j + 1] == 'H') && (board[i + 1][j + 1] == 'H')) ||
            ((board[i][j] == 'c') && (board[i + 1][j - 1] == 'H') && /*from the bottom*/
              (board[i + 1][j] == 'H') && (board[i + 1][j + 1] == 'H'))){
            board_copy[i][j] = 'c';
          }
        }
      }
      for(i = 0; i < 40; i++){
        for(j = 0; j < 41; j++){
        board[i][j] = board_copy[i][j];
        }
      }
      for(i = 0; i < 40; i++){ /*When the wires L, the H's double up. This is to fix that */
        for(j = 0; j < 41; j++){
          if((board[i][j] == 'H' && board[i][j - 1] == 'H')){
            fprintf(stdout, "%c", board_copy[i][j] = 'c');
          }
          else if((board[i][j] == 't' && board[i][j - 1] == 't')){
            fprintf(stdout, "%c", board_copy[i][j - 1] = 'c');
          }
          else{
            fprintf(stdout, "%c", board_copy[i][j]);
          }
        }
      }
      generations++;
    }while(generations != 91);

    fclose(fp);
  }
  else{
  printf("ERROR: Incorrect usage, try e.g. %s wiretext.txt\n", argv[0]);
  }

  return 0;
}
