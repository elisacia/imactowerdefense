#ifndef ITD_GRAPHIC__
#define ITD_GRAPHIC__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>



/* ------- FONCTIONS ------- */

SDL_Surface* loadImage(char* filename); //image loading
GLuint loadTexture (char* filename); //texture loading
void drawPicture(GLuint textureId, int xScale, int yScale); //drawing a square with texture

#endif