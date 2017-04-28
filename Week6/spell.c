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
Node *sortList(Node *list);

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
      while(fscanf(fp, "%s", name) == 1){
        np = makeNode(name);
        if(list == NULL)list = np;
        else last->next = np;
        last = np;
      }
      fclose(fp);
    }

    printList(list);
    printf("\n");
    list = sortList(list);
    printList(list);
    return 0;
}

/*Node *makeList(void) {
    Node *np, *list, *last;
    int n;
    top = NULL;
    if(scanf("%d", &n) != 1)n = 0;
    while(n != 0) {
        np = makeNode(n);
        if(top == NULL)top = np;
        else last->next = np;
        last = np;
        if(scanf("%d", &n)!=1)n=0;
    }
    return list;

}*/


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


Node *sortList(Node *list)
{

if(list == NULL || list->next == NULL)
    return list;


Node *curr, *largest, *largestPrev, *prev;
curr = list;
largest = list;
prev = list;
largestPrev = list;
while(curr != NULL) {
        if(strcmp(curr->num, largest->num) > 0) {
            largestPrev = prev;
            largest = curr;
        }
        prev = curr;
        curr = curr->next;

    }

Node *tmp;
if(largest != list)
{
    largestPrev->next = list;
    tmp = list->next;
    list->next = largest->next;
    largest->next = tmp;
}

largest->next = sortList(largest->next);


return largest;
}
