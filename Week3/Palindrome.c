
  #include <stdio.h>
  #include<ctype.h>

  #define MAXLINE 100

  void check(char s[], int *n);
  void read_in(char *s, int *n); /* Remeber, it can be both *s and s[]*/

  int main(void){

    char line[MAXLINE];
    int str_len = 0;

    printf("\nLets see whether your input is a Palindrome:\n");
    read_in(line, &str_len);
    check(line, &str_len);

    return 0;
  }

  void read_in(char s[], int *n){

    int c, i = 0, j = 0;

    while((c = getchar()) != EOF && c!= '\n'){
      if(isalpha(c)){
        s[i++] = tolower(c);
        *n = j++;
      }
    }
    s[i] = '\0';
  }

  void check(char *s, int *n){

    int i;
    char reversed_string[MAXLINE];
    char *p = reversed_string;

    for(i = *n; i >= 0; i--){
      *p++ = s[i];
    }
    *p = '\0';

    for(i = 0; i <= *n; i++){
      if(s[i] != reversed_string[i]){
        printf("This is not a palindrome! \n");
        break;
      }
      else if((s[i] == '\0') == (reversed_string[i] == '\0')){
        printf("This is a Palindrome! \n");
        break;
      }
    }
  }
