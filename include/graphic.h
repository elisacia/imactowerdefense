#ifndef ITD_GRAPHIC__
#define ITD_GRAPHIC__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>



/* ------- FONCTIONS ------- */

SDL_SURFACE* loadImage(char* filename);

#endif