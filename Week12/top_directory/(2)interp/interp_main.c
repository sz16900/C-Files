#include "interp.h"

int main(int argc, char **argv){

  int i;
  FILE *fp;
  SDL_Simplewin sw;
  Program prog;
  Coor coor;

  initProg(&prog);
  initCoor(&coor);

  if(argc >= 2){
    if(!(fp = fopen(argv[1], "r"))){
      fprintf(stderr, "Cannot open %s\n", argv[1]);
      exit (2);
    }
    else{
      i = 0;
			while(fscanf(fp, "%s", prog.wds[i++]) == 1){
        if(i > MAXNUMTOKENS){
          printf("\nI'm sorry, but you seem to have more than %d tokens."
          " Please try to shorten the number of tokens and try again. \n\n", MAXNUMTOKENS);
          exit(1);
        }
      }
      Neill_SDL_Init(&sw);
      Main(&prog, &sw, &coor);
    }
  }

  closeWinUserInput(&sw);

  return 0;
}
