#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
  srand ( time(NULL) );
  int numbers_required, i, generated_random, x, tmp;

  printf("How many songs required? \n");
  scanf("%d", &numbers_required);

  int number_of_songs[numbers_required]; /*Why do I have to declare this array here? That is, after...*/

  for (i = 0; i < numbers_required; i++ ){
    number_of_songs[i] = i + 1;
  }

  for (i = 0; i < numbers_required; i++ ){
    x = rand() % (numbers_required);
    tmp = number_of_songs[i];
    number_of_songs[i] = number_of_songs[x];
    number_of_songs[x] = tmp;
  }

    for (i = 0; i < numbers_required; i++ ){
      printf("%d\n", number_of_songs[i]);
    }

return 0;
}
