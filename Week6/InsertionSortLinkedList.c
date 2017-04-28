#include <stdio.h>
#include <stdlib.h>

typedef struct Node * nodePtr;

struct Node{

    int data;
    nodePtr next;

};

nodePtr globalHead;

void insertionSort(nodePtr current){

    nodePtr head = current;
    nodePtr insertionPointer = head;

    current = current->next;

    while(current != NULL){

        insertionPointer = head;

        while(insertionPointer->next != current){

            if (insertionPointer->data > current->data){

                int temp = current->data;
                current->data = insertionPointer->data;
                insertionPointer->data = temp;

            }else{

                insertionPointer = insertionPointer->next;

            }

        }

        current = current->next;

    }

}

void push(nodePtr *head, int data){

    nodePtr newNode = (nodePtr) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if ((*head) == NULL){
        *head = newNode;
        globalHead = *head;
    }else{
        (*head)->next = newNode;
        *head = newNode;
    }

}

void printList(nodePtr head){

    nodePtr current = head;

    while(current != NULL){

        printf("%d ",current->data);
        current = current->next;

    }

    printf("\n");

}

int main(void){

    nodePtr head = NULL;

    // linked list is formed from top to bottom fashion
    // push is done in constant time O(1)

    push(&head, 4); // |
    push(&head, 3); // |
    push(&head, 1); // |
    push(&head, 5); // |
    push(&head, 7); // V

    printList(globalHead);

    insertionSort(globalHead);

    printList(globalHead);

    return 0;
}
