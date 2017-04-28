#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){ /*Is it the same as *argv[]?*/

  int i, sum = 0;

  printf("argc = %d\n", argc);
  printf("Lets see whats inside argv[]\n");
  if(argc > 1){
    for(i = 1; i < argc; i++){
      printf("argv[%d] = %s\n", i, argv[i]);
      sum += atoi(argv[i]);
    }
    printf("Total = %d\n", sum);
  }

  return 0;
}
