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


/* ------- CHARGEMENT TEXTURE ------- */

GLuint loadTexture (char* filename){
	GLuint textureId;
	GLenum format;

	SDL_Surface* image= loadImage(filename); //chargement image

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image->w,image->h,0,format,GL_UNSIGNED_BYTE,image->pixels);

	glBindTexture(GL_TEXTURE_2D,0);
	SDL_FreeSurface(image);
	return textureId;
}

/* ------- DESSIN CARRE TEXTURE ------- */

void drawPicture(GLuint textureID, int xScale, int yScale){
	glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glBegin(GL_QUADS);
			glTexCoord2d(0,0);
			glVertex2f(0,yScale);
			glTexCoord2d(0,1);
			glVertex2f(0,0);
			glTexCoord2d(1,1);
			glVertex2f(xScale,0);
			glTexCoord2d(1,0);
			glVertex2f(xScale,yScale);
		glEnd();

		glBindTexture(GL_TEXTURE_2D,0);
		glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,0);

}