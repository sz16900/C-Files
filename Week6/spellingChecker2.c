#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 20

struct node{
  char name[MAXNAME];
  struct node *next; /*point to something of struct node*/
};

typedef struct node Node;

Node *AllocateNode(char *s); /*returns a pointer to the space we are allowed to use*/
void PrintList(Node *l);
void destroyEntry(Node *entry);
void push(Node *head, char *s);



int main(int argc, char **argv){

  char name[MAXNAME];
  Node *list, *current;
  FILE *fp;


  if( argc==2 ){
    if((fp = fopen(argv[1], "r")) == NULL){
      printf("ERROR: Incorrect usage, try e.g. %s 34words.txt\n", argv[0]);
      return 1;
    }
    if(fscanf(fp, "%s", name) == 1){
      list = current = AllocateNode(name);
    }
    else{
      return 1;
    }

    while(fscanf(fp, "%s", name) == 1){
      current->next = AllocateNode(name);
      current = current->next;
      }

      /*
      function passes in my list (start) and tmp node insert tmp node where in the list
      current->next = AllocateNode(name);
      current = current->next;
      */

    fclose(fp);

    PrintList(list);

    destroyEntry(list);
  }


  return 0;
}

Node *AllocateNode(char *s){

  Node *p;

  p = (Node*)malloc(sizeof(Node));

  if(p == NULL){
    printf("Cannot Allocate Node\n");
    exit (2);
  }

  strcpy(p->name, s);
  p->next = NULL;

  return p;
}

void PrintList(Node *l){

  printf("\n");
  do{
    printf("%s\n", l->name);
    l = l->next;
  }while(l != NULL);
  printf("\n");

}

void destroyEntry(Node *entry){
    free(entry);
}
