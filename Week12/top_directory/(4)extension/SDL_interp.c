#include "interp.h"

void closeWinUserInput(SDL_Simplewin *sw){

  do{
    /* Sleep for a short time */
    SDL_Delay(MILLISECONDDELAY);
    /* Update window - no graphics appear on some devices until this is finished */
    SDL_RenderPresent(sw->renderer);
    SDL_UpdateWindowSurface(sw->win);
    /* Has anyone pressed ESC or killed the SDL window ?
       Must be called frequently - it's the only way of escaping */
    Neill_SDL_Events(sw);
  }while(!sw->finished);

  }

void Neill_SDL_Init(SDL_Simplewin *sw){

  SDL_Surface *surface;
  SDL_Texture *tex;

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

   /* Load image into memory using SDL_image library functions */
   surface = IMG_Load("turtle.png");
   if(!surface){
     printf("error creating surface\n");
     SDL_DestroyRenderer(sw->renderer);
     SDL_DestroyWindow(sw->win);
     SDL_Quit();
     exit (1);
   }

   /* Load image into hardware using SDL_image library functions */
   tex = SDL_CreateTextureFromSurface(sw->renderer, surface);
   SDL_FreeSurface(surface);
   if(!tex){
     printf("error creating texture\n");
     SDL_DestroyRenderer(sw->renderer);
     SDL_DestroyWindow(sw->win);
     SDL_Quit();
     exit (1);
   }


   /* Set screen to white */
   Neill_SDL_SetDrawColour(sw, 255, 255, 255);
   SDL_RenderClear(sw->renderer);
   SDL_RenderCopy(sw->renderer, tex, NULL, NULL);
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

void sprite(SDL_Simplewin *sw, Coor *coor){

  SDL_Rect dest;
  SDL_Surface *surface;
  SDL_Texture *tex;

  surface = IMG_Load("pizza.png");
  if(!surface){
    printf("error creating surface\n");
    SDL_DestroyRenderer(sw->renderer);
    SDL_DestroyWindow(sw->win);
    SDL_Quit();
    exit (1);
  }

  /* Load image into hardware using SDL_image library functions */
  tex = SDL_CreateTextureFromSurface(sw->renderer, surface);
  SDL_FreeSurface(surface);
  if(!tex){
    printf("error creating texture\n");
    SDL_DestroyRenderer(sw->renderer);
    SDL_DestroyWindow(sw->win);
    SDL_Quit();
    exit (1);
  }

    dest.w = SPSIZE;
    dest.h = SPSIZE;

    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    dest.x = coor->x;
    dest.y = coor->y;
    SDL_RenderCopy(sw->renderer, tex, NULL, &dest);
    SDL_DestroyTexture(tex);

  }
