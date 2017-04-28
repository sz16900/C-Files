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

void InitialiseStack(Stack *s);
void Push(Stack *s, int n);
int Pop(Stack *s);

int main(void){

  Stack s;
  InitialiseStack(&s);

  Push(&s, 12);
  Push(&s, 117);
  Push(&s, 13);
  Push(&s, 15);
  printf("%d\n", Pop(&s));
  printf("%d\n", Pop(&s));
  printf("%d\n", Pop(&s));
  printf("%d\n", Pop(&s));
  printf("%d\n", Pop(&s));

  return 0;
}

void InitialiseStack(Stack *s){

  s->top = (Elem *)calloc(1, sizeof(Elem)); /* Always free space. But, how? */
  s->top->prev = NULL;
}

void Push(Stack *s, double n){

  Elem *e;
  e = (Elem*)calloc(1, sizeof(Elem));
  e->prev = s->top; /* "this is the most difficult code in C" --by Neill C. */
  s->top->i = n;
  s->top = e;
}

double Pop(Stack *s){

  s->top = s->top->prev;
  assert(s->top != NULL);
  return s->top->i;
}
