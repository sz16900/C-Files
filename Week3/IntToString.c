#include <stdio.h>
#include <stdlib.h>

void int2string(int i, char s[]);

int main(void){

  int i;
  char s[256] = {0};

  printf("\nType in an integer to see what kind of string we get:\n");
  if (scanf("%d", &i) == 1){
    int2string(i,s);
    printf("%s\n", s);
  }
  else{
    printf("Sorry, but this is not an integer.\n");
  }

  return 0;
}

void int2string(int i, char s[]){

  char x = '0';
  int a = 0, j;
  int count = 0;
  char tmp[256] = {0};

  /*if(i < 0){
    i = abs(i);
    s[0] = '175';
    while(i != 0){
      tmp[a] = x + (i % 10);
      a++;
      i = i / 10;
      count++;
    }
      a = 0;

      for (j = count - 1; j >= 1; j--){
        s[a] = tmp[j];
        a++;
      }
  }   IM TRYING TO PUT A NEGATIVE NUMBER IN FRONT SO IT READS THE NEGATIVE INTEGERS AS WELL */

  while(i != 0){
    tmp[a] = x + (i % 10);
    a++;
    i = i / 10;
    count++;
  }
    a = 0;

    for (j = count - 1; j >= 0; j--){
      s[a] = tmp[j];
      a++;
    }

}
