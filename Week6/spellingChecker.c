#include <stdio.h>
#include <string.h>
#include <time.h>

#define CSEC (double) (CLOCKS_PER_SEC)

int main(int argc, char **argv){

  int n = 1, i = 0, j = 0, k = 0;
  char arr[2891][5];
  char t[20];
  FILE *fp;
  clock_t c1, c2;

  c1 = clock();
  if( argc==2 ){
    if((fp = fopen(argv[1], "r")) == NULL){
      printf("ERROR: Incorrect usage, try e.g. %s 34words.txt\n", argv[0]);
      return 1;
    }
    else{
      n = fscanf(fp, "%s",arr[i]);
      i++;
      while(n > 0){
       n = fscanf(fp, "%s",arr[i]);
        i++;
        for (k = 1; k < i-1; k++) {
          for (j = 1; j < i-1; j++) {
            if (strcmp(arr[j - 1], arr[j]) > 0) {
              strcpy(t, arr[j - 1]);
              strcpy(arr[j - 1], arr[j]);
              strcpy(arr[j], t);
            }
          }
        }
      }
    }

  for (i = 0; i < 2891; i++) {
         printf("%s\n", arr[i]);
       }

    fclose(fp);
  }

  c2 = clock();
  printf("%f\n", (double)(c2-c1/CSEC));
  return 0;
}
