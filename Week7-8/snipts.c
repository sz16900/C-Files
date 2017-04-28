#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE 20000
#define TILE 2

struct node{
  int  puzzle[TILE][TILE];
  struct node *next;
};
typedef struct node Node;

struct queue{
  Node *n[MAX_QUEUE];
  int front;
  int back;
};
typedef struct queue Queue;

Node *AllocateNode(int s[TILE][TILE]);
void Insert(Node *t, Queue *q);
void InitialiseQueue(Queue *q);
int valid(int a[TILE][TILE], int x, int y);
int swap(int x, int y);


int main(void){

  int i, j, k;
  Node *start;
  Queue q;
  int original[TILE][TILE] =  {{0,1},{3,2}};
  int puzzle[TILE][TILE] =  {{0,1},{3,2}};
  int puzzle_copy[TILE][TILE] =  {{0,1},{3,2}};

  InitialiseQueue(&q);

  for(i = 0; i < TILE; i++){
    for(j = 0; j < TILE; j++){
      if(valid(puzzle, i, j+1) && puzzle[i][j] == 0){ /*RIGHT*/
        /*SWAP*/
        puzzle_copy[i][j] = puzzle[i][j+1];
        puzzle_copy[i][j+1] = 0;
        /*makes a copy*/
        for(i = 0; i < TILE; i++){
          for(j = 0; j < TILE; j++){
            puzzle[i][j] = puzzle_copy[i][j];
          }
        }
        start = AllocateNode(puzzle);
        Insert(start, &q);
      }
      /*makes a copy to original*/
      for(i = 0; i < TILE; i++){
        for(j = 0; j < TILE; j++){
          puzzle[i][j] = original[i][j];
          puzzle_copy[i][j] = original[i][j];
        }
      }
      i = 0;
      j = 0;

      if(valid(puzzle, i+1, j) && puzzle[i][j] == 0){ /*DOWN*/
        puzzle_copy[i][j] = puzzle[i+1][j];
        puzzle_copy[i+1][j] = 0;
        /*makes a copy*/
        for(i = 0; i < TILE; i++){
          for(j = 0; j < TILE; j++){
            puzzle[i][j] = puzzle_copy[i][j];
          }
        }
        start = AllocateNode(puzzle);
        Insert(start, &q);
      }
      /*makes a copy to original*/
      for(i = 0; i < TILE; i++){
        for(j = 0; j < TILE; j++){
          puzzle[i][j] = original[i][j];
          puzzle_copy[i][j] = original[i][j];
        }
      }
      i = 0;
      j = 0;

      if(valid(puzzle, i, j-1) && puzzle[i][j] == 0){ /*LEFT*/
        puzzle_copy[i][j] = puzzle[i][j-1];
        puzzle_copy[i][j-1] = 0;
        /*makes a copy*/
        for(i = 0; i < TILE; i++){
          for(j = 0; j < TILE; j++){
            puzzle[i][j] = puzzle_copy[i][j];
          }
        }
        start = AllocateNode(puzzle);
        Insert(start, &q);
      }
      /*makes a copy to original*/
      for(i = 0; i < TILE; i++){
        for(j = 0; j < TILE; j++){
          puzzle[i][j] = original[i][j];
          puzzle_copy[i][j] = original[i][j];
        }
      }
      i = 0;
      j = 0;

      if(valid(puzzle, i-1, j) && puzzle[i][j] == 0){ /*UP*/
        puzzle_copy[i][j] = puzzle[i-1][j];
        puzzle_copy[i-1][j] = 0;
        /*makes a copy*/
        for(i = 0; i < TILE; i++){
          for(j = 0; j < TILE; j++){
            puzzle[i][j] = puzzle_copy[i][j];
          }
        }
        start = AllocateNode(puzzle);
        Insert(start, &q);
      }
      /*makes a copy to original*/
      for(i = 0; i < TILE; i++){
        for(j = 0; j < TILE; j++){
          puzzle[i][j] = original[i][j];
          puzzle_copy[i][j] = original[i][j];
        }
      }
    }
  }

  while(q.n[k] != NULL){
    for(i=0; i<TILE; i++){
      for(j=0; j<TILE; j++){
      printf("%d", q.n[k]->puzzle[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    k++;
  }


    /*for(i=0; i<TILE; i++){
      for(j=0; j<TILE; j++){
      printf("%d", q.n[1]->puzzle[i][j]);
      }
      printf("\n");
    }*/


  return 0;
}

Node *AllocateNode(int s[TILE][TILE]){

  Node *p;
  int i, j;

  p = (Node*)malloc(sizeof(Node));

  if(p == NULL){
    printf("Cannot Allocate Node\n");
    exit (2);
  }

  for(i=0; i<TILE; i++){
    for(j=0; j<TILE; j++){
    p->puzzle[i][j] = s[i][j];
    }
  }
  p->next = NULL;

  return p;
}

void Insert(Node *t, Queue *q){
  q->n[q->back] = t;
  q->back = (q->back + 1) % MAX_QUEUE;
}

void InitialiseQueue(Queue *q){
  q->front = 0;
  q->back = 0;
}

int valid(int a[TILE][TILE], int x, int y)
{

   if((x<0)||(y<0)){
      return 0;
   }
   if((x>=TILE)||(y>=TILE)){
      return 0;
   }
   return 1;
}

int swap(int x, int y){
    int temp;
    temp = x;
    x = y;
    y = temp;
    return x;
    return y;
}
