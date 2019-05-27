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
#include "bat.h"
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
    jeu->start =1;
    jeu->win=0;
    jeu->lose=0;
    jeu->pause=0;
    jeu->help=0;
    Map map;
  
    int xClick = 0; 
    int yClick = 0;
    int xOver=0;
    int yOver =0;
    int buttonOver = 0;
    int terrain =0;
    int taille =0;
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
    char* yen= " YEN";
    char str_money[10]; // Chaine de char qui stocke l'entier money convertit en chaine de char
    char FinalStringMoney[20];
    sprintf(str_money, "%d", money); // Conversion de l'entier
    /* Concatenation de la chaine de caractere money et de "Euro"*/
    sprintf(FinalStringMoney, "%s%s", str_money, yen);
    printf("%s\n",FinalStringMoney );
   

    //Show the budget of the player 
    //printf("%d %s\n",money, yen);

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
    GLuint accessTex = loadTexture("img/accueil.png");
    /*Loading help page */
    GLuint helpTex = loadTexture("img/help.png");
    /*Loading informationstion's tower page */
    GLuint towerRedTex = loadTexture("img/tower_red_info.png");
    GLuint towerBluTex = loadTexture("img/tower_blue_info.png");
    GLuint towerGreTex = loadTexture("img/tower_green_info.png");
    GLuint towerYelTex = loadTexture("img/tower_yellow_info.png");


    /* Loading the ITD map */
    char* nameMap= "./img/carte1.ppm";
    map= loadMap("./data/carte1.itd");
    SDL_Surface* background= loadImage(nameMap);
    GLuint backgroundTex;
    if(background == NULL) 
    {
      fprintf(stderr, "Impossible de charger l'image. %s\n", nameMap);
      return EXIT_FAILURE;
    }
    backgroundTex= loadTexture(nameMap);

    //Initialisation Glut
    char *myargv [1];
    int myargc=1;
    myargv [0]=strdup("Myappname");
    glutInit(&myargc, myargv);


    /* Loading the menu */
    GLuint menu = loadTexture("img/menu.png");
    printf("ok pour le menu\n");

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
    char* totalWave=" / 10 vagues";
    printf("%d %s %d\n", wave.nbLists, totalWave, jeu->help);


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
        if (jeu->start ==0 && jeu->pause == 0 && jeu->help == 0 && jeu->win == 0 && jeu->lose == 0)
        {
          //draw a rectangle with the texture of the cart
          drawPicture(backgroundTex, background->w, background->h);
          //draw a rectangle with the texture of the map
          glTranslatef(600,0,0);
          drawPicture(menu, 200, 600);
        

            /* Choose the type of monster in function of the number of waves */
            typeMonster = chooseMonster(wave);
            /* Creation of a new monster with default parameters from the beginning */
            Monster* newM = createMonster(typeMonster, node->next, nodeX, nodeY);

            //printf("%d %d %d %s %d\n",monster->lifePoint,monster->resistance,monster->speed,monster->imageMonster,monster->profit);           


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
            glPushMatrix();
            glTranslatef(-600,483,0);
            createList(wave, jeu);
            glPopMatrix();

            /* Display the wave number */
            char stringWave[255];
            char str_wave[10];
            sprintf(str_wave, "%d", wave.nbLists); // Convert the integer
            sprintf(stringWave, "%s%s", str_wave, totalWave);
            displayText(GLUT_BITMAP_9_BY_15, stringWave, 300,30);
            
            /* Display the money of the player */
            glPushMatrix();
            glTranslatef(-570,550,0);
            glColor3f(0.0f, 0.0f, 0.0f); 
            drawSquare(90,30);
            glPopMatrix();

            displayText(GLUT_BITMAP_9_BY_15, FinalStringMoney, 40, 560);
            

        /* Delete a tower */
        /*if(towerSupp != NULL)
        {
          first = deleteTower(first, towerSupp);
        }  



        /******** ACTION TOWER / MONSTER *********/
        /* Display the list of monsters in the table */
 /*          for(int i = 0; i < wave.nbLists; i++) 
           {  
             while(monsterSupp != NULL) 
             {             
                 // If the tower detects a monster => return the type of the tower
                 actionTower = detectMonster(first, (*monsterSupp).x, (*monsterSupp).y);
                 if(actionTower!=-1){ 
                   if(monsterSupp->lifePoint > 0)
                   {
                     switch(actionTower)
                     {           
                       case RED:
                         // regulate the pace thanks to the modulo
                         if(times%first->cadence == 0)
                         {
                           /* Pour la resistance on divise la puissance de la tour par la résistance du monstre (+ sa résistance est grande moins la tour aura d'impact) */
/*                           if(monsterSupp->lifePoint >= first->puissance) 
                           {
                             monsterSupp->lifePoint -= first->puissance / monsterSupp->resistance;
                           }
                           else
                             {
                               monsterSupp->lifePoint = 0;
                             }
                         }
                         break;
                  
                        case GREEN: 
                         if(times%first->cadence == 0)
                         {
                           if(monsterSupp->lifePoint >= first->puissance) 
                           {
                             monsterSupp->lifePoint  -= (first->puissance) / (monsterSupp->resistance);
                           }
                           else 
                           {
                             monsterSupp->lifePoint = 0;
                           }
                         }
                         break;
                  
                       case YELLOW:
                         if(times%first->cadence == 0)
                         {
                           if(monsterSupp->lifePoint >= first->puissance) 
                             {
                               monsterSupp->lifePoint  -= (first->puissance) / (monsterSupp->resistance);
                             }
                           else monsterSupp->lifePoint = 0;
                       }
                         break;
                      
                       case BLUE:
                         if(times%first->cadence== 0)
                         {
                           if(monsterSupp->lifePoint >= first->puissance) 
                             {
                               monsterSupp->lifePoint  -= (first->puissance) / (monsterSupp->resistance);
                             }
                           else 
                             {
                               monsterSupp->lifePoint = 0;
                             }
                         }
                         break;

                       default:
                         break;
                     }
                     actionTower = -1;
                   }
                 }
               //Remove monsters with no longer life points
                  if(monsterSupp->lifePoint <= 0)
                 {
                      printf("mort\n");
                      monsterTmp = monsterSupp;
                      monsterSupp = monsterSupp->next;
                      wave.list[i].m = delMonster(wave.list[i].m, monsterTmp);
                      // Multiplying money by the number of the wave so the more the game advances the more the user earns money
                      /*money += 50 * vague.nbListes;
                      sprintf(ch_money, "%d", money); // Conversion de l'entier
                      sprintf(ChaineFinale, "%s%s", ch_money, euro); 
                      nbDead ++;
                      */
/*                    }
                   else 
                   {
                        monsterSupp = (*monsterSupp).next;
                   }
              /* Le nombre de monstre est égale au nombre de monstre tués */
//             }
//           }
        /*times++;  

        if(nbDead == 60){
                    jeu->win = 1;
                  }
*/

/**************************************** AFFICHAGE DES INFOS DANS LA BULLE ********************************/
//       // Bulle d'info tout au long du jeu
//       if(info!=NULL){
//         /* On recupere la taille de la chaine de caractère afin de pouvoir régler l'affichage du texte*/ 
//         taille = strlen(info);
//         //printf("%d\n", taille );
//         if (typeTower==-1 && taille<= 20){
//           frogBulle(GLUT_BITMAP_HELVETICA_18, info, 540, 540);
//         }
//         else if(taille>= 23 && taille < 35 ) frogBulle(GLUT_BITMAP_HELVETICA_18, info, 558, 555);
//         else if (taille<35) frogBulle(GLUT_BITMAP_HELVETICA_18, info, 528, 540); 
//         else if (taille>=35) frogBulle(GLUT_BITMAP_HELVETICA_12, info, 528, 555);          
//       }

         /* affichage de l'money restant*/
         displayText(GLUT_BITMAP_9_BY_15, FinalStringMoney, 40, 560);

              //Construction des tours
              /*if(first !=NULL) 
              {
                constructTower(first);
              }
              // if (tourOver != NULL) drawBulle(tourOver);
              //    Affiche description de la tour laser
              // if(buttonOver == 1){ 
              //     drawDescription(description_laser, 5);
              // }
              // //Affiche description de la tour mitraillettes
              // if(buttonOver == 2){
              //     drawDescription(description_mitraillettes, 175);
              // }
              // //Affiche description de la tour rocket
              // if(buttonOver == 3){
              //   drawDescription(description_rocket, 350);
              // }
              // //Affiche description de la tour hybrides
              // if(buttonOver == 4){
              //     drawDescription(description_hybrides, 520);
              // }
  
                    /* Display the informations about the towers */
            if(jeu->red)
            {
                glTranslatef(-205,395,0);
                drawPicture(towerRedTex, 200, 200);
            }
            else if(jeu->blue)
            {
                glTranslatef(-205,395,0);
                drawPicture(towerBluTex, 200, 200);
            }
            else if(jeu->green)
            {
                glTranslatef(-205,395,0);
                drawPicture(towerGreTex, 200, 200);
            }
            else if(jeu->yellow)
            {
                glTranslatef(-205,395,0);
                drawPicture(towerYelTex, 200, 200);
            }
    }



    
        /* Affichage regles */
        else if(jeu->help){
             drawPicture(helpTex, 800, 600);
         }  
    

         /* Page d'accueil  */
        else{
          //glTranslatef(-600,0,0);
          drawPicture(accessTex, 800, 600);

        }










        
        /* Exchange of the front and the back buffer: update of the window */
        SDL_GL_SwapBuffers();
        
        /* Loop dealing with events */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
               if(e.type == SDL_QUIT) 
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

          /* Keyboard key */
          case SDL_KEYDOWN:
            switch(e.key.keysym.sym)
            {
                case 'a':
                    jeu->help=1;
                    break;
                case 's':
                    jeu->start=0;
                    break;
                case 'q':
                    loop=0;
                    break;
                case 'r':
                    jeu->start=0;
                    jeu->help=0;
                    break;
                default:
                    break;
            }       

          /* Mouse click */
          case SDL_MOUSEBUTTONUP:
            info=NULL;
            switch(e.button.button) {
              case SDL_BUTTON_LEFT:
                xClick = e.button.x;
                yClick = e.button.y;
                      //On vérifie si on peut construire sur la zone
                      if(jeu->start==0 && jeu->pause == 0 && jeu->win == 0 && jeu->lose == 0 )
                      {
                          printf("on rentre dans boucle1\n");

                          terrain = checkTowerPosition(first, xClick, yClick, map.colorConstruct.r, map.colorConstruct.g, map.colorConstruct.b);
                          //Si on se trouve dans la zone jeu et qu'une tour est sélectionnée
                          if(xClick < 600 && yClick<600 && typeTower != -1) 
                          {
                            printf("on rentre dans boucle2\n");
                            // Création des tours
                            if(first == NULL && terrain==1)
                            {
                                 printf("on rentre dans boucle3\n");
                                   first = createTower(xClick, yClick, typeTower);
                                    /* Achat de la tour*/
                                    money = money - first->cout;
                                    sprintf(str_money, "%d", money); // Conversion de l'entier
                                    sprintf(FinalStringMoney, "%s%s", str_money, yen); 
                            }
                            else if(terrain && ( ((typeTower == RED) && money>=500) || ((typeTower == GREEN) && money>=300) || 
                                ((typeTower ==YELLOW) && money>=250) || ((typeTower == BLUE) && money>=400)))
                            {                 
                                  tower = first;
                                  first = createTower(xClick, yClick, typeTower);
                                  first->next = tower;       
                                  money = money - first->cout; 
                                  sprintf(str_money, "%d", money); // Conversion de l'entier
                                  sprintf(FinalStringMoney, "%s%s", str_money, yen);          
                            }
                            else if(money<500 || money<1000)
                            {
                                  info = "Vous n'avez plus assez d'argent\npour acheter cette tour... ";
                                  printf("Vous n'avez plus d'argent\n");
                            }
                            else info = "Zone non constructible";     
                        }
                      else if(typeTower == -1) 
                      {
                         if(yClick > 550)  
                        {
                            info = "Zone non constructible";
                        }
                        info = "Choisissez une tour !";
                      }
            }
                //Lance le jeu, lorsque l'utilisateur clique sur le bouton jouer
                if(xClick > 225 && xClick < 580 && yClick >440 && yClick < 500)
                {
                 jeu->start = 0;
                 jeu->help=0;

                }
                //Lance les regles, lorsque l'utilisateur clique sur le bouton aide
                if(jeu->start == 1 && xClick > 285 && xClick < 515 && yClick > 520 && yClick < 570)
                {
                    jeu->help = 1;
                }
                printf("clic en (%d, %d)\n", e.button.x, e.button.y);
               
              break;
            }

            case SDL_MOUSEMOTION :
            xOver = e.motion.x;
            yOver = e.motion.y;

                      if(jeu->start==0 && xOver > 610 && xOver < 780 && yOver > 80 && yOver < 130)
                      {      
                        jeu->red=1;  
                      }
                      else
                      {
                        jeu->red=0;
                      }
                      
                      if(jeu->start==0 && xOver > 610 && xOver < 780 && yOver > 195 && yOver < 250)
                      {      
                        jeu->blue=1;  
                      }
                      else
                      {
                        jeu->blue=0;
                      }
                    
                      if(jeu->start==0 && xOver > 610 && xOver < 780 && yOver > 250 && yOver < 305)
                      {      
                        jeu->green=1;  
                      }
                      else
                      {
                        jeu->green=0;
                      }

                      if(jeu->start==0 && xOver > 610 && xOver < 780 && yOver > 135 && yOver < 190)
                      {      
                        jeu->yellow=1;  
                      }
                      else
                      {
                        jeu->yellow=0;
                      }

              break;
           
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
    glDelefirstxtures(1, &backgroundTex);
    //SDL_FreeSurface(screen);
    /* Release of resources associated with the SDL */
    SDL_Quit();
    
    return EXIT_SUCCESS;
}