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
Node *InList(Node *n, char *s); /* Searching a List */
void printListRecursive(Node *l); /* Printing a List Recursively */
Node *InListRecursive(Node *n, char *s); /* Searching a List Recursively*/
Node *DeleteNode(Node *start, char *s); /* Delete an element in the list */



int main(void){

  char name[MAXNAME];
  Node *start, *current;

  printf("Enter the first name: ");
  if(scanf("%s", name) == 1){
    start = current = AllocateNode(name);
  }
  else{
    return 1;
  }

  printf("Enter more names: ");
  while(scanf("%s", name) == 1){
    current->next = AllocateNode(name);
    current = current->next;
  }

  DeleteNode(start, "bob");
  PrintList(start);
  printf("\n");
  printf("%p\n", InList(start, "jack"));
  printf("%p\n", InList(start, "bob"));
  printf("%p\n", InList(start, "joe"));
  printf("\n");

  printListRecursive(start);
  printf("\n");
  printf("%p\n", InListRecursive(start, "jack"));
  printf("%p\n", InListRecursive(start, "bob"));
  printf("%p\n", InListRecursive(start, "joe"));
  printf("\n");

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
    printf("Name : %s\n", l->name);
    l = l->next;
  }while(l != NULL);
  printf("END\n");

}

Node *InList(Node *n, char *s){

  do {
    if(strcmp(n->name, s) == 0){
      return n;
    }
    n = n->next;
  }while(n != NULL);

  return NULL;
}

void printListRecursive(Node *l){

  /* Recursive Base-Case */
  if(l == NULL) return ;

  printf("Name : %s\n", l->name);
  printListRecursive(l->next);

  }

  Node *InListRecursive(Node *n, char *s){

    /* Recursive Base-Case */
    if(n == NULL) return NULL;

    if(strcmp(n->name, s) == 0){
      return n;
    }

    return InListRecursive(n->next,s);
  }

  Node *DeleteNode(Node *start, char *s){

    Node *prev, *l;

    /* 1st in list ? */
    if(!strcmp(start->name,s)){
      return start->next;
    }

    l = start;
    do{
      prev = l;
      l = l->next;
      if(strcmp(l->name, s) == 0){
        prev->next = l->next;
        return start;
      }
    }while(l != NULL);

    return start;
  }
