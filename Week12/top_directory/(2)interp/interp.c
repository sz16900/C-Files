#include "interp.h"

void Main(Program *p, SDL_Simplewin *sw, Coor *coor){

  if(!strsame(p->wds[p->cw], "{")){
    ERROR("No { statement ?");
  }
  p->cw = p->cw + 1;
  Instrclst(p, sw, coor);
}

void Instrclst(Program *p, SDL_Simplewin *sw, Coor *coor){

  if(strsame(p->wds[p->cw], "}")){
    return;
  }
  Instruction(p, sw, coor);
  p->cw = p->cw + 1;
  Instrclst(p, sw, coor);
}

void Instruction(Program *p, SDL_Simplewin *sw, Coor *coor){

  if(strsame(p->wds[p->cw], "FD")){
    p->cw = p->cw + 1;
    FD(sw, p, coor);
    return;
  }

  if(strsame(p->wds[p->cw], "LT")){
    p->cw = p->cw + 1;
    LT(p, coor);
    return;
  }

  if(strsame(p->wds[p->cw], "RT")){
    p->cw = p->cw + 1;
    RT(p, coor);
    return;
  }

  if(strsame(p->wds[p->cw], "DO")){
    p->cw = p->cw + 1;
    DO(sw, p , coor);
    return;
  }

  if(strsame(p->wds[p->cw], "SET")){
    p->cw = p->cw + 1;
    Set(p);
    return;
  }

  ERROR("Expecting FD, LT, RT, DO, SET or } ?")
}

void FD(SDL_Simplewin *sw, Program *p, Coor *coor){

  double a, nx, ny;
  a = Varnum(p);

  nx = (coor->x + a * cos(coor->a / CIRC * TWIC * M_PI));
  ny = (coor->y + a * sin(coor->a / CIRC * TWIC * M_PI));

  Neill_SDL_SetDrawColour(sw, 255, 255, 255);
  SDL_RenderDrawLine(sw->renderer, coor->x, coor->y, nx, ny);

  /* This is to save the last position, so we can start from here */
  coor->x = nx;
  coor->y = ny;

  SDL_RenderPresent(sw->renderer);
  SDL_UpdateWindowSurface(sw->win);
  SDL_Delay(MILLISECONDDELAY);

  return;
}

void LT(Program *p, Coor *coor){

  double a;
  a = Varnum(p);
  coor->a -= a;

  return;
}

void RT(Program *p, Coor *coor){

  double a;
  a = Varnum(p);
  coor->a += a;

  return;
}

int Var(Program *p, int tempVar){

  int x;

  x = p->wds[tempVar][0] - ANSIA;
  p->alph[x] = p->temp;
  p->flag[x] = 1;
  return x;

}

double Varnum(Program *p){

  int x, tempVar = p->cw;
  double a;

  if( isVar(p) ){
    x = p->wds[tempVar][0] - ANSIA;
    if(p->flag[x] == 0){
      ERROR("Variable not set");
    }
    a = p->alph[x];
    return a;
  }
  else if ( isNum(p) ){
    a = strtod(p->wds[p->cw], NULL);
    return a;
  }
  else{
    ERROR("Not a variable or a number");
  }

}

void DO(SDL_Simplewin *sw, Program *p, Coor *coor){

  double b;
  int temp, tempVar;
  /* Saves the location of the variable so it can be updated */
  tempVar = p->cw;

  if( !(isVar(p)) ){
    ERROR("Not a variable");
  }
  p->cw = p->cw + 1;
  if(!strsame(p->wds[p->cw], "FROM")){
    ERROR("No FROM");
  }
  p->cw = p->cw + 1;
  p->temp = Varnum(p);
  Var(p, tempVar);
  p->cw = p->cw + 1;
  if(!strsame(p->wds[p->cw], "TO")){
    ERROR("No TO")
  }
  p->cw = p->cw + 1;
  b = Varnum(p);
  p->cw = p->cw + 1;
  if(!strsame(p->wds[p->cw], "{")){
    ERROR("No {")
  }
  /* Save the location of the last word to resume from here */
  temp = p->cw;
  doTheLoop(temp, tempVar, p->temp, b, sw, p, coor);

}

