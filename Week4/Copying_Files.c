#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 128

int main(void){

  FILE *ifp, *ofp;
  char inpname[MAXLINE];
  char oupname[MAXLINE];
  int i;

  printf("Enter two filenames: ");
  if (scanf("%s %s", inpname, oupname) != 2){
    printf("Failed to scan 2 filenames.\n");
    exit(1);
  }
  ifp = fopen(inpname, "r");
  ofp = fopen(oupname, "w");
  if(ifp == NULL || ofp == NULL){
    printf("Failes to open 2 filenames.\n");
    exit(1);
  }
  while((i = getc(ifp)) != EOF){
    putc(i, ofp);
  }

  fclose(ifp);
  fclose(ofp);
  return 0;
}
