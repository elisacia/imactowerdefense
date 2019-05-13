#include <SDL/SDL_image.h>
#include <math.h> 
#include <GL/glut.h> 
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include "map.h"
#include "graphic.h"
#include "menu.h"
#include "monstre.h"
#include "tower.h"
#include "struct.h"

/* Dimensions of the window */
static const unsigned int WIDTH = 800;
static const unsigned int HEIGHT = 600;
/* Number of bits per pixel of the window */
static const unsigned int BIT_PER_PIXEL = 32;
/* Minimal number of milliseconds separating the rendering of two images*/
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;
/* Title of the window */
static const char WINDOW_TITLE[] = "TOWER DEFENSE (by Elisa et Océane)";
/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 2.;

static float aspectRatio;

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{ 
    SDL_Surface* surface_temp = SDL_SetVideoMode(   
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface_temp) 
    {
        fprintf(
            stderr, 
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;

    aspectRatio = width / (float) height;

    glViewport(0, 0, (*surface)->w, (*surface)->h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
        gluOrtho2D(
        0,WIDTH,
        0,HEIGHT);
}


int main(int argc, char** argv) 
{
    /* Initialization of the game */
    Jeu* jeu;
    jeu = (Jeu*)malloc(sizeof(Jeu));
    jeu->start =0;
    jeu->win=0;
    jeu->lose=0;
    jeu->pause=0;
    jeu->help=0;
    jeu->rule=0;
    Map map;
  
    int xClick = 0; 
    int yClick = 0;
    /*
    int xOver=0, yOver =0, buttonOver = 0;
    int terrain =0;
    int taille =0;
    */
    int times=1;
    

    /* Creation of monsters */
    MonsterType typeMonster = CAT_1;
    Monster* monsterSupp = NULL;
    Monster* monsterTmp = NULL;
    monsterSupp=(Monster*)malloc(sizeof(Monster));
    monsterTmp=(Monster*)malloc(sizeof(Monster));
    int nbDead=0; 

    /* Creation of towers */
    TowerType typeTower = RED;
    Tower* tower= NULL;
    Tower* first= NULL;
    Tower* towerOver= NULL;
    Tower* towerSupp= NULL;
    TowerType actionTower = RED;
    towerOver=(Tower*)malloc(sizeof(Tower));
    
    char* info=NULL;

    /* Initialization of money */
    int money = 3000;
    char* yen= "YEN";
    //Show the budget of the player 
    printf("%d %s\n",money, yen);

    /* Initializing the SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
  
    /* Opening a window and creating an OpenGL context */
    SDL_Surface* surface;
    reshape(&surface, WIDTH, HEIGHT);

    /* Initializing the window title */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);


    /* Loading access page */
    //GLuint accessTex = loadTexture("image/access.ppm");
    /*Loading page winner */
    //GLuint winnerTex = loadTexture("image/winner.png");
    /*Loading page loser */
    //GLuint loserTex = loadTexture("image/loser.png");
    /*Loading rules page */
    //GLuint rulesTex = loadTexture("image/rules.png");
    /*Loading help page */
    //GLuint helpTex = loadTexture("image/help.png");
    /*Loading pause page */
    //GLuint pauseTex = loadTexture("image/pause.png");


    /* Loading the ITD map */
    char* nameMap= "./img/carte1.ppm";
    map= loadMap("./data/carte1.itd");
    SDL_Surface* background= loadImage(nameMap);
    GLuint backgroundTex;
    if(background == NULL) {
      fprintf(stderr, "Impossible de charger l'image. %s\n", nameMap);
      return EXIT_FAILURE;
    }
    backgroundTex= loadTexture(nameMap);


    /* Loading the menu */
    GLuint menu = loadTexture("img/menu.png");
    printf("ok\n");

    /* Take back the coordinated of the node */
    Node* node;
    node=(Node*)malloc(sizeof(Node));
    node=map.listNode;
    int nodeX= node->x;
    int nodeY= node->y;

    /* Creation of a monster */
    Monster* monster= createMonster(typeMonster, node->next, nodeX, nodeY);

    /* Creation of a list of monster */
    listMonster listM;
    listM.m= monster;
    listM.nbMonster= 1;
   
    /* Creation of the wave of monsters */
    Wave wave;
    wave.nbLists=1;
    //Creation of the table of the monster's lists 
    wave.list[wave.nbLists -1]= listM;
    char* totalWave=" vagues";
    printf("%d %s\n", wave.nbLists, totalWave);


  
    /* Main loop */
    int loop = 1;
    while(loop) 
    {
        /* Time recovery at the beginning of the loop */
        Uint32 startTime = SDL_GetTicks();
        
        /* Drawing code */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        /* when the player clicks on "play" */
        if (jeu->start ==0 && jeu->pause == 0 && jeu->help == 0 && jeu->win == 0 && jeu->lose == 0 && jeu->rule == 0)
        {

          //draw a rectangle with the texture of the cart
          //glTranslatef(-400,-300,0);
          drawPicture(backgroundTex, background->w, background->h);
          //Draw the path with .itd's colors and the coordinates of nodes
          glColor3ub(map.colorPath.r, map.colorPath.g, map.colorPath.b);
          drawPath(node);

          // Color of the building zones
          /*glColor3ub(map.colorConstruct.r, map.colorConstruct.g, map.colorConstruct.b);
          glPushMatrix();
          glTranslatef(10,220,0);
          drawSquare(160,200);
          glPopMatrix();

          glPushMatrix();
          glTranslatef(230,330,0);
          drawSquare(200,80);
          glPopMatrix();

          glPushMatrix();
          glTranslatef(230,410,0);
          drawSquare(70,150);
          glPopMatrix();

          glPushMatrix();
          glTranslatef(200,90,0);
          drawSquare(160,170);
          glPopMatrix();

          glPushMatrix();
          glTranslatef(510,150,0);
          drawSquare(160,200);
          glPopMatrix();

          glColor3ub(255,255,255);

          /* Displays infos about the selected tower type */     
          if(info == NULL)
          { 
            switch(typeTower)
            {
              case RED:
                loadTexture("img/tower_red_info.png");
                break;
              case GREEN :
                loadTexture("img/tower_green_info.png");
                break;  
              case YELLOW :
                loadTexture("img/tower_yellow_info.png");
                break;
              case BLUE :  
                loadTexture("img/tower_blue_info.png");
                break;
              default:
                break;
            }
          }

        }

        /* Choose the type of monster in function of the number of waves */
        typeMonster = chooseMonster(wave);
        /* Creation of a new monster with default parameters from the beginning */
        Monster* newM = createMonster(typeMonster, node->next, nodeX, nodeY);

        /* About monster list lists */
        if( times%600 == 0  && wave.nbLists < 10 ) 
        {
          listMonster listMonst;
          monster = newM;
          listM.m = monster;
          listM = listMonst;
          listM.nbMonster = 1;
          wave.nbLists+=1;
          wave.list[wave.nbLists - 1]= listM;
          printf("%d %s\n", wave.nbLists, totalWave);
        }
        /* To pause in order to space monsters*/
        else if(times%60 == 0 && listM.nbMonster<6)
        {
          monster = newMonster(monster, newM); //add a monster
          wave.list[wave.nbLists - 1].m = monster;
          listM.nbMonster +=1;
        }

        /* Draw the wave of monsters */    
        //createList(wave, jeu);
        /* Display the wave number */
        //affichageTexte(GLUT_BITMAP_TIMES_ROMAN_24, ChaineFinaleVague, 10,100);





        
        /* Exchange of the front and the back buffer: update of the window */
        SDL_GL_SwapBuffers();
        
        /* Loop dealing with events */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* The user closes the window : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }

            /* The user closes the window : */
                if(e.type == SDL_QUIT) 
                {
                  loop = 0;
                  break;
                }
    
                if( e.type == SDL_KEYDOWN 
                  && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
                {
                  loop = 0; 
                  break;
                }
            
        /* Some examples of treatment of events : */
        switch(e.type) 
        {
          /* Window resizing */
          case SDL_VIDEORESIZE:
            reshape(&surface, e.resize.w, e.resize.h);
            break; 

          /* Mouse click */
          case SDL_MOUSEBUTTONUP:
            printf("clic en (%d, %d)\n", e.button.x, e.button.y);
            break;
                  
          /* Keyboard key */
          case SDL_KEYDOWN:
              printf("touche pressee (code = %d)\n", e.key.keysym.sym);
              break;
                      
            default:
              break;
        }
      }
        

      /* Calculation of elapsed time */
      Uint32 elapsedTime = SDL_GetTicks() - startTime;
      /* If too little time has passed, we pause the program */
      if(elapsedTime < FRAMERATE_MILLISECONDS) 
      {
        SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
      }
    }

    //free(node);
    //free(tourOver);
    //free(tower);
    /*if (jeu->win == 0)
    {
      free(monster);
    } 

    SDL_FreeSurface(background);
    //Suppression de la texture du background
    glDeleteTextures(1, &backgroundTex);
    //SDL_FreeSurface(screen);
    /* Release of resources associated with the SDL */
    SDL_Quit();
    
    return EXIT_SUCCESS;
}