void Set(Program *p){

  int tempVar;
  Stack s;
  InitialiseStack(&s);
  /* Save the location of the variable */
  tempVar = p->cw;

  if( !(isVar(p)) ){
    ERROR("Not a variable");
  }
  p->cw = p->cw + 1;
  if(!(strsame(p->wds[p->cw], ":="))){
    ERROR("No :=");
  }
  p->cw = p->cw + 1;
  Polish(p, &s);
  /* This should be the last element in the stack, and clear it */
  p->temp = Pop(&s);
  /* Make sure it really is empty, otherwise, abort */
  if(s.top != 0){
    ERROR("There is something wrong with your Polish");
  }
  Var(p, tempVar);

}

void Polish(Program *p, Stack *s){

  double x, y;

  if(strsame(p->wds[p->cw], ";")){
    return;
    }
  if(strsame(p->wds[p->cw], "+") || strsame(p->wds[p->cw], "-") ||
     strsame(p->wds[p->cw], "*") || strsame(p->wds[p->cw], "/")){
    y = OP(p, s);
    Push(s, y);
    p->cw = p->cw + 1;
    Polish(p, s);
    return;
  }
  if( isVar(p) || isNum(p) ){
    x = Varnum(p);
    Push(s, x);
    p->cw = p->cw + 1;
    Polish(p, s);
    return;

  }
  else{
    ERROR("Something is wrong with your Polish function ")
  }
}

double OP(Program *p, Stack *s){

  double a, b, c;
  b = Pop(s);
  a = Pop(s);

  if(strsame(p->wds[p->cw], "+")){
    c = a + b;
    return c;
  }
  if(strsame(p->wds[p->cw], "-")){
    c = a - b;
    return c;
  }
  if(strsame(p->wds[p->cw], "*")){
    c = a * b;
    return c;
  }
  if(strsame(p->wds[p->cw], "/")){
    c = a / b;
    return c;
  }
  else{
    ERROR("There is something wrong with your operators")
  }
}

double Pop(Stack *s){
  /* Can't pop empty stack (overflow) */
  if(s->top <= 0){
    ERROR("Something is wrong with your Polish expression");
  };
  s->top = s->top - 1;
  return s->stk[s->top].i;
}


void Push(Stack *s, double n){
  /* Make sure stack doesnt overflow */
  if(s->top > STACKSIZE){
    ERROR("You've reached the amount of calculations I can perform. Try a shorter one.");
  }
  s->stk[s->top].i = n;
  s->top = s->top + 1;

}

int isVar(Program *p){

  if( strlen(p->wds[p->cw]) == 1 && isalpha(p->wds[p->cw][0])
      && isupper(p->wds[p->cw][0]) ){
        return 1;
      }

  return 0;
}


int isNum(Program *p){

  int i, cntp = 0, cntm = 0;

  for (i = 0; i < (int)strlen(p->wds[p->cw]); ++i){
    /*Check for non digits */
    if (!isdigit(p->wds[p->cw][i])){
      /*Check for decimals*/
      if(p->wds[p->cw][i] ==  '.'){
        cntp++;
      }
      else if(p->wds[p->cw][i] ==  '-'){
        cntm++;
      }
      else{
        ERROR("Not a Digit");
      }
    }
  }
  /* This makes sure that we only get one '-' and one '.' in case of a negative float */
  if(cntp > 1 || cntm > 1){
    ERROR("Not a Digit");
  }

  return 1;
}

/* This is to check whether we loop up or down */
void doTheLoop(int temp, int tempVar, double a,
  double b, SDL_Simplewin *sw, Program *p, Coor *coor){

  double var = 0;

  if(a > b){
    for(var = a; var >= b; var--){
      p->temp = var;
      Var(p, tempVar);
      p->cw = p->cw + 1;
      Instrclst(p, sw, coor);
      if(var > b){
        p->cw = temp;
      }
    }
  }
  else{
    for(var = a; var <= b; var++){
      p->temp = var;
      Var(p, tempVar);
      p->cw = p->cw + 1;
      Instrclst(p, sw, coor);
      if(var < b){
        p->cw = temp;
      }
    }
  }

}
