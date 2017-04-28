#include "dhash.h"

/* I used and pasted this algorithm from:
http://stackoverflow.com/questions/7666509/hash-function-for-string
acknoledgements to Dan Bernstein*/
int hashKey(char *name, int prime){

unsigned long key = CONST;
int c;
int i;

for(i = 0; name[i]; i++){
  c = name[i];
  key = ((key << SHIFT) + key) + c; /* key * 33 + c */
  key %= prime;
}

return key;
}

Data *initTable(Data *table, int prime){

  table = (Data *)calloc(prime, sizeof(Data));

  return table;
}

int primeFinder(int prime){

  int i;

  if (prime <= 1){
    return 0;
  }
  if (prime % 2 == 0 && prime > 2){
    return 0;
  }
  for(i = 3; i < prime / 2; i+= 2){
    if (prime % i == 0){
      return 0;
    }
  }

  return 1;
}

int doublePrime(int prime){

  prime *= 2;

  /* loop until a prime number is found. Because hash functions require prime
  numbers*/
  while(!primeFinder(prime)){
    prime++;
  }

  return prime;
}

Data *crateNewTable(Data *tableptr, int prime, int array_size){

  Data *temp, *searcher, *tmp;
  int i;

  temp = tableptr;
  tableptr = initTable(tableptr, prime);

  for (i = 0; i < array_size; i++) {
    if (temp[i].used == 1){
      insertData(tableptr, temp[i].word, prime);
      searcher = temp[i].next;
      while(searcher != NULL){
        insertData(tableptr, searcher->word, prime);
        tmp = searcher;
        searcher = searcher->next;
        free(tmp); /*this frees each node as after it has been re-hashed*/
      }
    }
  }

  free(temp);
  return tableptr;
  }

void insertData(Data *tableptr, char *names, int prime){

  int key;
  Data *next_struct;
  key = hashKey(names, prime);
  next_struct = allocateNode(names, key);

  if(tableptr[key].used == 1){
    if(tableptr[key].next == NULL){
      tableptr[key].next = next_struct;
    }
    else{
      next_struct->next = tableptr[key].next;
      tableptr[key].next = next_struct;
    }

  }
  else{
    strcpy(tableptr[key].word, names);
    tableptr[key].key = key;
    tableptr[key].used = 1;
    tableptr[key].next = NULL;
 }

}

Data *allocateNode(char *names, int key){

  Data *p;
  p = (Data*)malloc(sizeof(Data));

  if(p == NULL){
    printf("Cannot Allocate Node\n");
    exit (EXIT_FAILURE);
  }
  strcpy(p->word, names);
  p->key = key;
  p->next = NULL;

  return p;
}

int tableFull(int cnt, int prime){

  if(cnt < prime*2){
    return 0;
  }

  return 1;
}

void Neill_SDL_Init(SDL_Simplewin *sw){

  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
   }

  sw->finished = 0;

  sw->win= SDL_CreateWindow("SDL Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          WWIDTH, WHEIGHT,
                          SDL_WINDOW_SHOWN);
  if(sw->win == NULL){
    fprintf(stderr, "\nUnable to initialize SDL Window:  %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

   sw->renderer = SDL_CreateRenderer(sw->win, -1, 0);
   if(sw->renderer == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Renderer:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(EXIT_FAILURE);
   }

   /* Set screen to black */
   Neill_SDL_SetDrawColour(sw, 0, 0, 0);
   SDL_RenderClear(sw->renderer);
   SDL_RenderPresent(sw->renderer);

  }

  /* Gobble all events & ignore most */
void Neill_SDL_Events(SDL_Simplewin *sw){
  SDL_Event event;
    while(SDL_PollEvent(&event)){
      switch (event.type){
        case SDL_QUIT:
        /*case SDL_MOUSEBUTTONDOWN:*/
        case SDL_KEYDOWN:
          sw->finished = 1;
      }
    }
}

/* Trivial wrapper to avoid complexities of renderer & alpha channels */
void Neill_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b){

  SDL_SetRenderDrawColor(sw->renderer, r, g, b, SDL_ALPHA_OPAQUE);

}

void Neill_SDL_DrawString(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT],
  char *str, int ox, int oy, int z){

  int i = 0;
  unsigned char chr;
  do{
    chr = str[i++];
    Neill_SDL_DrawChar(sw, fontdata, chr, ox+i*FNTWIDTH, oy, z);
  }while(str[i]);

}

void Neill_SDL_DrawChar(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT],
   unsigned char chr, int ox, int oy, int z){

  unsigned x, y;
  for(y = 0; y < FNTHEIGHT; y++){
    for(x = 0; x < FNTWIDTH; x++){
      if(fontdata[chr-FNT1STCHAR][y] >> (FNTWIDTH - 1 - x) & 1){
        switch (z) {
          case 0: Neill_SDL_SetDrawColour(sw, 255, 255, 255);break;
          case 1: Neill_SDL_SetDrawColour(sw, 0, 255, 0);break;
          case 2: Neill_SDL_SetDrawColour(sw, 255, 255, 0);break;
          case 3: Neill_SDL_SetDrawColour(sw, 255, 128, 0);break;
          case 4: Neill_SDL_SetDrawColour(sw, 255, 0, 0);break;
        }
        SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
      }
      else{
        /*printf(".");*/
        /* Black Ink */
        Neill_SDL_SetDrawColour(sw, 0, 0, 0);
        SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
      }
    }
  }
}

