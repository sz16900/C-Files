/*A complete working C program to demonstrate all insertion methods on Linked List*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 10

/*A linked list node*/
struct node
{
  char data[MAXNAME];
  struct node *next;
};

/* Given a reference (pointer to pointer) to the head of a list and
   an int, inserts a new node on the front of the list. */
void push(struct node** head_ref, char *new_data)
{
    /* 1. allocate node */
    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    /* 2. put in the data  */
    strcpy(new_node->data, new_data);

    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);

    /* 4. move the head to point to the new node */
    (*head_ref)    = new_node;
}

/* Given a node prev_node, insert a new node after the given
   prev_node */
void insertAfter(struct node* prev_node, char *new_data)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL)
    {
      printf("the given previous node cannot be NULL");
      return;
    }

    /* 2. allocate new node */
    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    /* 3. put in the data  */
    strcpy(new_node->data, new_data);


    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;

    /* 5. move the next of prev_node as new_node */
    prev_node->next = new_node;
}

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void append(struct node** head_ref, char *new_data)
{
    /* 1. allocate node */
    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    struct node *last = *head_ref;  /* used in step 5*/

    /* 2. put in the data  */
    strcpy(new_node->data, new_data);


    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}

/* This function prints contents of linked list starting from head*/
void printList(struct node *node)
{
  while (node != NULL)
  {
     printf("%s\n", node->data);
     node = node->next;
  }
}

/* Driver program to test above functions*/
int main(int argc, char **argv)
{

  char name[MAXNAME];
  FILE *fp;

  /* Start with the empty list */
  struct node* head = NULL;
  struct node* current;



  if( argc==2 ){
    if((fp = fopen(argv[1], "r")) == NULL){
      printf("ERROR: Incorrect usage, try e.g. %s 34words.txt\n", argv[0]);
      return 1;
    }
    if(fscanf(fp, "%s", name) == 1){
      append(&head, name);
      current = head;
      fscanf(fp, "%s", name);
      push(&head, name);
      current = head->next;
      while(fscanf(fp, "%s", name) != EOF){
        if((strcmp(name, head->data) > 0) && strcmp(name, current->data) < 0){
          insertAfter(head->next, name);
        }
        else if(strcmp(name, head->next) < 0){
          insertAfter(head, name);
        }
        else{
          insertAfter(head, name);

        }
      }


    }
    else{
      return 1;
    }



  printList(head);

    fclose(fp);
  }
  return 0;
}
