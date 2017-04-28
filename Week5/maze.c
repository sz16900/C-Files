#include <stdio.h>

#define FALSE 0
#define TRUE 1

#define NROWS 6
#define MCOLS 6

char maze[NROWS][MCOLS] = {
  "S...##",
  "#.#...",
  "#.##.#",
  "..#.##",
  "#...#G",
  "#.#..."
};

void display_maze(void);
int find_path(int x, int y);

int main(void){

  display_maze();

  if (find_path(0, 0) == TRUE) {
    printf("SUCCESS!\n");
  }
  else{
    printf("FAILES!\n");
  }

  display_maze();

  return 0;
}

void display_maze(void){

  int i;

  printf("MAZE:\n");
  for(i = 0; i < NROWS; i++){
    printf("%.*s\n", MCOLS, maze[i]);
  }
  printf("\n");

  return;
}

int find_path(int x, int y){

  if ( x < 0 || x > MCOLS - 1 || y < 0 || y > NROWS - 1 ) return FALSE;
  if ( maze[y][x] == 'G' ) return TRUE;
  if ( maze[y][x] != '.' && maze[y][x] != 'S' ) return FALSE;
  maze[y][x] = '+';
  if ( find_path(x, y - 1) == TRUE ) return TRUE;
  if ( find_path(x + 1, y) == TRUE ) return TRUE;
  if ( find_path(x, y + 1) == TRUE ) return TRUE;
  if ( find_path(x - 1, y) == TRUE ) return TRUE;
  maze[y][x] = 'x';

  return FALSE;  
}
