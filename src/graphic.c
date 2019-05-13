#include "graphic.h"

/* ------- CHARGEMENT IMAGE ------- */

SDL_Surface* loadImage(char* filename){
	SDL_Surface* image = IMG_Load(filename);
	if (image == NULL)
	{
		fprintf(stderr, "Erreur chargement image %s\n", filename );
		exit(1);
	}
	return image;
	//SDL_FreeSurface(image);
}



/* ------- CHARGEMENT TEXTURE ------- */

/*GLuint loadTexture (char* filename){
	GLuint textureId;
	SDL_Surface* image= loadImage(filename); //chargement image

		if (image == NULL)
		{
			fprintf(stderr, "Erreur chargement image %s\n", filename );
			exit(1);

		}
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image->w,image->h,0,GL_RGBA,GL_UNSIGNED_BYTE,image->pixels);
	printf("ok6\n");
	SDL_FreeSurface(image);
	printf("ok7\n");
	glBindTexture(GL_TEXTURE_2D,0);

	return textureId;
}*/

//Fonction qui créé une texture à partir d'une image
GLuint loadTexture (char* filename){
  GLuint textureId;
  GLenum format;
  //Chargement de l'image
  SDL_Surface* image = loadImage(filename);
  //espace mémoire pour la texture
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  //applique un filtre
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //GLenum format;
  switch(image->format->BytesPerPixel) {
  //Si on a 1 pixel
  case 1:
  format = GL_RED;
  break;
  case 3:
  /* Ne gere pas les machines big-endian (a confirmer...) */
  format = GL_RGB;
  break;
  case 4:
  /* Ne gere pas les machines big-endian (a confirmer...) */
  //Gère transparence
  format = GL_RGBA;
  break;
  default:
  /* On ne traite pas les autres cas */
    fprintf(stderr, "Format des pixels de l’image %s non pris en charge\n", filename);
    exit(1);
  }

  //envoie donner à OpenGL
  glTexImage2D(
  GL_TEXTURE_2D, 
  0, 
  GL_RGBA, 
  image->w, 
  image->h, 
  0, 
  format, 
  GL_UNSIGNED_BYTE, 
  image->pixels
   );

  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(image);
  return textureId;
}

/* ------- DESSIN CARRE TEXTURE ------- */

void drawPicture(GLuint textureId, int xScale, int yScale){
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