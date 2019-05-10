#ifndef ITD_BAT__
#define ITD_BAT__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "struct.h"
#include "graphic.h"



/* ------- STRUCTURES ------- */

typedef enum{
	ENERGIE, ALIMENTATION
}BatType;

typedef struct str_bat
{
	//type of the bat
	BatType type;

	//price of the bat
	unsigned int cout;

	//field of action of the bat
	unsigned int portee;

	//position 
	int x;
	int y;

	struct str_bat* next;			
}Bat;




/* ------- FONCTIONS ------- */

//CREATE BAT
Bat* createBat(int x, int y, BatType type);

//CONSTRUCT BAT
void contructBat(Bat* bat);

//CHECK ZONE OF THE BAT POSITION
int checkBatPosition(Bat* t, int x, int y, int R, int G, int B);

//TYPE-BAT SELECTION
BatType selectBat(int xClick, int yClick);

//SELECT THE BAT
Bat* overBat(Bat* t, int x, int y);

//DISPLAY TOWER INFORMATIONS
void drawBatInformations(Bat* currentBat);

//DELETE TOWER
Bat* deleteBat(Bat* firstElement, Bat* t);

//DETECTION OF TOWER AROUND T HE BAT
// BatType detectTower(Bat* t, int x, int y);


#endif

