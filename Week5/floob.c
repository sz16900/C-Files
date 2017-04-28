#include <stdio.h>
#include <string.h>

#define WORD 4

void valid(char *s1, char *s2, int p[WORD]);

int main(int argc, char *argv[])
{

   int p[WORD] = {4,1,2,3};
   valid("wild", "tame", p);
   return 0;

}

void valid(char *s1, char *s2, int p[WORD])
{

   int plc, i;
   char tmp[WORD+1];

   strcpy(tmp, s1);

   printf("%s\n", tmp);
   for(i=0; i<WORD; i++){
      plc = p[i]-1;
      tmp[plc] = s2[plc];
      printf("%s\n", tmp);
   }

}
