#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "neillncurses.h"

#define TILE 3
#define BORDERS 10
#define SIZE 40
#define DELAY 1000
/*these are enough bytes to accomodate a 3X3 puzzle*/
#define MAX_FILE_SIZE 13

struct node{
  char  puzzle[TILE][TILE];
  struct node *next;
  struct node *parent;
};
typedef struct node Node;

Node *AllocateNode(char s[TILE][TILE]);
int valid(int x, int y);
int isReady(char arr[TILE][TILE]);
int isValidFile(char c);
void copyArray(char board[TILE][TILE], char board_copy[TILE][TILE]);
int fillUpArray(char board[TILE][TILE], FILE *fp);
int checkSize(FILE *fp);
int arrayCompare(char a[TILE][TILE], char b[TILE][TILE]);
int walkArray(char puzzle[TILE][TILE], Node *start);
int isReady(char arr[TILE][TILE]);
void printResult(Node *current);
void freeList(Node *start);
Node *insert(Node *current, Node *head, char puzzle[TILE][TILE]);
void runProgram(char puzzle[TILE][TILE]);
int isSolvable(char puzzle[TILE][TILE]);
int isRepeated(char puzzle[TILE][TILE]);

int main(int argc, char **argv){

  FILE *fp;
  char puzzle[TILE][TILE];

  if( argc==2 ){
    if((fp = fopen(argv[1], "r")) == NULL){
      printf("ERROR: Something is wrong with your file \n");
      return 1;
    }
    else if(fillUpArray(puzzle, fp) == 1 || checkSize(fp) == 1 ||
    isRepeated(puzzle) == 1){
      printf("ERROR: Something is wrong with your file \n");
      return 1;
    }

  
    runProgram(puzzle);

    fclose(fp);
  }

  return 0;
}

Node *AllocateNode(char s[TILE][TILE]){

  Node *p;
  int i;
  p = (Node*)malloc(sizeof(Node));

  if(p == NULL){
    printf("Cannot Allocate Node\n");
    exit (2);
  }

  for(i=0; i<TILE; i++){
    memcpy(p->puzzle[i], s[i], sizeof(s[0]));
  }
  p->next = NULL;
  p->parent = NULL;

  return p;
}

