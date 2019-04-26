#include "graphic.h"

/* ------- CHARGEMENT IMAGE ------- */

SDL_SURFACE* loadImage(char* filename){
	SDL_SURFACE* image = IMG_LOAD(filename);
	if (image == NULL)
	{
		fprintf(stderr, "Erreur chargement image %s\n", filename );
		exit(1);
	}
	return image;
	SDL_FreeSurface(image);
}