void Neill_SDL_ReadFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname){

  FILE *fp = fopen(fname, "rb");
  size_t itms;
  if(!fp){
    fprintf(stderr, "Can't open Font file %s\n", fname);
    exit(EXIT_FAILURE);
  }
  itms = fread(fontdata, sizeof(fntrow), FNTCHARS*FNTHEIGHT, fp);
  if(itms != FNTCHARS*FNTHEIGHT){
    fprintf(stderr, "Can't read all Font file %s (%d) \n", fname, (int)itms);
    exit(EXIT_FAILURE);
  }

  fclose(fp);
}

/* Because of professor Neill's wrapper function, it is pretty difficult to keep
this function small */
void openSDL(Data *tableptr, int prime){

  int y = EDGEWINDOW, key = 0, x = 0, elem_cnt;
  Data *searcher;
  SDL_Simplewin sw;
  SDL_Rect rectangle;
  rectangle.w = RECTSIZE;
  rectangle.h = RECTSIZE;
  Neill_SDL_Init(&sw);

  do{
    /* Sleep for a short time */
    SDL_Delay(MILLISECONDDELAY);
    y += (RECTSIZE+1); /*plus 1 for borders*/
    rectangle.x = x;
    rectangle.y = y;

    if(y >= WHEIGHT-EDGEWINDOW){ /*so it doesnt go off the sceen*/
      x += RECTSIZE+1;
      y = EDGEWINDOW;
    }

    elem_cnt = 0;
    /*count the number of links per memory location to be drawn onto the screen
    via their respective colour*/
    if(tableptr[key].used == 1){
      elem_cnt++;
      searcher = tableptr[key].next;
      while(searcher != NULL){
        elem_cnt++;
        searcher = searcher->next;
      }
    }

   if(key < prime){ /*so it doesn't SegFaults when it reaches end of table*/
     key++;
     switch(elem_cnt){
       case 0: Neill_SDL_SetDrawColour(&sw, 255, 255, 255); break;
       case 1: Neill_SDL_SetDrawColour(&sw, 0, 255, 0); break;
       case 2: Neill_SDL_SetDrawColour(&sw, 255, 255, 0); break;
       case 3: Neill_SDL_SetDrawColour(&sw, 255, 128, 0); break;
       case 4: Neill_SDL_SetDrawColour(&sw, 255, 0, 0); break;
     }
    SDL_RenderFillRect(sw.renderer, &rectangle);
   }
   /* Update window - no graphics appear on some devices until this is finished */
   SDL_RenderPresent(sw.renderer);
   SDL_UpdateWindowSurface(sw.win);
   /* Has anyone pressed ESC or killed the SDL window ?
      Must be called frequently - it's the only way of escaping */
   Neill_SDL_Events(&sw);

   if(key % FILLEDPIXLES == 0){ /* has it filled the SDL_Window yet? If so new Window */
     Neill_SDL_Init(&sw);
     x = 0;
     y = EDGEWINDOW;
   }

}while(!sw.finished);
/* Clear up graphics subsystems */
atexit(SDL_Quit);
}

/* this function is large due to the nature of the text to be rendered
onto the SDL window*/
void openSDLInstructions(){

  /* x and y values are set as parameters for rendering the text. These are not Magic Numbers*/
  int x = XVAL, y = YVAL, z = WSPACE;
  int delay = 0;
  fntrow fontdata[FNTCHARS][FNTHEIGHT];
  SDL_Simplewin sw;
  Neill_SDL_ReadFont(fontdata, FONTFILE);
  Neill_SDL_Init(&sw);
  do{
    /* Sleep for a short time */
    SDL_Delay(MILLISECONDDELAY2);
    switch (delay) {
      case 0:Neill_SDL_DrawString(&sw, fontdata, "Hello world! Up next, I will show you a"
      " representation of data via some colours.", y, x, 0);break;
      case 1: Neill_SDL_DrawString(&sw, fontdata, "Each square represents data"
      " stored with a key rendered by a hash function.", y, x, 0);break;
      case 2: Neill_SDL_DrawString(&sw, fontdata, "And each square will be redenred"
      " north-south, representing contigious memory.", y, x, 0);break;
      case 3: Neill_SDL_DrawString(&sw, fontdata, "Because of linked-lists, colours represent"
      " the ammount of links each key contains.", y, x, 0);break;
      case 4: Neill_SDL_DrawString(&sw, fontdata, "Let me illustrate this better:", y, x, 0);break;
      case 5: Neill_SDL_DrawString(&sw, fontdata, "This colour represents an"
      " empty key", y, x, 0);break;
      case 6: Neill_SDL_DrawString(&sw, fontdata, "This colour represents a key"
      " with one element", y, x, 1);break;
      case 7: Neill_SDL_DrawString(&sw, fontdata, "This colour represents a key"
      " with two linked elements", y, x, 2);break;
      case 8: Neill_SDL_DrawString(&sw, fontdata, "This colour represents a key"
      " with three linked elements", y, x, 3);break;
      case 9: Neill_SDL_DrawString(&sw, fontdata, "This colour represents a key"
      " with four or more linked elements", y, x, 4);break;
      case 10: Neill_SDL_DrawString(&sw, fontdata, "Because data could be large,"
      " several windows might be needed to show it.", y, x, 0);break;
      case 11: Neill_SDL_DrawString(&sw, fontdata, "Press ESC to continue."
      " Press ESC again to exit.", y, x, 0);break;
    }
    /* Update window - no graphics appear on some devices until this is finished */
    SDL_RenderPresent(sw.renderer);
    SDL_UpdateWindowSurface(sw.win);
     /* Has anyone pressed ESC or killed the SDL window ?
      Must be called frequently - it's the only way of escaping */
    Neill_SDL_Events(&sw);
    delay++;
    x = x + z;
  }while(!sw.finished);
/* Clear up graphics subsystems */
atexit(SDL_Quit);
}