int checkSize(FILE *fp){

  int size = 0;

  fseek(fp, 0L, SEEK_END);
  size = ftell(fp);
  rewind(fp);
  if(size > MAX_FILE_SIZE /*this is the number of bytes in a file we should care for*/){
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
      if(c == '\n' || c == '\r'){
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

  int i;

  for(i = 0; i < TILE; i++){
    memcpy(&board_copy[i], &board[i], sizeof(board[i]));
  }

}

int isValidFile(char c){

  if(c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6'
    && c != '7' && c != '8' && c!= ' ' && c!= '\n' && '\r'){
    return 1;
  }
  else{
    return 0;
  }

}

int valid(int x, int y){

   if((x<0)||(y<0)){
      return 0;
   }
   if((x>=TILE)||(y>=TILE)){
      return 0;
   }

   return 1;
}

int walkArray(char puzzle[TILE][TILE], Node *start){

  while(start != NULL){
    if((arrayCompare(puzzle, start->puzzle))){
      return 1;
    }
    start = start->next;
  }

  return 0;
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

int isReady(char puzzle[TILE][TILE]){

  if(puzzle[0][0]=='1' && puzzle[0][1]=='2' && puzzle[0][2]=='3' &&
  puzzle[1][0]=='4' && puzzle[1][1]=='5' && puzzle[1][2]=='6' &&
  puzzle[2][0]=='7' && puzzle[2][1]=='8'){
    return 1;
  }

  else {
    return 0;
  }

}

void printResult(Node *current){

  int i, j, k, l;
  char a[SIZE][SIZE];
  NCURS_Simplewin sw;

  for(i=0; i<SIZE; i++){
    for(j=0; j<SIZE; j++){
      a[i][j] = '#';
    }
  }

  /* this arranges the list from front to back */
  while(current->parent != NULL){
    current->parent->next = current;
    current = current->parent;
  }

  Neill_NCURS_Init(&sw);
  Neill_NCURS_CharStyle(&sw, " ", COLOR_RED, COLOR_RED, A_NORMAL);
  Neill_NCURS_CharStyle(&sw, "#", COLOR_YELLOW, COLOR_YELLOW, A_NORMAL);
  Neill_NCURS_CharStyle(&sw, "12345678", COLOR_WHITE, COLOR_BLUE  , A_NORMAL);

do{
    /*fill up a the array with the puzzle to display borders*/
    for(i=BORDERS , k=0; i<=SIZE-BORDERS && k<TILE; i=i+BORDERS , k++){
      for(j=BORDERS , l=0; j<=SIZE-BORDERS && l<TILE; j=j+BORDERS , l++){
        a[i][j] = current->puzzle[k][l];
      }
    }
    Neill_NCURS_PrintArray(&a[0][0], SIZE, SIZE, &sw);
    Neill_NCURS_Delay(DELAY);
    Neill_NCURS_Events(&sw);
    current = current->next;
  }while(!sw.finished && current != NULL);

  atexit(Neill_NCURS_Done);
  exit(EXIT_SUCCESS);

}

void freeList(Node *start){
  Node *q;

  while(q != NULL){
    q = start->next;
    free(start);
    start = q;
  }

}

Node *insert(Node *current, Node *head, char puzzle[TILE][TILE]){

  current->next = AllocateNode(puzzle);
  current = current->next;
  current->parent = head;
  return current;

}

void runProgram(char puzzle[TILE][TILE]){

  int i, j, count = 0, end = 0;
  Node *head, *current, *start;
  start = head = current = AllocateNode(puzzle);

  while(!end){

    for(i = 0; i < TILE; i++){
      for(j = 0; j < TILE; j++){

        if((valid(i, j+1) == 1) && head->puzzle[i][j] == ' '){ /*RIGHT*/
          /*SWAP*/
          puzzle[i][j] = head->puzzle[i][j+1];
          puzzle[i][j+1] = ' ';
          if(isReady(puzzle)){
            current = insert(current, head, puzzle);
            end = 1;
          }
          if(end == 0){
            if((walkArray(puzzle, start)) < 1){
              current = insert(current, head, puzzle);
            }
          }
          copyArray(head->puzzle, puzzle);
        }

        if((valid(i+1, j) == 1) && head->puzzle[i][j] == ' '){ /*DOWN*/
          /*SWAP*/
          puzzle[i][j] = head->puzzle[i+1][j];
          puzzle[i+1][j] = ' ';
          if(isReady(puzzle)){
            current = insert(current, head, puzzle);
            end = 1;
          }
          if(!end){
            if((walkArray(puzzle, start)) < 1){
              current = insert(current, head, puzzle);
            }
          }
          copyArray(head->puzzle, puzzle);
        }

        if((valid(i, j-1) == 1) && head->puzzle[i][j] == ' '){ /*LEFT*/
          /*SWAP*/
          puzzle[i][j] = head->puzzle[i][j-1];
          puzzle[i][j-1] = ' ';
          if(isReady(puzzle)){
            current = insert(current, head, puzzle);
            end = 1;
          }
          if(end == 0){
            if((walkArray(puzzle, start)) < 1){
              current = insert(current, head, puzzle);
            }
          }
          copyArray(head->puzzle, puzzle);
          }

        if((valid(i-1, j) == 1) && head->puzzle[i][j] == ' '){ /*UP*/
          /*SWAP*/
          puzzle[i][j] = head->puzzle[i-1][j];
          puzzle[i-1][j] = ' ';
          if(isReady(puzzle)){
            current = insert(current, head, puzzle);
            end = 1;
          }
          if(end == 0){
            if((walkArray(puzzle, start)) < 1){
              current = insert(current, head, puzzle);
            }
          }
          copyArray(head->puzzle, puzzle);
        }

      }
    }

    head = head->next;
    copyArray(head->puzzle, puzzle);
    count++;
  }

  printResult(current);
  freeList(start);
}

int isSolvable(char puzzle[TILE][TILE]){

  int i, j, up=0, inversions=0;
  int x[9];
  char copy[TILE][TILE];

  for(i = 0; i < TILE; i++){
    for(j = 0; j < TILE; j++){
      if(puzzle[i][j] == ' '){
        copy[i][j] = '0';
      }
      else{
        copy[i][j] = puzzle[i][j];
      }
    }
  }

  for(i = 0; i < TILE; i++){
    for(j = 0; j < TILE; j++){
      x[up] = (int)copy[i][j];
      up++;
    }
  }

  for(i = 0; i < 9-1; i++){
    for(j = i+1; j < 9; j++){
      if(x[j] && x[i] && x[i] > x[j]){
        inversions++;
      }
    }
  }

  if(inversions % 2 == 1){
    return 0;
  }
  else{
    return 1;
  }

}

int isRepeated(char puzzle[TILE][TILE]){

  int i, j, up=0;
  int x[9];
  int count = sizeof(x) / sizeof(x[0]);

  for(i = 0; i < TILE; i++){
    for(j = 0; j < TILE; j++){
      x[up] = puzzle[i][j];
      up++;
    }
  }

  for (i = 0; i < count - 1; i++) {
      for (j = i + 1; j < count; j++) {
          if (x[i] == x[j]) {
              return 1;
          }
      }
  }

  return 0;
}
