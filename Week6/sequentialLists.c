#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 20

struct node{
  char name[MAXNAME];
};
typedef struct node Node;

int FillNode(Node l[], char *s, int n);
void PrintList(Node l[], int size);
void DelElem(Node l[], int n, int *size); /* I still dont know how to call this */

int main(void){

  char name[MAXNAME];
  int current;
  Node list[100];

  printf("Enter the first name\n");
  if(scanf("%s", name) == 1){
    current = FillNode(list, name, 0);
  }
  else{
    return 1;
  }

  printf("Enter more names: ");
  while(scanf("%s", name) == 1){
    current = FillNode(list, name, current + 1);
  }
  ++current;
  PrintList(list, current);


  return 0;
}

int FillNode(Node l[], char *s, int n){

  strcpy(l[n].name, s);

  return n;
}

void PrintList(Node l[], int size){

  int i;

  for(i = 0; i < size; i++){
    printf("Name: %s\n", l[i].name);
  }
  printf("END\n");
}

void DelElem(Node l[], int n, int *size){

  int i;

  for(i = n + 1; i < *size; i++){
    *size = *size - 1;
  }
}
