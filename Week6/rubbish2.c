void *sortList(Node *list){

  Node *curr, *next, *prev, *endlist, *tmp;
  endlist = NULL;
  int cmp;
  int cmp2;

  while(endlist != list->next){
    prev = curr = list;
    next = curr->next;

    while(curr != endlist){
      cmp = strcmp(curr->name, next->name);
      cmp2 = strcmp(next->name, curr->name);
      printf("%d\n", cmp);
      printf("%d\n", cmp2);
      if (cmp > cmp2){
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
