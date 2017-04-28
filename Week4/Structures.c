#include <stdio.h>
#include <ctype.h>

struct student{
  char *surname;
  int id;
  char grade;
};

int failures(struct student j[], int n);

int main(void){

  struct student class [] = {
    {"Bloogs",    95112175, 'c'},
    {"Doobeedoo", 95112176, 'b'},
    {"Campbell",  95112177, 'f'},
    {"Johnson",   95112178, 'a'},
  };

  printf("Number of fails: %d\n", failures(class, 4));

  return 0;
}

int failures(struct student j[], int n){
  
  int i, cnt = 0;

  for(i = 0 ; i<n; i++){
    cnt += (tolower(j[i].grade) == 'f');
  }
    return cnt;
}
