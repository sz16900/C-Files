#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 20

struct node{
    char num[MAXNAME];
    struct node *next;
  };
typedef struct node Node;


void printList(Node *np);
Node *makeList(void);
Node *makeNode(char *n);

int main(int argc, char **argv){
    Node *np, *list, *last;
    list = NULL;
    char name[MAXNAME];
    FILE *fp;

    if( argc==2 ){
      if((fp = fopen(argv[1], "r")) == NULL){
        printf("ERROR: Incorrect usage, try e.g. %s 34words.txt\n", argv[0]);
        return 1;
      }
      fscanf(fp, "%s", name);
        list = np = makeNode(name);
      while(fscanf(fp, "%s", name) == 1){
        np = makeNode(name);
        if(list == NULL){
          list = np;
        }
        else {
          last->next = np;
        }
        last = np;
      }
      fclose(fp);
    }

    printList(list);
    printf("\n");
    return 0;
}

void printList(Node *np) {
    while(np != NULL) {
        printf("%s\n", np->num);
        np = np->next;
    }
}

Node *makeNode(char *n) {
    Node *np = (Node *)malloc(sizeof(Node));
    strcpy(np->num, n);
    np->next = NULL;
    return np;
}
