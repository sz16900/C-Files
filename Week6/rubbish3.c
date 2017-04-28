#include <stdio.h>
#include <stdlib.h>

struct node{
    int num;
    struct node *next;
  };
typedef struct node Node;


void printList(Node *np);
Node *makeList(void);
Node *makeNode(int n);
Node *sortList(Node *list);

int main(void) {
    Node *list;
    printf("Enter numbers for the list (0 to end)\n");
    list = makeList();
    printList(list);
    list = sortList(list);
    printList(list);
    return 0;
}

Node *makeList(void) {
    Node *np, *top, *last;
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
    return top;

    printf("%d here\n", top->num);
}


void printList(Node *np) {
    while(np != NULL) {
        printf("%d\n", np->num);
        np = np->next;
    }
}

Node *makeNode(int n) {
    Node *np = (Node *)malloc(sizeof(Node));
    np->num = n;
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
        if(curr->num > largest->num) {
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
