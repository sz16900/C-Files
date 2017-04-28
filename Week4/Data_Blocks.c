#include <stdio.h>
#include <stdlib.h>

int main(void){

  FILE *fp;
  int i;
  char arr[6];

  if((fp = fopen("file1.txt", "rb")) == NULL){
    printf("Cannot open file\n");
    return(1);
  }
  fread(arr, sizeof(char), 5, fp);

  for(i = 0; i < 5; i++){
    printf("Character %d was i%d\n", i, arr[i]);
  }

  fclose(fp);

  return 0;
}
