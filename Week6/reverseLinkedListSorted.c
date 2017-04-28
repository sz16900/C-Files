#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int num;
    struct node *next;
} Node, *NodePtr;

void printList(NodePtr np);
NodePtr makeList(void);
NodePtr makeNode(int n);
NodePtr sortList(NodePtr list);

int main(void) {
    NodePtr list;
    printf("Enter numbers for the list (0 to end)\n");
    list = makeList();
    printList(list);
    list = sortList(list);
    printList(list);
    return 0;
}

NodePtr makeList(void) {
    NodePtr makeNode(int), np, top, last;
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
}


void printList(NodePtr np) {
    while(np != NULL) {
        printf("%d\n", np->num);
        np = np->next;
    }
}

NodePtr makeNode(int n) {
    NodePtr np = (NodePtr)malloc(sizeof(Node));
    np->num = n;
    np->next = NULL;
    return np;
}


NodePtr sortList(NodePtr list)
{

if(list == NULL || list->next == NULL)
    return list;


NodePtr curr, largest, largestPrev, prev;
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

NodePtr tmp;
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
