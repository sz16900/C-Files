#include "parse.h"

void Main(Program *p){
  if(!strsame(p->wds[p->cw], "{")){
    ERROR("No { statement ?");
  }
  p->cw = p->cw + 1;
  Instrclst(p);
}

void Instrclst(Program *p){
  if(strsame(p->wds[p->cw], "}")){
    return;
  }
  Instruction(p);
  p->cw = p->cw + 1;
  Instrclst(p);
}

void Instruction(Program *p){
  if(strsame(p->wds[p->cw], "FD")){
    p->cw = p->cw + 1;
    Varnum(p);
    return;
  }
  if(strsame(p->wds[p->cw], "LT")){
    p->cw = p->cw + 1;
    Varnum(p);
    return;
  }
  if(strsame(p->wds[p->cw], "RT")){
    p->cw = p->cw + 1;
    Varnum(p);
    return;
  }
  if(strsame(p->wds[p->cw], "DO")){
    p->cw = p->cw + 1;
    DO(p);
    return;
  }
  if(strsame(p->wds[p->cw], "SET")){
    p->cw = p->cw + 1;
    Set(p);
    return;
  }
  ERROR("Expecting FD, LT, RT, DO, SET or } ?")
}

void Varnum(Program *p){

  if( isVar(p) ){
    return;
  }
  else if( isNum(p) ){
    return;
  }
  else{
    ERROR("Not a variable or a number");
  }

}

void DO(Program *p){

  if( !(isVar(p)) ){
    ERROR("Not a variable");
  }
  p->cw = p->cw + 1;
  if(!strsame(p->wds[p->cw], "FROM")){
    ERROR("No FROM ");
  }
  p->cw = p->cw + 1;
  Varnum(p);
  p->cw = p->cw + 1;
  if(!strsame(p->wds[p->cw], "TO")){
    ERROR("Not TO")
  }
  p->cw = p->cw + 1;
  Varnum(p);
  p->cw = p->cw + 1;
  if(!strsame(p->wds[p->cw], "{")){
    ERROR("Not {")
  }
  p->cw = p->cw + 1;
  Instrclst(p);
}

void Set(Program *p){

  if( !(isVar(p) ) ){
    ERROR("Not a variable");
  }
  p->cw = p->cw + 1;
  if(!(strsame(p->wds[p->cw], ":="))){
    ERROR("No :=");
  }
  p->cw = p->cw + 1;
  Polish(p);

  return;
}

void Polish(Program *p){

  if(strsame(p->wds[p->cw], ";")){
    return;
    }
  if(strsame(p->wds[p->cw], "+") || strsame(p->wds[p->cw], "-") ||
     strsame(p->wds[p->cw], "*") || strsame(p->wds[p->cw], "/")){
    p->cw = p->cw + 1;
    Polish(p);
    return;
  }
  if( isVar(p) || isNum(p) ){
    Varnum(p);
    p->cw = p->cw + 1;
    Polish(p);
    return;

  }
  else{
    ERROR("Something is wrong with your Polish function ")
  }
}

/* Initializes the structure and sets all the elements to '\0'*/
Program *initProg(Program *p){

  int i;

  p->cw = 0;
  for(i = 0; i < MAXNUMTOKENS; i++){
    p->wds[i][0] = '\0';
  }

  return p;
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
      /* Check for negative numbers */
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
