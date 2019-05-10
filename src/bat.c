#include "bat.h"

/* ------- BAT CREATION ------- */
Bat* createBat(int x, int y, BatType type){

	Bat* bat = (Bat*)malloc(sizeof(Bat));

	if(bat == NULL) {
		fprintf(stderr, "MEMORY ERROR\n");
		exit(1);
	}

	bat->type = type;
	bat->x = x;
	bat->y = y;
	bat->next = NULL;

	switch(type){

		case ENERGIE :
			bat->cout = 500;
			break;

		case ALIMENTATION:
			bat->cout = 500;

			break;

		default:
			break;
		}

	return bat;
}

/* ------- BAT CONSTRUCTION ------- */


//BAT SELECTION FONCTION
BatType selectBat( xClick,  yClick){
	BatType T;

// !!!!! A METTRE A JOUR EN FONCTION PLACEMENT BOUTON !!!!//
	
	//ENERGIE selection
	if (xClick > 610 && xClick < 780 && yClick >550 && yClick<590)
	{
		T=ENERGIE;
	}

	//ALIMENTATION selection
	if (xClick > 610 && xClick < 780 && yClick > 420 && yClick < 480)
	{
		T=ALIMENTATION;
	}

	else T=-1;
	return T;
}

//BAT CONSTRUCTION FONCTION + TEXTURES

void constructBat(Bat* bat){
	GLuint batTexture;
	Bat* current = bat;
	while(current !=NULL) {
		switch(current->type){
			case ENERGIE:
				batTexture = loadTexture("images/bat_energie.png");
				break;
			case ALIMENTATION:
				batTexture = loadTexture("images/bat_amelioration.png");
				break;
			default:
				break;
		}

		int y = 600 - (current->y);

		glPushMatrix();
		glTranslatef(current->x, y,0);
		drawPicture(batTexture, 60, 60); //taille bat
		glPopMatrix();

		current = current->next;
	}
}

/* ------- CHECK BAT POSITION ------- */

//vérifie si déja un batiment placé
int checkBatPosition(Bat* bat, int x, int y, int R, int G, int B){
	Bat* currentBat = bat;
	char color[3];

	while(currentBat != NULL){
		if (x>=(currentBat->x - 60) && x<=(currentBat->x+60) && y>= (currentBat->y-60) && y<=(currentBat->y+60))
		{
			fprintf(stderr, "Impossible de placer un batiment ici" );
			return 0;
		}
		else{
			currentBat = (*currentBat).next;
		}
	}

	int positionY = 600-y;
	glReadPixels(x,positionY,1,1,GL_RGB, GL_UNSIGNED_BYTE,color);
	if (color[0] != R && color[1] != G && color[2] != B) {}
	{
		fprintf(stderr, "Impossible de placer un batiment hors du terrain\n");
		return 0;
	}

	return 1;
}


/* ------- SELECT BAT ------- */
Bat* overBat(Bat* b, int x, int y) {
	if (b != NULL)
	{
		Bat* currentBat = b;
		while(currentBat != NULL) {
			if (x>=(currentBat->x) && x<=(currentBat->x+60) && y>= (currentBat->y-60) && y<=(currentBat->y))
			{
				return currentBat;
			}
			else {
				currentBat = (*currentBat).next;
			}
		}
	}
}

// /* ------- DISPLAY bat INFOS ------- */
// void drawTowerInformations(Bat* currentTower){
// 	GLuint towerInfo;
// 	switch(currentTower->type){
// 			case RED:
// 				towerInfo = loadTexture("images/tower_red_info.png");
// 				break;
// 			case GREEN:
// 				towerInfo = loadTexture("images/tower_green_info.png");
// 				break;
// 			case YELLOW:
// 				towerInfo = loadTexture("images/tower_yellow_info.png");
// 				break;
// 			case BLUE:
// 				towerInfo = loadTexture("images/tower_blue_info.png");
// 				break;
// 			default:
// 				break;
// 	}

// 	glPushMatrix();
// 	glTranslatef(500,450,0); //position info bulle image
// 	drawPicture(towerInfo,200,150); //taille info bulle image
// 	glPopMatrix();

// }

/* ------- DELETE TOWER  ------- */
Bat* deleteBat(Bat* firstElement, Bat* t){
	if (firstElement == NULL)
	{
		return NULL;
	}

	Bat* bat = firstElement;
	Bat* delBat;

	if (t == firstElement)
	{
		delBat = t;

		if (firstElement->next !=NULL)
		{
			firstElement = firstElement->next;
			free(delBat);
			return firstElement;
		}
		else {
			free(delBat);
			return NULL;
		}
	}

	while(firstElement != NULL) {
		if(firstElement->next == t) {
			delBat = firstElement->next;

			if (delBat->next != NULL)
			{
				firstElement->next= delBat->next;
			}
			else {
				firstElement->next = NULL;
				break;
			}
			free(delBat);
		}
		firstElement = firstElement->next;
	}
	return bat;
}

/* ------- DETECT TOWER AROUND BAT POSITION ------- */

// BatType detectTower(Bat* t, int x, int y){
	
// }


