#include "interp.h"

void ISEQUAL(Program *p, SDL_Simplewin *sw, Coor *coor){

  double a, b;

  a = Varnum(p);
  p->cw = p->cw + 1;
  if(!(strsame(p->wds[p->cw], "TO"))){
    ERROR("NOT EQUAL");
  }
  p->cw = p->cw + 1;
  b = Varnum(p);
  p->cw = p->cw + 1;
  if(!(strsame(p->wds[p->cw], "{"))){
    ERROR("NOT EQUAL");
  }
  if( (int)a == (int)b ){
    p->cw = p->cw + 1;
    Instrclst(p, sw, coor);
  }
  else{
    while(!(strsame(p->wds[p->cw], "}"))){
      p->cw = p->cw + 1;
    }
    return;
  }

}

void ISGREATER(Program *p, SDL_Simplewin *sw, Coor *coor){

  double a, b;

  a = Varnum(p);
  p->cw = p->cw + 1;
  if(!(strsame(p->wds[p->cw], "TO"))){
    ERROR("NOT EQUAL");
  }
  p->cw = p->cw + 1;
  b = Varnum(p);
  p->cw = p->cw + 1;
  if(!(strsame(p->wds[p->cw], "{"))){
    ERROR("NOT EQUAL");
  }
  if( (int)a > (int)b ){
    p->cw = p->cw + 1;
    Instrclst(p, sw, coor);
  }
  else{
    while(!(strsame(p->wds[p->cw], "}"))){
      p->cw = p->cw + 1;
    }
    return;
  }

}

void ISLESS(Program *p, SDL_Simplewin *sw, Coor *coor){

  double a, b;

  a = Varnum(p);
  p->cw = p->cw + 1;
  if(!(strsame(p->wds[p->cw], "TO"))){
    ERROR("NOT EQUAL");
  }
  p->cw = p->cw + 1;
  b = Varnum(p);
  p->cw = p->cw + 1;
  if(!(strsame(p->wds[p->cw], "{"))){
    ERROR("NOT EQUAL");
  }
  if( (int)a < (int)b ){
    p->cw = p->cw + 1;
    Instrclst(p, sw, coor);
  }
  else{
    while(!(strsame(p->wds[p->cw], "}"))){
      p->cw = p->cw + 1;
    }
    return;
  }

}

void PENCOLOUR(Program *p){
  if (isNum(p) || isVar(p)){
    p->red = Varnum(p);
    if(p->red < 0 || p->red > 255 ){
      ERROR("This does not correspond to a valid rgb value");
    }
  }
  p->cw = p->cw + 1;
  if (isNum(p) || isVar(p)){
    p->green = Varnum(p);
    if(p->green < 0 || p->green > 255 ){
      ERROR("This does not correspond to a valid rgb value");
    }
  }
  p->cw = p->cw + 1;
  if (isNum(p) || isVar(p)){
    p->black = Varnum(p);
    if(p->black < 0 || p->black > 255 ){
      ERROR("This does not correspond to a valid rgb value");
    }
  }
  return;
}

/*double FUNC (Program *p, SDL_Simplewin *sw, Coor *coor, double a , double b){

  if((int)b == 0){
    p->start = 0;
    return a;
  }
  else{
    while(!(strsame(p->wds[p->cw], "STARTFUNC"))){
      Instrclst(p, sw, coor);
      p->cw = p->cw + 1;
    }

    return FUNC(p, sw, coor, a, b);
  }
}*/

/*void penSize(){

}*/
