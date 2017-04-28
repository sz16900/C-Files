curr = list;
largest = list;
prev = list;
largestPrev = list;
while(curr != NULL) {
        if(strcmp(curr->name, largest->name) < 0) {
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
