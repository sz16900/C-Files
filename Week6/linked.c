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
void *sortList(Node *list);



int main(int argc, char **argv){

  char name[MAXNAME];
  Node *start, *current;
  FILE *fp;

  if( argc==2 ){
    if((fp = fopen(argv[1], "r")) == NULL){
      printf("ERROR: Incorrect usage, try e.g. %s 34words.txt\n", argv[0]);
      return 1;
    }
    if(fscanf(fp, "%s", name) == 1){
      start = current = AllocateNode(name);
    }
    else{
      return 1;
    }
    while(fscanf(fp, "%s", name) == 1){
      current->next = AllocateNode(name);
      current = current->next;

    }
    fclose(fp);
    PrintList(start);
    sortList(start);
    PrintList(start);
    destroyEntry(start);
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


void *sortList(Node *list){

  Node *curr, *next, *prev, *endlist, *tmp;
  endlist = NULL;

  while(endlist != list->next){
    prev = curr = list;
    next = curr->next;

    while(curr != endlist){
      if (strcmp(list->name, list->next->name) > 0){
        if(curr == list){
          tmp = next->next;
          next->next = curr;
          curr->next = tmp;

          list = next;
          prev = next;
        }
        else{
          tmp = next->next;
          next->next = curr;
          curr->next = tmp;

          prev->next = next;
          prev = next;
        }
      }
      else{
        prev = curr;
        curr = curr->next;
      }
      next = curr->next;
      if(next == endlist){
        endlist = curr;
      }
    }
  }


}
