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
#include "jeu.h"
#include "struct.h"

#define WIDTH 800
#define HEIGHT 600

/*//Correspond a un dixième de seconde
static const Uint32 FRAMERATE_MILLISECONDS = 100;*/
/* Correspond a un centième de seconde */
static const Uint32 FRAMERATE_MILLISECONDS = 10;

int main(int argc, char** argv) {
  
  /* Initialization du jeu */
  Jeu* jeu;
  jeu = (Jeu*)malloc(sizeof(Jeu));
  jeu->start = 0;
  jeu->aide = 0;
  jeu->perdu = 0;
  jeu->gagne =0;
  jeu->pause = 0;
  jeu->regle = 0;
  Map map;
  //texture background
  GLuint backgroundTex;
  
  int xClick = 0, yClick = 0, xOver=0, yOver =0, buttonOver = 0;
  int terrain =0;
  int taille =0;
  int times=1;


  /* Argent */
  int argent = 2000;
  char ch_argent[10]; // Chaine de char qui stocke l'entier argent convertit en chaine de char
  char* euro = " EUROS";
  char ChaineFinale[20];

  /* Vague*/
  char ch_vague[10];
  char* totalVague = "/10 vagues";
  char ChaineFinaleVague[20];

  /* Initilaisation des tours */
  TowerType towerType = -1;
  Tower* tour = NULL;
  Tower* tete = NULL;
  Tower* tourOver = NULL;
  Tower* tourSuppr = NULL; 
  TowerType actionTour = -1;

  tourOver = (Tower*)malloc(sizeof(Tower));


  char* info = NULL;

  /* Initialisation des monstres */
  MonsterType typeMonstre = BLESSE;
  Monster* monstreSuppr = NULL;
  Monster* tmpMonstre = NULL;
  //char* imgMonstre ="images/monstre1.png";
  monstreSuppr = (Monster*)malloc(sizeof(Monster));
  tmpMonstre = (Monster*)malloc(sizeof(Monster));
  int nbMort = 0;
  int i;
  
  /* Affichage du budget du joueur */
  /* On convertir l'entier argent en chaine de caractere*/ 
  sprintf(ch_argent, "%d", argent); // Conversion de l'entier
  /* Concatenation de la chaine de caractere argent et de "Euro"*/
  sprintf(ChaineFinale, "%s%s", ch_argent, euro);
  printf("%s\n",ChaineFinale );

  
 

  // Initialisation SDL
   if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
      fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
      return EXIT_FAILURE;
   }

	//Initialisation Glut
	char *myargv [1];
	int myargc=1;
	myargv [0]=strdup("Myappname");
	glutInit(&myargc, myargv);
   
	SDL_Surface* screen = NULL;
	   if(NULL == (screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL |SDL_RESIZABLE))) {
		  fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		  return EXIT_FAILURE;
	   }

  /* 800 * 600 */
	reshape(WIDTH, HEIGHT);

	SDL_WM_SetCaption("Tower Defense by Alexandre Bordereau et Emilie Coulombel", NULL);

  // Chargement de la page d'accueil
  GLuint accueilTex = loadTexture("images/accueil.ppm");
  // Chaargement de la page gagné
  GLuint gagneTex = loadTexture("images/gagne.png");
  // Chaargement de la page perdu
  GLuint perduTex = loadTexture("images/perdu.png");
  // Chaargement de la page regles
  GLuint regleTex = loadTexture("images/regle.png");
  // Chaargement de la page aide
  GLuint aideTex = loadTexture("images/aide.png");
  // Chaargement de la page aide
  GLuint pauseTex = loadTexture("images/pause.png");


  // Chargement de la carte itd
  char* filename = "images/image.ppm";
  map = loadMap("data/carte.itd");  
  SDL_Surface* background = loadImage(filename);
  backgroundTex = loadTexture(filename);

  //Chargement des boutons tours
  GLuint bt_laser= loadTexture("images/bt_laser.png");
  GLuint bt_mitraillettes= loadTexture("images/bt_mitraillettes.png");
  GLuint bt_rocket= loadTexture("images/bt_rocket.png");
  GLuint bt_hybrides= loadTexture("images/bt_hybrides.png");

  //Chargement des descriptions des tours
  GLuint description_laser= loadTexture("images/description_laser.png");
  GLuint description_mitraillettes= loadTexture("images/description_mitraillettes.png");
  GLuint description_rocket= loadTexture("images/description_rocket.png");
  GLuint description_hybrides= loadTexture("images/description_hybrides.png");
  
  // Chargement des boutons menu
  GLuint menuAction= loadTexture("images/menu.png");

  /* On recupere les coordonnées des noeuds*/
  Node* n;
  n = (Node*)malloc(sizeof(Node));
  n = map.listeNoeud;
  int coordNoeudX = n->x;
  int coordNoeudY = n->y;

  // Création d'un monstre
  Monster* monstre = createMonster(typeMonstre, n->next, coordNoeudX, coordNoeudY);
  // Création de liste de monstre
  listeMonstre lMonstre;
  lMonstre.m = monstre;
  lMonstre.nbMonstre = 1;
  
  Vague vague;
  vague.nbListes = 1;
  // Création du tableau de liste de monstre
  vague.liste[vague.nbListes - 1] = lMonstre;

  sprintf(ch_vague, "%d", vague.nbListes); // Conversion de l'entier
  sprintf(ChaineFinaleVague, "%s%s", ch_vague, totalVague);
  printf("%s\n",ChaineFinaleVague );


  int loop = 1;
  while(loop) {
  Uint32 startTime = SDL_GetTicks();
  
  /* dessin */
  glClear(GL_COLOR_BUFFER_BIT);

    /* Si l'utilisateur click sur jouer*/
    if(jeu->start && jeu->pause == 0 && jeu->aide == 0 && jeu->gagne == 0 && jeu->perdu == 0 && jeu->gagne == 0 && jeu->regle ==0) {
    
    //On dessine un rectangle qui a pour texture la carte
    drawPicture(backgroundTex, background->w, background->h);
    //On trace le chemin avec les couleurs du .itd et les coordonnées des noeuds
    glColor3ub(map.couleurChemin.r, map.couleurChemin.g, map.couleurChemin.b);
    drawChemin(n);

    // Zone constructible
    // Couleur des zones constructible
    glColor3ub(map.couleurConstruct.r, map.couleurConstruct.g, map.couleurConstruct.b);
    glPushMatrix();
    glTranslatef(10,220,0);
    dessinCarre(160,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(230,330,0);
    dessinCarre(200,80);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(230,410,0);
    dessinCarre(70,150);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,90,0);
    dessinCarre(160,170);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(510,150,0);
    dessinCarre(160,200);
    glPopMatrix();

    glColor3ub(255,255,255);

    /* Info sur le type de tour sélectionné */     
     if(info == NULL){ 
      switch(towerType){
          case ROCKET:
            frogBulle(GLUT_BITMAP_HELVETICA_12, "Vous disposez d'une tour rocket\nTrouvez lui un emplacement !\nAttention une fois la tour placee\n1000 euros vous seront retires", 528, 570);
          break;
      case LASER :
          frogBulle(GLUT_BITMAP_HELVETICA_12, "Vous disposez d'une tour laser\nTrouvez lui un emplacement !\nAttention une fois la tour placee\n500 euros vous seront retires", 528, 570);
          break;  
        case MITRAILLETTE :
          frogBulle(GLUT_BITMAP_HELVETICA_10, "Vous disposez d'une tour mitraillettes\nTrouvez lui un emplacement !\nAttention une fois la tour placee\n1000 euros vous seront retires ", 528, 570);
          break;
        case HYBRIDE :  
          frogBulle(GLUT_BITMAP_HELVETICA_12, "Vous disposez d'une tour hybrides\nTrouvez lui un emplacement !\nAttention une fois la tour placee\n500 euros vous seront retires ", 528, 570);
          break;
        default:
          break;
      }
    }
    

    /* Selection du type de monstre en fonction du nombre de vague */
    typeMonstre = chooseMonstre(vague);
    // Création d'un monstre
    Monster* newMonstre = createMonster(typeMonstre, n->next, coordNoeudX, coordNoeudY);
      /* Gestion des listes de liste de monstres*/
      if(times%600 == 0  && vague.nbListes < 10 ) {
          //SDL_Delay(1000);  //1000 millisecondes = 1 seconde ; faire pause :
          listeMonstre listeM;
          monstre = newMonstre;
          listeM.m = monstre;
          lMonstre = listeM;
          lMonstre.nbMonstre = 1;
          vague.nbListes +=1;
          vague.liste[vague.nbListes - 1]= lMonstre;
          /* convertion pour l'affichage du nombre de vague*/
          sprintf(ch_vague, "%d", vague.nbListes); // Conversion de l'entier
          sprintf(ChaineFinaleVague, "%s%s", ch_vague, totalVague);
      }
      /* Création liste de monstre times permet de faire une pause afin d'espacer les monstres*/
      else if(times%60 == 0/*startTime - last_time > 2000*/ && lMonstre.nbMonstre<6){
            //last_time = startTime;
            monstre = ajoutMonstre(monstre, newMonstre);
            vague.liste[vague.nbListes - 1].m = monstre;
            lMonstre.nbMonstre +=1;
            //printf("%d\n", startTime);
      }
      /* On dessine la vague de monstres */    
      drawListMonster(vague, jeu);
      /* affichage du numéro de vague*/
      affichageTexte(GLUT_BITMAP_TIMES_ROMAN_24, ChaineFinaleVague, 10,100);

    
    //On dessine les boutons pour placer les tours
    glPushMatrix();
    glTranslatef(5,5,0);
    drawPicture(bt_laser, 161 , 52); 
    glTranslatef(170,0,0);
    drawPicture(bt_mitraillettes, 161 , 52);
    glTranslatef(170,0,0);
    drawPicture(bt_rocket, 161 , 52);
    glTranslatef(170,0,0);
    drawPicture(bt_hybrides, 161 , 52);
    glTranslatef(170,5,0);
    drawPicture(menuAction,121 , 39);
    glPopMatrix();



      

          
      /* Suppression d'une tour */
       if(tourSuppr != NULL)  tete = desctructTour(tete, tourSuppr);
 

/*************************************** ACTION TOUR / MONSTRE ************************************/
        /* permet d'afficher les listes de monstres du tableau */
        for(i = 0; i < vague.nbListes; i++) {   
          monstreSuppr = vague.liste[i].m; 
          while(monstreSuppr != NULL) { 
            // Si la tour a détecter un monstre on retourne le type de la tour*/
            actionTour = detectMonstre(tete, (*monstreSuppr).coord.x, (*monstreSuppr).coord.y);
              if(actionTour!=-1){ 
                if(monstreSuppr->point_de_vie > 0){
                  switch(actionTour){
                    case ROCKET:
                      // On regle la cadence grace au modulo
                      if(times%tete->cadence== 0){
                        /* Pour la resistance on divise la puissance de la tour par la résistance du monstre (+ sa résistance est grande moins la tour aura d'impact) */
                        if(monstreSuppr->point_de_vie >= tete->puissance) monstreSuppr->point_de_vie -= tete->puissance / monstreSuppr->resistance;
                        else monstreSuppr->point_de_vie = 0;
                      }
                      break;
                  
                    case LASER: 
                      if(times%tete->cadence == 0){
                        if(monstreSuppr->point_de_vie >= tete->puissance) monstreSuppr->point_de_vie  -= tete->puissance/ monstreSuppr->resistance;
                        else monstreSuppr->point_de_vie = 0;
                      }
                      break;
                  
                    case MITRAILLETTE:
                      if(times%tete->cadence == 0){
                        if(monstreSuppr->point_de_vie >= tete->puissance) monstreSuppr->point_de_vie  -= tete->puissance/ monstreSuppr->resistance;
                        else monstreSuppr->point_de_vie = 0;
                    }
                      break;
                      
                    case HYBRIDE:
                      if(times%tete->cadence== 0){
                        if(monstreSuppr->point_de_vie >= tete->puissance) monstreSuppr->point_de_vie  -= tete->puissance/ monstreSuppr->resistance;
                        else monstreSuppr->point_de_vie = 0;
                     }
                      break;

                    default:
                      break;
                  }
                  actionTour = -1;
                }
              }
            // On supprime les monstres qui n'ont plus de point de vie
            if(monstreSuppr->point_de_vie<=0){
                printf("mort\n");
                tmpMonstre = monstreSuppr;
                monstreSuppr = monstreSuppr->next;
                vague.liste[i].m = supprimeMonstre(vague.liste[i].m, tmpMonstre);
                //On multiplie l'argent par le numéro de la vague comme ca plus le jeu avance plus l'utilisateur gagne de l'argent
                argent += 50 * vague.nbListes;
                sprintf(ch_argent, "%d", argent); // Conversion de l'entier
                sprintf(ChaineFinale, "%s%s", ch_argent, euro); 
                nbMort ++;

              }
              else monstreSuppr = (*monstreSuppr).next;
              /* Le nombre de monstre est égale au nombre de monstre tués */

          }
        }

        times++;  

        if(nbMort == 60){
                    jeu->gagne = 1;
                  }


/**************************************** AFFICHAGE DES INFOS DANS LA BULLE ********************************/
      // Bulle d'info tout au long du jeu
      if(info!=NULL){
        /* On recupere la taille de la chaine de caractère afin de pouvoir régler l'affichage du texte*/ 
        taille = strlen(info);
        //printf("%d\n", taille );
        if (towerType==-1 && taille<= 20){
          frogBulle(GLUT_BITMAP_HELVETICA_18, info, 540, 540);
        }
        else if(taille>= 23 && taille < 35 ) frogBulle(GLUT_BITMAP_HELVETICA_18, info, 558, 555);
        else if (taille<35) frogBulle(GLUT_BITMAP_HELVETICA_18, info, 528, 540); 
        else if (taille>=35) frogBulle(GLUT_BITMAP_HELVETICA_12, info, 528, 555);          
      }

      /* affichage de l'argent restant*/
      affichageTexte(GLUT_BITMAP_TIMES_ROMAN_24, ChaineFinale, 10,570);

      //Construction des tours
      if(tete !=NULL) constructTower(tete);
      if (tourOver != NULL) drawBulle(tourOver);
        //Affiche description de la tour laser
      if(buttonOver == 1){ 
          drawDescription(description_laser, 5);
      }
      //Affiche description de la tour mitraillettes
      if(buttonOver == 2){
          drawDescription(description_mitraillettes, 175);
      }
      //Affiche description de la tour rocket
      if(buttonOver == 3){
        drawDescription(description_rocket, 350);
      }
      //Affiche description de la tour hybrides
      if(buttonOver == 4){
          drawDescription(description_hybrides, 520);
      }
  
  
}

/* Affichage de l'aide de la page d'accueil*/
else if(jeu->aide){
   drawPicture(aideTex, background->w, background->h);
}
/* Si l'utilisateur gagne */
  else if(jeu->gagne){
    drawPicture(gagneTex, background->w, background->h);
  }
/* menu pause */
else if(jeu->pause){
  drawPicture(pauseTex, background->w, background->h);
}
/* Si l'utilisateur perd */
else if(jeu->perdu){
    drawPicture(perduTex, background->w, background->h);
}
/* Affichage regles */
else if(jeu->regle){
    drawPicture(regleTex, background->w, background->h);
}   
 /* Page d'accueil */   
else{
  drawPicture(accueilTex, background->w, background->h);
}



SDL_GL_SwapBuffers();
    
    /*Gestion des events*/
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      switch(e.type) {
        case SDL_KEYDOWN:
            switch(e.key.keysym.sym) {
              //Aide
              case 'a' :
                jeu->aide = 1;
                break;
              //Commencer le jeu
              case 'c' :
                jeu->start = 1;
                break;
              //Quitter le jeu
              case 'q' :
                loop = 0;
                break;
              //Retour
              case 'r' :
                jeu->aide = 0;
                jeu->pause = 0;
                jeu->regle = 0;
                break;
              case SDLK_ESCAPE: 
                loop = 0;
                break;
              default: 
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
          info=NULL;
          switch(e.button.button) {
            case SDL_BUTTON_LEFT:
              xClick = e.button.x;
              yClick = e.button.y;
              //printf("%d %d\n", xClick, yClick);
                
/******************************************* MENU ****************************************/
                //Si y > 550, on se trouve dans la zone des boutons
                if(yClick > 550){
                  //Bouton de selection du type de tour
                   towerType = selectTour(xClick, yClick);
                      //Bouton Aide
                      if(xClick > 690 && xClick < 720 && yClick > 550 && yClick < 590){
                        jeu->aide = 1;
                      }
                      //Bouton Pause
                      if(xClick > 725 && xClick < 755 && yClick > 550 && yClick < 590){
                        jeu->pause = 1;

                      }
                      //Bouton quitter
                      if(xClick > 760 && xClick < 790 && yClick > 550 && yClick < 590){
                        loop = 0;
                      }
                }
/******************************************** JEU *****************************************/
                      //On vérifie si on peut construire sur la zone
                      if(jeu->start && jeu->pause == 0 && jeu->aide == 0 && jeu->gagne == 0 && jeu->perdu == 0 && jeu->gagne == 0 && jeu->regle ==0){
                      terrain = verifPositionTower(tete, xClick, yClick, map.couleurConstruct.r, map.couleurConstruct.g, map.couleurConstruct.b);
                      //Si on se trouve dans la zone jeu et qu'une tour est sélectionnée
                      if(yClick < 550 && towerType != -1) 
                      {
                        // Création des tours
                        if(tete == NULL && terrain){
                                tete = createTower(xClick, yClick, towerType);
                                /* Achat de la tour*/
                                argent = argent - tete->cout;
                                sprintf(ch_argent, "%d", argent); // Conversion de l'entier
                                sprintf(ChaineFinale, "%s%s", ch_argent, euro); 
                        }
                        else if(terrain && (((towerType == LASER || towerType == HYBRIDE) && argent>=500) ||  ((towerType == ROCKET || towerType == MITRAILLETTE) && argent>=1000))){                 
                              tour = tete;
                              tete = createTower(xClick, yClick, towerType);
                              tete->next = tour;       
                              argent = argent - tete->cout; 
                              sprintf(ch_argent, "%d", argent); // Conversion de l'entier
                              sprintf(ChaineFinale, "%s%s", ch_argent, euro);            
                        }
                        else if(argent<500 || argent<1000){
                              info = "Vous n'avez plus assez d'argent\npour acheter cette tour... ";
                              printf("Vous n'avez plus d'argent\n");
                        }
                        else info = "Zone non constructible";     
              }
              else if(towerType == -1) {
                 if(yClick > 550)  info = "Zone non constructible";;
                  info = "Choisissez une tour !";
              }
            }
              //Lance le jeu, lorsque l'utilisateur clique sur le bouton jouer
              if(yClick >128 && yClick < 180 && xClick > 280 && xClick < 520){
                jeu->start = 1;
              }
              //Lance les regles, lorsque l'utilisateur clique sur le bouton aide
              if(jeu->start == 0 && xClick > 285 && xClick < 515 && yClick > 220 && yClick < 280){
              jeu->regle = 1;
              }
              break;
          case SDL_BUTTON_RIGHT:
              //xClickR = e.button.x;
              //yClickR = e.button.y;
              //printf("%d %d\n", xClickR, yClickR);
              /* Selection de la tour à supprimer */
              tourSuppr = overTour(tete, xOver, yOver);
              if(tourSuppr != NULL){
                // Argent gagné grace a la suppression de la tour*/
                argent += tourSuppr->cout;
                sprintf(ch_argent, "%d", argent); // Conversion de l'entier
                sprintf(ChaineFinale, "%s%s", ch_argent, euro);  
              }   
          default:   
            break;
            }
        case SDL_MOUSEMOTION :
            xOver = e.motion.x;
            yOver = e.motion.y;
            tourOver = overTour(tete, xOver, yOver); 
              /* On affiche la description des tours au survol du bouton */              
              buttonOver = descriptionTour(xOver, yOver); 
                      //Bouton Aide
                      if(xOver > 690 && xOver < 720 && yOver > 550 && yOver < 590){
                        info = "Clickez pour \nobtenir de l'aide";
                      }
                      //Bouton Pause
                      else if(xOver > 725 && xOver < 755 && yOver > 550 && yOver < 590){
                        info = "Clickez pour \nfaire une pause";
                      }
                      //Bouton quitter
                      else if(xOver > 760 && xOver < 790 && yOver > 550 && yOver < 590){
                        info = "Clickez pour \nquitter le jeu";
                      }
                      else if ((yOver < 550 && yOver > 535) || (xOver < 690 && yOver > 550)) info = NULL;
              break;
        }                 
    }
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  free(n);
  free(tourOver);
  free(tour);
  if (jeu->gagne == 0) free(monstre);
  if (jeu->gagne == 0) free(jeu);
  SDL_FreeSurface(background);
  //Suppression de la texture du background
  glDeleteTextures(1, &backgroundTex);
  SDL_FreeSurface(screen);
  /* Liberation des ressources associées à la SDL */ 
  SDL_Quit();
  return EXIT_SUCCESS;
}