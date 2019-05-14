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



//Function that creates a texture from an image
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
/*
      glTexCoord2d(0,0);
      glVertex2f(-xScale/2,yScale/2); //haut gauche
      glTexCoord2d(0,1);
      glVertex2f(-xScale/2,-yScale/2); //bas-gauche
      glTexCoord2d(1,1);
      glVertex2f(xScale/2, -yScale/2); //bas-droite
      glTexCoord2d(1,0);
      glVertex2f(xScale/2,yScale/2); //haut-droite
*/
/* ------- DESSIN CARRE  ------- */


void drawSquare(int x, int y){
    glBegin(GL_QUADS);
      glTexCoord2d(0, 0); 
      glVertex2f(0, y);
      glTexCoord2d(0, 1); 
      glVertex2f(0, 0);
      glTexCoord2d(1, 1); 
      glVertex2f( x, 0);
      glTexCoord2d(1, 0); 
      glVertex2f( x, y);
    glEnd();
}


/* ------- TEXTE  ------- */

void displayText(void *font, char* info, float x, float y){
  glPushMatrix();
    glLoadIdentity();
    glColor3f(0.5f, 0.5f, 0.5f); 
    glRasterPos2f(x,y);
    glutBitmapString(font,info);
  glPopMatrix();
  glColor3f(1.0f, 1.0f, 1.0f); 
}