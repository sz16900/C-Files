#include "neillncurses.h"

#define SIZE 20

int main(void)
{


  /* Array we'll display */
  char a[SIZE][SIZE];
  int i,j;

  /* Here's where we hold all the information we need to display
     the array in the correct colours, and also event information */
  NCURS_Simplewin sw;

  /* fill the array with spaces */
  for(j=0; j<SIZE; j++){
     for(i=0; i<SIZE; i++){
        a[j][i] = ' ';
     }
  }
  /* Use memcpy, not strcpy, because I don't want any null chars in my array */
  memcpy(a[SIZE/2-1], " lqqqqqqqqqqqqqqqk  ", SIZE);
  memcpy(a[SIZE/2  ], " x  HELLO WORLD! x  ", SIZE);
  memcpy(a[SIZE/2+1], " mqqqqqqqqqqqqqqqj  ", SIZE);

  Neill_NCURS_Init(&sw);
  /* For the character 'H', 'E' etc. use red foreground colour, black background,
     and the alternative character set */
  Neill_NCURS_CharStyle(&sw, "HELOWRD", COLOR_RED, COLOR_BLACK, A_NORMAL);
  /* For the characters 'j', 'k', 'l' etc. use green foreground colour, black background,
     in bold with the alternative character set */
  Neill_NCURS_CharStyle(&sw, "jklmqxf", COLOR_GREEN, COLOR_BLACK, A_BOLD | A_ALTCHARSET);

  Neill_NCURS_PrintArray(&a[0][0], SIZE, SIZE, &sw);

  do{
     /* Wait for mouse click, or ESC key */
     Neill_NCURS_Events(&sw);
  }while(!sw.finished);

  /* Call this function if we exit() anywhere in the code */
  atexit(Neill_NCURS_Done);

  exit(EXIT_SUCCESS);

}
