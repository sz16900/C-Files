#include <stdio.h>
#include <string.h>

#define NUMPEOPLE 6

struct key {
  char *name;
  int age;
};

typedef struct key Key;

int FindAge(char *name, Key *l, int n);

int main(void){

  int i, j;
  Key a[NUMPEOPLE] = { /*array of structures*/
        {"Ackerby", 21},
        {"Bloggs", 25},
        {"Chumley", 25},
        {"Dalton", 25},
        {"Eggson", 21},
        {"Fulton", 21}, };

  i = FindAge("Eggson", a, NUMPEOPLE);
  j = FindAge("Campbell", a, NUMPEOPLE);
  printf("%d %d\n",i, j);


  return 0;
}

int FindAge(char *name, Key *l, int n){

  int j;

  for(j = 0; j < n; j++){
    if(strcmp(name, l[j].name) == 0){
      return l[j].age;
    }
  }

  return -1;
}
