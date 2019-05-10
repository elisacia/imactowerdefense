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
#define BIT_PER_PIXEL 32


int main(int argc, char** argv) {
  
  // /* Initialization du jeu */
  // Jeu* jeu;
  // jeu = (Jeu*)malloc(sizeof(Jeu));
  // jeu->start =0;
  // jeu->win=0;
  // jeu->lose=0;
  // jeu->pause=0;
  // jeu->help=0;
  // jeu->rule=0;
  // Map map;
  

  
  // int xClick = 0; 
  // int yClick = 0;
  // /*
  // int xOver=0, yOver =0, buttonOver = 0;
  // int terrain =0;
  // int taille =0;
  // int times=1;
  // */

  // /* Creation of monsters */
  // MonsterType typeMonster = CAT_1;
  // Monster* monsterSupp = NULL;
  // Monster* monsterTmp = NULL;
  // monsterSupp=(Monster*)malloc(sizeof(Monster));
  // monsterTmp=(Monster*)malloc(sizeof(Monster));
  // int nbDead=0; 


  // /* Creation of towers */
  // TowerType typeTower = RED;
  // Tower* tower= NULL;
  // Tower* first= NULL;
  // Tower* towerOver= NULL;
  // Tower* towerSupp= NULL;
  // TowerType actionTower = RED;
  // towerOver=(Tower*)malloc(sizeof(Tower));
  
  // char* info=NULL;


  // /* Initialization of money */
  // int money = 3000;
  // char* yen= "YEN";


  // /* Initialization of wave*/
  // char* totalWave=" vagues";


  // /* Texture background */
  // //GLuint backgroundTex;


  // /* Show the budget of the player */
  // printf("%d %s\n",money, yen);

  // /* Initialization of SDL*/
  // if (SDL_Init(SDL_INIT_VIDEO)==-1)
  // {
  //     fprintf(stderr, "Problème dans l'initalisation du jeu. Fin du programme.");
  //     return EXIT_FAILURE;
  // }

  
  // /* Initialization of GLUT and window */ 
  // if(NULL == SDL_SetVideoMode(WIDTH, HEIGHT, BIT_PER_PIXEL, 
  //         SDL_OPENGL  | SDL_RESIZABLE | SDL_DOUBLEBUF)) {
  //   fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
  //   exit(EXIT_FAILURE);
  
  // reshape();
  
  // glClear(GL_COLOR_BUFFER_BIT);
  // SDL_GL_SwapBuffers();

  // setVideoMode();

  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // glutInit(&argc, argv); 

  // SDL_WM_SetCaption("Tower Defense par Elisa et Océane - IMAC1", NULL);


  // /* Loading access page */
  // GLuint accessTex = loadTexture("image/access.ppm");
  // /*Loading page winner */
  // GLuint winnerTex = loadTexture("image/winner.png");
  // /*Loading page loser */
  // GLuint loserTex = loadTexture("image/loser.png");
  // /*Loading rules page */
  // GLuint rulesTex = loadTexture("image/rules.png");
  // /*Loading help page */
  // GLuint helpTex = loadTexture("image/help.png");
  // /*Loading pause page */
  // GLuint pauseTex = loadTexture("image/pause.png");


  // /* Loading the ITD map */
  // char* mapImage= "images/carte1.ppm";
  // map= loadMap("data/carte1.itd");
  // SDL_Surface* background= loadImage(mapImage);
  // backgroundTex= loadTexture(mapImage);
   loadMap("data/carte1.itd");


}