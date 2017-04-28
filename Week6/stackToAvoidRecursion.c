#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct stackelem{
  int i;
  struct stackelem *prev;
};
typedef struct stackelem Elem;

struct thestack{
  Elem *tp;
};
typedef struct thestack Stack;

void StringReverse(char *s);
void InitialiseStack(Stack *s);
void Push(Stack *s, int n);
int Pop(Stack *s);

int main(void){

  char str[] = "Hello World!";
  StringReverse(str);
  printf("%s\n", str);

  return 0;
}

void StringReverse(char *str){

  char *k;
  int i;
  int l = 0;
  Stack s;
  InitialiseStack(&s);

  k = str;
  while(*k != '\0'){
    Push(&s, (int)*k);
    k++;
    l++;
  }

  k = str;
  for(i = 0; i < l; i++){
    *k = Pop(&s);
    k++;
  }
}

void InitialiseStack(Stack *s){

  s->tp = (Elem *)calloc(1, sizeof(Elem)); /* Always free space. But, how? */
  s->tp->prev = NULL;
}

void Push(Stack *s, int n){

  Elem *e;
  e = (Elem*)calloc(1, sizeof(Elem));
  e->prev = s->tp; /* "this is the most difficult code in C" --by Neill C. */
  s->tp->i = n;
  s->tp = e;
}

int Pop(Stack *s){

  s->tp = s->tp->prev;
  assert(s->tp != NULL);
  return s->tp->i;
}
