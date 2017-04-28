#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <SDL2/SDL_image.h>

#define ANSIA 65
#define ALPHABET 26
#define STACKSIZE 1000
#define MAXNUMTOKENS 30000
#define MAXTOKENSIZE 64
#define strsame(A,B) (strcmp(A, B) == 0)
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %s ocurred in %s, \
line %d\n", PHRASE, __FILE__, __LINE__); exit (2); }
#define WWIDTH 1000
#define WHEIGHT 600
#define MILLISECONDDELAY 1
#define STPOINTX 500
#define STPOINTY 300
#define CIRC 360.0
#define TWIC 2.0
#define SPSIZE 32
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

/* All info required for windows / renderer & event loop */
struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
};
typedef struct SDL_Simplewin SDL_Simplewin;

struct prog{
  char wds[MAXNUMTOKENS][MAXTOKENSIZE];
  double alph[ALPHABET];
  int cw; /* Current Word */
  double temp;
  int tempvars;
  int penup;
  int flag[ALPHABET];
  int red;
  int green;
  int black;
  /*int func;
  int start;*/
};
typedef struct prog Program;

struct coor{
  double x;
  double y;
  double a;
};
typedef struct coor Coor;

struct stackelem{
  double i;
};
typedef struct stackelem Elem;

struct thestack{
  Elem stk[STACKSIZE];
  int top;
};
typedef struct thestack Stack;

void Main(Program *p, SDL_Simplewin *sw, Coor *coor);
void Instrclst(Program *p, SDL_Simplewin *sw, Coor *coor);
void Instruction(Program *p, SDL_Simplewin *sw, Coor *coor);
void FD(SDL_Simplewin *sw, Program *p, Coor *coor);
void LT(Program *p, Coor *coor);
void RT(Program *p, Coor *coor);
void DO(SDL_Simplewin *sw, Program *p, Coor *coor);
int Var(Program *p, int tempVar);
double Varnum(Program *p);
double Set(Program *p);
void Polish(Program *p, Stack *s);
double OP(Program *p, Stack *s);
Program *initProg(Program *p);
Coor *initCoor(Coor *coor);
void InitialiseStack(Stack *s);
void Push(Stack *s, double n);
double Pop(Stack *s);
void Neill_SDL_Init(SDL_Simplewin *sw);
void Neill_SDL_Events(SDL_Simplewin *sw);
void Neill_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b);
void drawLine(SDL_Simplewin *sw, Coor *coor);
void closeWinUserInput(SDL_Simplewin *sw);
int isNum(Program *p);
int isVar(Program *p);
void doTheLoop(int temp, int tempVar, double a, double b, SDL_Simplewin *sw, Program *p, Coor *coor);

/* Entended Grammar Functions */
void ISEQUAL(Program *p, SDL_Simplewin *sw, Coor *coor);
void ISGREATER(Program *p, SDL_Simplewin *sw, Coor *coor);
void ISLESS(Program *p, SDL_Simplewin *sw, Coor *coor);
void PENCOLOUR(Program *p);
void sprite(SDL_Simplewin *sw, Coor *coor);
/*double FUNC (Program *p, SDL_Simplewin *sw, Coor *coor, double a, double b );*/
