#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#define MAXNUMTOKENS 30000
#define ANSIA 26
#define MAXTOKENSIZE 64
#define strsame(A,B) (strcmp(A, B) == 0)
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %s ocurred in %s, \
line %d\n", PHRASE, __FILE__, __LINE__); exit (2); }

struct prog{
  char wds[MAXNUMTOKENS][MAXTOKENSIZE];
  int cw; /* Current Word */
};
typedef struct prog Program;

void Main(Program *p);
void Instrclst(Program *p);
void Instruction(Program *p);
void DO(Program *p);
void Varnum(Program *p);
void Set(Program *p);
void Polish(Program *p);
int isVar(Program *p);
int isNum(Program *p);
Program *initProg(Program *p);
