#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <math.h>

#define PRIME  1567
#define CONST 5381
#define SHIFT 5
#define WORDSIZE 30
#define WWIDTH 1000
#define WHEIGHT 600
#define RECTSIZE 4
#define MILLISECONDDELAY 1
#define MILLISECONDDELAY2 1000
#define FILLEDPIXLES 22000
#define EDGEWINDOW 20
#define XVAL 10
#define YVAL 2
#define WSPACE 40
/* Font stuff */
typedef unsigned short fntrow;
#define FNTWIDTH (sizeof(fntrow)*6)
#define FNTHEIGHT 18
#define FNTCHARS 90
#define FNT1STCHAR 32
#define FONTFILE "m7fixed.fnt"



#define SDL_8BITCOLOUR 256

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

/* All info required for windows / renderer & event loop */
struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
};

typedef struct SDL_Simplewin SDL_Simplewin;
struct data{
int used; /* 0 -> unused : 1 -> used */
int key;
char word[WORDSIZE];
struct data *next;
};
typedef struct data Data;

int hashKey(char *name, int prime);
Data *initTable(Data *table, int prime);
int primeFinder(int prime);
int doublePrime(int prime);
Data *crateNewTable(Data *tableptr, int prime, int array_size);
void insertData(Data *tableptr, char *names, int prime);
Data *readFile(int argc, char **argv, Data *tableptr, int prime);
Data *allocateNode(char *names, int key);
int tableFull(int cnt, int prime);
void Neill_SDL_Init(SDL_Simplewin *sw);
void Neill_SDL_Events(SDL_Simplewin *sw);
void Neill_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b);
void Neill_SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r);
void Neill_SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r);
void Neill_SDL_DrawChar(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy, int z);
void Neill_SDL_DrawString(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], char *str, int ox, int oy, int z);
void Neill_SDL_ReadFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname);
void openSDL(Data *tableptr, int prime);
void openSDLInstructions();
