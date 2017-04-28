#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE 100

struct node {
  int letter;
  struct node *left;
  struct node *right;
};
typedef struct node Node;

struct queue{
  Node *n[MAX_QUEUE];
  int front;
  int back;
};
typedef struct queue Queue;

void InitialiseQueue(Queue *q);
void PrintLevelOrder(Node *t);
Node *Remove(Queue *q);
void Insert(Node *t, Queue *q);
int Empty(Queue q);
Node *AllocateNode(char s);

int main(void){

  Node *s;

  s->letter = 'A';
  s->left = AllocateNode('B');
  s->right = AllocateNode('C');
  s->left->left = AllocateNode('E');
  s->left->right = AllocateNode('F');
  printf("%c\n", s  ->letter);
  printf("%c\n", s->left->letter);
  printf("%c\n", s->right->letter);
  printf("%c\n", s->left->left->letter);
  printf("%c\n", s->left->right->letter);

  PrintLevelOrder(s);


  return 0;
}

void InitialiseQueue(Queue *q){
  q->front = 0;
  q->back = 0;
}

Node *Remove(Queue *q){
  Node *n;
  n = q->n[q->front];
  q->front = (q->front + 1) % MAX_QUEUE;
  return n;
}

void Insert(Node *t, Queue *q){
  q->n[q->back] = t;
  q->back = (q->back + 1) % MAX_QUEUE;
}

int Empty(Queue q){
  if(q.front == q.back){
    return 1;
  }
  return 0;
}

void PrintLevelOrder(Node *t){
  Queue q;
  Node *n;

  InitialiseQueue(&q);
  Insert(t, &q);
  while(!Empty(q)){
    n = Remove(&q);
    if(n != NULL){
      printf("%c\n", n->letter);
      Insert(n->left, &q);
      Insert(n->right, &q);
    }
  }
}

Node *AllocateNode(char s){

  Node *p;
  p = (Node*)malloc(sizeof(Node));
  if(p == NULL){
    printf("Cannot Allocate Node\n");
    exit (2);
  }
  p->letter = s;
  p->left = NULL;
  p->right = NULL;

  return p;
}
