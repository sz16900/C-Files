#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE 363000
#define TILE 3

struct node{
  char  puzzle[TILE][TILE];
  int parent;
};
typedef struct node Node;

struct queue{
  Node n[MAX_QUEUE];
  int front;
  int back;
};
typedef struct queue Queue;

void Insert(char s[TILE][TILE], int x, Queue *q);
void InitialiseQueue(Queue *q);
int valid(int x, int y);
int swap(int x, int y);
int arrayCompare(char a[TILE][TILE], char b[TILE][TILE]);
int isReady(char arr[TILE][TILE]);
int isValidFile(char c);
void copyArray(char board[TILE][TILE], char board_copy[TILE][TILE]);
int fillUpArray(char board[TILE][TILE], FILE *fp);
int checkSize(FILE *fp);
void printResult(int the_one, Queue *q);
int walkArray(int array_pos, char puzzle[TILE][TILE], Queue *q);

int main(int argc, char **argv){

  int i, j, k, s, t, n, array_pos = 0, inc = 0, up = 0, copy_found = 0, x = 0, end = 0, the_one;
  Queue q;
  FILE *fp;
  char puzzle[TILE][TILE];
  char original[TILE][TILE];

  if( argc==2 ){
    if((fp = fopen(argv[1], "r")) == NULL){
      printf("ERROR: Something is wrong with your file \n");
      return 1;
    }
    else if(fillUpArray(original, fp) == 1 || checkSize(fp) == 1){
      return 1;
    }

    copyArray(original, puzzle);
    InitialiseQueue(&q);
    Insert(puzzle, array_pos , &q);
    array_pos++;

  while(end == 0){
    for(i = 0; i < TILE; i++){
      for(j = 0; j < TILE; j++){

        if((valid(i, j+1) == 1) && q.n[up].puzzle[i][j] == ' '){ /*RIGHT*/
          /*SWAP*/
          puzzle[i][j] = q.n[up].puzzle[i][j+1];
          puzzle[i][j+1] = ' ';
          if(isReady(puzzle)){
            the_one = array_pos;
            end = 1;
          }
          /*Walk through the array to find similar puzzle*/
          if((walkArray(array_pos, puzzle, &q)) < 1){
              Insert(puzzle, up, &q); /*I NEED TO ALSO STORE THE PARENTS NUMBER*/
              array_pos++;
          }
          /*copy back to original*/
          copyArray(original, puzzle);
        }


        if((valid(i+1, j) == 1) && q.n[up].puzzle[i][j] == ' '){ /*DOWN*/
          puzzle[i][j] = q.n[up].puzzle[i+1][j];
          puzzle[i+1][j] = ' ';
          if(isReady(puzzle)){
            the_one = array_pos;
            end = 1;
          }
          /*Walk through the list to find similar puzzle*/
          if((walkArray(array_pos, puzzle, &q)) < 1){
              Insert(puzzle, up, &q); /*I NEED TO ALSO STORE THE PARENTS NUMBER*/
              array_pos++;
          }
          /*copy back to original*/
          copyArray(original, puzzle);
        }


        if((valid(i, j-1) == 1) && q.n[up].puzzle[i][j] == ' '){ /*LEFT*/
          puzzle[i][j] = q.n[up].puzzle[i][j-1];
          puzzle[i][j-1] = ' ';
          if(isReady(puzzle)){
            the_one = array_pos;
            end = 1;
          }
          /*Walk through the list to find similar puzzle*/
          if((walkArray(array_pos, puzzle, &q)) < 1){
              Insert(puzzle, up, &q); /*I NEED TO ALSO STORE THE PARENTS NUMBER*/
              array_pos++;
          }
          /*copy back to original*/
          copyArray(original, puzzle);
        }

        if((valid(i-1, j) == 1) && q.n[up].puzzle[i][j] == ' '){ /*UP*/
          puzzle[i][j] = q.n[up].puzzle[i-1][j];
          puzzle[i-1][j] = ' ';
          if(isReady(puzzle)){
            the_one = array_pos;
            end = 1;
          }
          /*Walk through the list to find similar puzzle*/
          if((walkArray(array_pos, puzzle, &q)) < 1){
              Insert(puzzle, up, &q); /*I NEED TO ALSO STORE THE PARENTS NUMBER*/
              array_pos++;
          }
          /*copy back to original*/
          copyArray(original, puzzle);
        }
      }
    }
    /*update the original*/
      up++; /*moves to the next parent*/
      for(s = 0; s < TILE; s++){
        for(t = 0; t < TILE; t++){
          puzzle[s][t] = q.n[up].puzzle[s][t];
          original[s][t] = q.n[up].puzzle[s][t];
        }
      }

}

    printResult(the_one, &q);


}
    return 0;
  }

