#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE 20000
#define TILE 2

struct node{
  char  puzzle[TILE][TILE];
  struct node *next;
};
typedef struct node Node;

struct queue{
  Node *n[MAX_QUEUE];
  int front;
  int back;
};
typedef struct queue Queue;

Node *AllocateNode(char s[TILE][TILE]);
void Insert(Node *t, Queue *q);
void InitialiseQueue(Queue *q);
int valid(int x, int y);
int swap(int x, int y);


int main(void){

  int i, j, k, s, t, u = 0, end = 0, sum = 0;
  Node *start, *current, *head;
  Queue q;
  char puzzle[TILE][TILE] =  {{'0','2'},{'1','3'}};
  char original[TILE][TILE] =  {{'0','2'},{'1','3'}}; /*needs to be updated to next array elem*/

  InitialiseQueue(&q);
  head = start = current = AllocateNode(puzzle);
  Insert(start, &q);

while(end == 0){
  for(i = 0; i < TILE; i++){
    for(j = 0; j < TILE; j++){

      if((valid(i, j+1) == 1) && q.n[u]->puzzle[i][j] == '0'){ /*RIGHT*/
        /*SWAP*/
        puzzle[i][j] = q.n[u]->puzzle[i][j+1];
        puzzle[i][j+1] = '0';
        /*Walk through the list to find similar puzzle*/
        while(start != NULL){
            for(s = 0; s < TILE; s++){
                if(strcmp(start->puzzle[s], puzzle[s]) == 0){
                  sum++;
                }
            }
            if(sum == 0){
              start->next = AllocateNode(puzzle); /*is there a problem with current and start?*/
              start = start->next;
              Insert(start, &q);
            }
            start = start->next;
            sum = 0;
        }
        start = head;
        /*makes a copy back to the original*/
        for(s = 0; s < TILE; s++){
          for(t = 0; t < TILE; t++){
            puzzle[s][t] = original[s][t];
          }
        }
      }

      if((valid(i+1, j) == 1) && q.n[u]->puzzle[i][j] == '0'){ /*DOWN*/
        puzzle[i][j] = q.n[u]->puzzle[i+1][j];
        puzzle[i+1][j] = '0';
        /*Walk through the list to find similar puzzle*/
        while(start != NULL){
            for(s = 0; s < TILE; s++){
                if(strcmp(start->puzzle[s], puzzle[s]) == 0){
                  sum++;
                }
            }
            if(sum == 0){
              start->next = AllocateNode(puzzle); /*is there a problem with current and start?*/
              start = start->next;
              Insert(start, &q);
            }
            start = start->next;
            sum = 0;
        }
        start = head;
        /*makes a copy*/
        for(s = 0; s < TILE; s++){
          for(t = 0; t < TILE; t++){
            puzzle[s][t] = original[s][t];
          }
        }
      }

      if((valid(i, j-1) == 1) && q.n[u]->puzzle[i][j] == '0'){ /*LEFT*/
        puzzle[i][j] = q.n[u]->puzzle[i][j-1];
        puzzle[i][j-1] = '0';
        /*Walk through the list to find similar puzzle*/
        while(start != NULL){
            for(s = 0; s < TILE; s++){
                if(strcmp(start->puzzle[s], puzzle[s]) == 0){
                  sum++;
                }
            }
            if(sum == 0){
              start->next = AllocateNode(puzzle); /*is there a problem with current and start?*/
              start = start->next;
              Insert(start, &q);
            }
            start = start->next;
            sum = 0;
        }
        start = head;
        /*makes a copy*/
        for(s = 0; s < TILE; s++){
          for(t = 0; t < TILE; t++){
            puzzle[s][t] = original[s][t];
          }
        }
      }

      if((valid(i-1, j) == 1) && q.n[u]->puzzle[i][j] == '0'){ /*UP*/
        puzzle[i][j] = q.n[u]->puzzle[i-1][j];
        puzzle[i-1][j] = '0';
        /*Walk through the list to find similar puzzle*/
        while(start != NULL){
            for(s = 0; s < TILE; s++){
                if(strcmp(start->puzzle[s], puzzle[s]) == 0){
                  sum++;
                }
            }
            if(sum == 0){
              start->next = AllocateNode(puzzle); /*is there a problem with current and start?*/
              start = start->next;
              Insert(start, &q);
            }
            start = start->next;
            sum = 0;
        }
        start = head;
        /*makes a copy*/
        for(s = 0; s < TILE; s++){
          for(t = 0; t < TILE; t++){
            puzzle[s][t] = original[s][t];
          }
        }
      }
    }
  }

  u++;

  /*update the original*/
    for(s = 0; s < TILE; s++){
      for(t = 0; t < TILE; t++){
        puzzle[s][t] = q.n[u]->puzzle[s][t];
        original[s][t] = q.n[u]->puzzle[s][t];

      }
    }

  /* checks to see if it has reached the final state*/
  if(original[0][0]=='1' && original[0][1]=='2' && original[1][0]=='3' &&
          original[1][1]=='0'){
            end = 1;;
          }
}



  while(q.n[k] != NULL){
    for(i=0; i<TILE; i++){
      for(j=0; j<TILE; j++){
      printf("%c", q.n[k]->puzzle[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    k++;
  }

  return 0;
}

Node *AllocateNode(char s[TILE][TILE]){

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

int valid(int x, int y)
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
