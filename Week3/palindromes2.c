#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

int main(void){

  char str[MAXLINE];
  int i=0,j, k = 0;
  int new_str[MAXLINE];

  printf("Enter a String:\n");
  scanf("%s",&str);

  while (str[i]!='\0'){
    i++;
  }

  printf("Reversed String is:\n");

  for(j=i-1; j>=0;j--)
  {
    new_str[k] = tolower(str[j]);
    k++;
  }

  for (j = 0; j<= i - 1; j++){
    printf("%s\n", new_str);
  }

  return 0;
}
