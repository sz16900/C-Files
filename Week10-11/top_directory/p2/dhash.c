#include "dhash.h"

/* I have copied and pasted this algorith from:
http://stackoverflow.com/questions/7666509/hash-function-for-string
acknoledgements to Dan Bernstein*/
int hashKey(char *name, int prime){


  unsigned long key = CONST;
  int c;
  int i;

  for(i=0; name[i]; i++){
    c = name[i];
    key = ((key << SHIFT) + key) + c; /* key * 33 + c */
    key %= prime;
  }

  return key;
}

Data *initTable(Data *table, int prime){

  table = (Data *)calloc(prime, sizeof(Data));

  return table;
}

int primeFinder(int prime){

  int i;

  if (prime <= 1){
    return 0;
  }
  if (prime % 2 == 0 && prime > 2){
    return 0;
  }
  for(i = 3; i < prime / 2; i+= 2){
    if (prime % i == 0){
      return 0;
    }
  }

  return 1;
}

int doublePrime(int prime){

  prime *= 2;

  /* loop until a prime number is found. Because hash functions require prime
  numbers*/
  while(!primeFinder(prime)){
    prime++;
  }
  return prime;
}

Data *crateNewTable(Data *tableptr, int prime, int array_size){

  Data *temp, *searcher, *tmp;
  int i;

  temp = tableptr;
  tableptr = initTable(tableptr, prime);
  for (i = 0; i < array_size; i++) {
    if (temp[i].used == 1){
      insertData(tableptr, temp[i].word, prime);
      searcher = temp[i].next; /*start re-hashing the nodes in the linked list*/
      while(searcher != NULL){
        insertData(tableptr, searcher->word, prime);
        tmp = searcher;
        searcher = searcher->next;
        free(tmp); /*this frees each node after it has been re-hashed*/
      }
    }
  }

  free(temp);
  return tableptr;
}

void insertData(Data *tableptr, char *words, int prime){

  int key;
  Data *next_struct;
  key = hashKey(words, prime);
  next_struct = allocateNode(words, key);

  if(tableptr[key].used == 1){
    if(tableptr[key].next == NULL){
      tableptr[key].next = next_struct;
    }
    else{
      next_struct->next = tableptr[key].next;
      tableptr[key].next = next_struct;
    }

  }
  else{
    strcpy(tableptr[key].word, words);
    tableptr[key].key = key;
    tableptr[key].used = 1;
    tableptr[key].next = NULL;
 }

}

Data *allocateNode(char *words, int key){

  Data *p;
  p = (Data*)malloc(sizeof(Data));

  if(p == NULL){
    printf("Cannot Allocate Node\n");
    exit (EXIT_FAILURE);
  }

  strcpy(p->word, words);
  p->key = key;
  p->next = NULL;

  return p;
}

int tableFull(int cnt, int prime){

  if(cnt < prime*2){
    return 0;
  }

  return 1;
}

void findAverage(Data *tableptr, int prime, char **argv){

  float number_of_lookups = 0, number_of_touches = 0;
  int key;
  FILE *fp;
  char words[WORDSIZE];

  if((fp = fopen(argv[2], "r")) == NULL){
    printf("ERROR: Incorrect usage, try e.g. %s eowl_shuffle.txt eowl_shuffle.txt\n", argv[0]);
    exit (EXIT_FAILURE);
  }
  else{
    while(fscanf(fp, "%s", words) == 1){
      number_of_lookups++;
      key = hashKey(words, prime);
      if(!strsame(words, tableptr[key].word)){
        number_of_touches = checkWordExistance(number_of_touches, key, words, tableptr);
      }
      else {
        number_of_touches++;
      }
    }
  }

  printf("Average: %.2f\n\n", number_of_touches/number_of_lookups);
  fclose(fp);
}

/* Checks whether a word is not registerd in the table. */
float checkWordExistance(float number_of_touches, int key, char *x, Data *tableptr){

  Data *searcher;
  float touches_if_not_found;

  searcher = &tableptr[key];
  touches_if_not_found = number_of_touches;
  while(searcher != NULL && !strsame(x, searcher->word)){
    number_of_touches++;
    searcher = searcher->next;
  }
    if(searcher == NULL){
      number_of_touches = touches_if_not_found;
      printf("Sorry, but I cannot find this word: \"%s\"\n\n", x);
    }

  return number_of_touches;
}
