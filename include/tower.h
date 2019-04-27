#ifndef ITD_TOWER__
#define ITD_TOWER__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "struct.h"



/* ------- STRUCTURES ------- */

typedef enum{
	RED, GREEN, YELLOW, BLUE
}TowerType

typedef struct str_tower
{
	//type of the tower
	TowerType type;

	//power of the tower
	unsigned int puissance;

	//field of action of the tower
	unsigned int portee;

	//firing rate of the tower
	int cadence;

	//price of the tower
	unsigned int cout;

	//position 
	int x;
	int y;

	struct str_tower* next;			
}Tower;




/* ------- FONCTIONS ------- */

//CREATE TOWER
Tower* createTower(int x, int y, TowerType type);

//CONSTRUCT TOWER
void contructTower(Tower* tower);

//CHECK ZONE OF THE TOWER POSITION
int checkTowerPosition(Tower* t, int x, int y, int R, int G, int B);

//TYPE-TOWER SELECTION
TowerType selectTower(int xClick, int yClick);

//SELECT THE TOWER
Tower* overTour(Tower* t, int x, int y);

//DISPLAY TOWER INFORMATIONS
void drawTowerInformations(Tower* currentTower);

//DELETE TOWER
Tower* deleteTower(Tower* firstElement, Tower* t);

//DETECTION OF MONSTER AROUND THE TOWER
TowerType detectMonster(Tower* t, int x, int y);


#endif

// Les tours sont de quatre types :

// • Les tours de type rouge : Type rocket. Ces tours infligent beaucoup de d ́egˆats mais ont une
// cadence de feu faible.

// • Les tours de type vert : Type laser. Elles tirent tr`es rapidement mais ont une faible port ́ee et
// occasionne des dommages moyens.

// • Les tours de type jaune : Elles occasionnent peu de d ́egˆat, ont une port ́ee tr`es limit ́e mais une
// bonne cadence de tir et tirent sur tous les monstres `a leur port ́ee.

// • Les tours de type bleue : Elles ont une tr`es bonne port ́ee et une bonne cadence de tir mais
// occasionnent peu de d ́egˆats.