void Insert(char s[TILE][TILE], int x, Queue *q){
  int i, j;

  for(i=0; i<TILE; i++){
    for(j=0; j<TILE; j++){
    q->n[q->back].puzzle[i][j] = s[i][j];
    }
  }
  q->n[q->back].parent = x;
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

int arrayCompare(char a[TILE][TILE], char b[TILE][TILE]){
  int i, j;

  for(i=0; i<TILE; i++){
    for(j=0; j<TILE; j++){
      if((a[i][j]) != (b[i][j])){
        return 0;
      }
    }
  }
  return 1;
}

/*int swap(int x, int y){
    int temp;
    temp = x;
    x = y;
    y = temp;
    return x;
    return y;
}*/

int isReady(char arr[TILE][TILE]){
    if(arr[0][0]=='1' && arr[0][1]=='2' && arr[0][2]=='3' &&
            arr[1][0]=='4' && arr[1][1]=='5' && arr[1][2]=='6' &&
            arr[2][0]=='7' && arr[2][1]=='8'){
        return 1;
    }
    else return 0;
}

int checkSize(FILE *fp){

  int size = 0;

  fseek(fp, 0L, SEEK_END);
  size = ftell(fp);
  rewind(fp);
  if(size != 13 /*this is the number of bytes in a file we should care for*/){
    printf("ERROR. Your file is too large.\n");
    return 1;
  }

  return 0;
}

int fillUpArray(char board[TILE][TILE], FILE *fp){

  int i, j;
  char c;

  for(i = 0; i < TILE; i++){
    for(j = 0; j < TILE; j++){
      /*Checks whether the file is corrupted*/
      if(fscanf(fp, "%c", &c) != 1  || isValidFile(c) == 1){
        printf("ERROR. There seems to be a problem with your file.\n");
        return 1;
      }
      if(c == '\n'){
        j--;
      }
      else{
        board[i][j] = c;
      }
    }
  }

  return 0;
}

void copyArray(char board[TILE][TILE], char board_copy[TILE][TILE]){

  int i, j;

  for(i = 0; i < TILE; i++){
    for(j = 0; j < TILE; j++){
      board_copy[i][j] = board[i][j];
    }
  }
}

int isValidFile(char c){

  if(c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c!= ' ' && c!= '\n'){
    return 1;
  }
  else{
    return 0;
  }

}

void printResult(int the_one, Queue *q){

  int pos[MAX_QUEUE];
  int i, j, k = 0;
  while(the_one != 0){
    pos[k] = the_one;
    the_one = q->n[the_one].parent;
    k++;
  }

  while(k != 0){
    for(i=0; i<TILE; i++){
      for(j=0; j<TILE; j++){
      printf("%c", q->n[pos[k]].puzzle[i][j]);
      }
      printf("\n");
    }
    if(pos[k] == 0){
      printf("IM the Father and thse are my children: \n\n");
    }
    else{
    printf("My parent's position is: %d\n\n", q->n[pos[k]].parent);
  }
    k--;
  }

    for(i=0; i<TILE; i++){
      for(j=0; j<TILE; j++){
      printf("%c", q->n[pos[0]].puzzle[i][j]);
      }
      printf("\n");
    }
    printf("My parent's position is: %d\n\n", q->n[pos[0]].parent);

}

int walkArray(int array_pos, char puzzle[TILE][TILE], Queue *q){
  int inc = 0;

  while(inc <= array_pos){
    if((arrayCompare(puzzle, q->n[inc].puzzle))){
      inc = array_pos;
      return 1;
    }
    inc++;
  }
  return 0;
}
