#include <stdio.h>
#include <stdlib.h>

int main(void){

  FILE *fp;

  if((fp = fopen("file3.txt", "w")) == NULL){
    printf("Cannot open file\n");
    return(1);
  }
  fprintf(fp, "Konichiwua\n");
  fclose(fp);

  return 0;
}
