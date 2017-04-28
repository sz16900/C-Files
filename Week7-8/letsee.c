#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TILE 3

struct node{
  char  puzzle[TILE][TILE];
  struct node *next;
  struct node *parent;
  int position;
};
typedef struct node Node;

Node *AllocateNode(char s[TILE][TILE], int x);
int valid(int x, int y);
int isReady(char arr[TILE][TILE]);
int isValidFile(char c);
void copyArray(char board[TILE][TILE], char board_copy[TILE][TILE]);
int fillUpArray(char board[TILE][TILE], FILE *fp);
int checkSize(FILE *fp);
int arrayCompare(char a[TILE][TILE], char b[TILE][TILE]);
int walkArray(char puzzle[TILE][TILE], Node *start);
int isReady(char arr[TILE][TILE]);

int main(int argc, char **argv){

  int i, j, k, end = 0, position = 0;
  Node *head, *current, *start;
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
    start = head = current = AllocateNode(puzzle, position);
    position++;

    while(end == 0){

      for(i = 0; i < TILE; i++){
        for(j = 0; j < TILE; j++){

          if((valid(i, j+1) == 1) && head->puzzle[i][j] == ' '){ /*RIGHT*/
            /*SWAP*/
            puzzle[i][j] = head->puzzle[i][j+1];
            puzzle[i][j+1] = ' ';
            if(isReady(puzzle)){
              current->next = AllocateNode(puzzle, position);
              current = current->next;
              current->parent = head;
              end = 1; /*I THINK I NEED TO SEE HOW I CAN GET OUT OF THE WHOLE LOOP*/
            }
            /*Walk through the array to find similar puzzle*/
            if(end == 0){
              if((walkArray(puzzle, start)) < 1){
              current->next = AllocateNode(puzzle, position);
              position++;
              current = current->next;
              current->parent = head;
              }
            }
            /*head->next = current; current because we dont want to loose it*/
            copyArray(head->puzzle, puzzle);

          }

          if((valid(i+1, j) == 1) && head->puzzle[i][j] == ' '){ /*DOWN*/
            /*SWAP*/
            puzzle[i][j] = head->puzzle[i+1][j];
            puzzle[i+1][j] = ' ';
            if(isReady(puzzle)){
              current->next = AllocateNode(puzzle, position);
              current = current->next;
              current->parent = head;
              end = 1; /*I THINK I NEED TO SEE HOW I CAN GET OUT OF THE WHOLE LOOP*/
            }
            /*Walk through the array to find similar puzzle*/
            if(end == 0){
              if((walkArray(puzzle, start)) < 1){
              current->next = AllocateNode(puzzle, position);
              position++;
              current = current->next;
              current->parent = head;
              }
            }
            /* i dont think we want to do this head->next = current; current because we dont want to loose it*/
            copyArray(head->puzzle, puzzle);
          }

          if((valid(i, j-1) == 1) && head->puzzle[i][j] == ' '){ /*LEFT*/
            /*SWAP*/
            puzzle[i][j] = head->puzzle[i][j-1];
            puzzle[i][j-1] = ' ';
            if(isReady(puzzle)){
              current->next = AllocateNode(puzzle, position);
              current = current->next;
              current->parent = head;
              end = 1; /*I THINK I NEED TO SEE HOW I CAN GET OUT OF THE WHOLE LOOP*/
            }
            /*Walk through the array to find similar puzzle*/
            if(end == 0){
              if((walkArray(puzzle, start)) < 1){
              current->next = AllocateNode(puzzle, position);
              position++;
              current = current->next;
              current->parent = head;
              }
            }
            /* i dont think we want to do this  head->next = current; current because we dont want to loose it*/
            copyArray(head->puzzle, puzzle);
            }

          if((valid(i-1, j) == 1) && head->puzzle[i][j] == ' '){ /*UP*/
            /*SWAP*/
            puzzle[i][j] = head->puzzle[i-1][j];
            puzzle[i-1][j] = ' ';
            if(isReady(puzzle)){
              current->next = AllocateNode(puzzle, position);
              current = current->next;
              current->parent = head;
              end = 1; /*I THINK I NEED TO SEE HOW I CAN GET OUT OF THE WHOLE LOOP*/
            }
            /*Walk through the array to find similar puzzle*/
            if(end == 0){
              if((walkArray(puzzle, start)) < 1){
              current->next = AllocateNode(puzzle, position);
              position++;
              current = current->next;
              current->parent = head;
              }
            }
            /* i dont think we want to do this  head->next = current; /*current because we dont want to loose it*/
            copyArray(head->puzzle, puzzle);
            }

        }
      }

      head = head->next;
      copyArray(head->puzzle, puzzle);
    }


    while(start != NULL){
      for(i = 0; i < TILE; i++){
        for(j = 0; j < TILE; j++){
          printf("%c", start->puzzle[i][j]);
        }
        printf("\n");
      }
      printf("My position is: %d\n", start->position);
      start = start->next;
      printf("\n");

    }

  }
  return 0;
}

Node *AllocateNode(char s[TILE][TILE], int x){

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
  p->parent = NULL;
  p->position = x;

  return p;
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

  if(c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6'
    && c != '7' && c != '8' && c!= ' ' && c!= '\n'){
    return 1;
  }
  else{
    return 0;
  }

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

int isReady(char arr[TILE][TILE]){
    if(arr[0][0]=='1' && arr[0][1]=='2' && arr[0][2]=='3' &&
            arr[1][0]=='4' && arr[1][1]=='5' && arr[1][2]=='6' &&
            arr[2][0]=='7' && arr[2][1]=='8'){
        return 1;
    }
    else return 0;
}

void printResult(Node *current){

  NCURS_Simplewin sw;
  Neill_NCURS_Init(&sw);
  Neill_NCURS_CharStyle(&sw, " ", COLOR_BLACK, COLOR_BLACK, A_NORMAL);

do{
  while(current != NULL){
   /* Wait for mouse click, or ESC key */
   Neill_NCURS_PrintArray(&current->puzzle[0][0], TILE, TILE, &sw);
   Neill_NCURS_Delay(1000);
   Neill_NCURS_Events(&sw);
   current = current->parent;
 }
}while(!sw.finished);

/* Call this function if we exit() anywhere in the code */
atexit(Neill_NCURS_Done);
exit(EXIT_SUCCESS);
}
