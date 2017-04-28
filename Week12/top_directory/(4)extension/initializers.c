#include "interp.h"

/* Initializes the structure and set all the elements with values */
Program *initProg(Program *p){

  int i;

  p->cw = 0;
  for(i = 0; i < MAXNUMTOKENS; i++){
    p->wds[i][0] = '\0';
  }
  for(i = 0; i < ALPHABET; i++){
    p->alph[i] = 0;
    p->flag[i] = 0;
  }
  p->red = 0;
  p->green = 255;
  p->black = 0;

  return p;
}

Coor *initCoor(Coor *coor){

  coor->x = STPOINTX;
  coor->y = STPOINTY;
  coor->a = 0;

  return coor;
}

void InitialiseStack(Stack *s){
  s->top = 0;
}
