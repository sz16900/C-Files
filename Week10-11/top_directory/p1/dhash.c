#include "dhash.h"

/* I have used this algorithm from:
http://stackoverflow.com/questions/7666509/hash-function-for-string
acknoledgements to Dan Bernstein */

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

int doubleHashKey(int key, int prime){

  key /= prime;
  key %= prime;
  if(key == 0){ /* this is to avoid infinite loops with zeros */
    return 1;
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

  Data *temp;
  int i;

  temp = tableptr;
  tableptr = initTable(tableptr, prime);
  for (i = 0; i < array_size; i++) {
    if (temp[i].used == 1){
      insertData(tableptr, temp[i].word, prime);
    }
  }

  free(temp);
  return tableptr;
  }

void insertData(Data *tableptr, char *words, int prime){

  int key, move;

  key = hashKey(words, prime);

  if(tableptr[key].used == 1){
    move = doubleHashKey(key, prime);
    while(tableptr[key].used == 1){
      key += move;
      key %= prime;
    }
    strcpy(tableptr[key].word, words);
    tableptr[key].key = key;
    tableptr[key].used = 1;
  }
  else{
    strcpy(tableptr[key].word, words);
    tableptr[key].key = key;
    tableptr[key].used = 1;
 }

}

void findAverage(Data *tableptr, int prime, char **argv){

  float number_of_lookups = 0, number_of_touches = 0;
  int key = 0;
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
        number_of_touches = checkWordExistance(prime, key, number_of_touches, words, tableptr);
      }
      else {
        number_of_touches++;
      }
    }
  }

  printf("Average: %.2f\n\n", number_of_touches/number_of_lookups);
  fclose(fp);
}

int tableFull(int cnt, int prime){

  /* 1.0 to turn them into decimals*/
  if(((cnt*1.0)/(prime*1.0)) <= PERCENTAGE){
    return 0;
  }

  return 1;
}

/* Checks whether a word is not registerd in the table. */
float checkWordExistance(int prime, int key, float number_of_touches, char *x, Data *tableptr){

  int touches_if_not_found, loops = 1, move;
  float touches = number_of_touches;

  move = doubleHashKey(key, prime);
  touches_if_not_found = number_of_touches;
  while(!strsame(x, tableptr[key].word)){
    loops++;
    touches++;
    key += move;
    key %= prime;
    if(loops > prime){
      touches = touches_if_not_found;
      printf("Sorry, but I cannot find this word: \"%s\"\n\n", x);
      return touches;
    }
  }

  return touches;
}
