#include <stdio.h>
#include <stdlib.h>
#define MYSIZE 40

int main(int argc, char **argv){

    FILE *fp;
    char board[MYSIZE][MYSIZE];
    int i, j;
    int count = 0;
    char c;

    if( argc==2 ){
      if((fp = fopen(argv[1], "r")) == NULL){
        printf("Cannot open file\n");
        return(1);
      }
      for(i = 0; i < MYSIZE; i++){
        for(j = 0; j < MYSIZE; j++){

          fscanf(fp, "%c", &c);


            board[i][j] = c;
          }
          }
        


      for(i = 0; i < MYSIZE; i++){
        for(j = 0; j < MYSIZE; j++){
          printf("%c", board[i][j]);
        }
      }

      printf("%d", count);
      fclose(fp);
    }
    else{
    printf("ERROR: Incorrect usage, try e.g. %s wiretext.txt\n", argv[0]);
    }
    return 0;
  }
