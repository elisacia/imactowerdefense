#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <GL/glut.h> 

#include "map.h"
#include "graphic.h"
#include "menu.h"
#include "monstre.h"
#include "tower.h"
#include "struct.h"

#define WIDTH 800
#define HEIGHT 600


int main(int argc, char** argv) {
  
  /* Initialization du jeu */
  Jeu* jeu;
  jeu = (Jeu*)malloc(sizeof(Jeu));
  jeu->start =0;
  jeu->win=0;
  jeu->lose=0;
  jeu->pause=0;
  jeu->help=0;
  jeu->rule=0;
  Map map;
  

  
  int xClick = 0, 
  int yClick = 0;
  /*
  int xOver=0, yOver =0, buttonOver = 0;
  int terrain =0;
  int taille =0;
  int times=1;
  */

}