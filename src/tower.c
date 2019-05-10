#include "tower.h"

/* ------- TOWER CREATION ------- */
Tower* createTower(int x, int y, TowerType type){

	Tower* tower = (Tower*)malloc(sizeof(Tower));

	if(tower == NULL) {
		fprintf(stderr, "MEMORY ERROR\n");
		exit(1);
	}

	tower->type = type;
	tower->x = x;
	tower->y = y;
	tower->next = NULL;

	switch(type){

		case RED :
			tower->puissance = 100;
			tower->cadence = 10; //every second
			tower->cout = 500;
			tower->portee= 300;
			break;

		case GREEN:
			tower->puissance = 50;
			tower->cadence = 50; //every 200ms
			tower->cout = 300;
			tower->portee= 200;
			break;

		case YELLOW:
			tower->puissance = 30;
			tower->cadence = 30; //every 600ms
			tower->cout = 250;
			tower->portee= 100;
			break;

		case BLUE:
			tower->puissance = 30;
			tower->cadence = 30; //every 400ms
			tower->cout = 400;
			tower->portee= 40;
			break;

		default:
			break;
		}

	return tower;
}

/* ------- TOWER CONSTRUCTION ------- */


//TOWER SELECTION FONCTION
TowerType selectTower( xClick,  yClick){
	TowerType T;

	
	//Red tower selection
	if (xClick > 610 && xClick < 780 && yClick >80 && yClick<130)
	{
		T=RED;
	}

	//Green tower selection
	if (xClick > 610 && xClick < 780 && yClick > 250 && yClick < 305)
	{
		T=GREEN;
	}

	//Yellow tower selection
	if (xClick > 610 && xClick < 780 && yClick > 135 && yClick < 190)
	{
		T=YELLOW;
	}

	//Blue tower selection
	if (xClick > 610 && xClick < 780 && yClick > 195 && yClick < 250)
	{
		T=BLUE;
	}
	else T=-1;
	return T;
}

//TOWER CONSTRUCTION FONCTION + TEXTURES

void constructTower(Tower* tower){
	GLuint towerTexture;
	Tower* current = tower;
	while(current !=NULL) {
		switch(current->type){
			case RED:
				towerTexture = loadTexture("images/tower_red.png");
				break;
			case GREEN:
				towerTexture = loadTexture("images/tower_green.png");
				break;
			case YELLOW:
				towerTexture = loadTexture("images/tower_yellow.png");
				break;
			case BLUE:
				towerTexture = loadTexture("images/tower_blue.png");
				break;
			default:
				break;
		}

		int y = 600 - (current->y);

		glPushMatrix();
		glTranslatef(current->x, y,0);
		drawPicture(towerTexture, 60, 60); //taille tour
		glPopMatrix();

		current = current->next;
	}
}

/* ------- CHECK TOWER POSITION ------- */

//vérifie si déja une tour placée
int checkTowerPosition(Tower* tower, int x, int y, int R, int G, int B){
	Tower* currentTower = tower;
	char color[3];

	while(currentTower != NULL){
		if (x>=(currentTower->x - 60) && x<=(currentTower->x+60) && y>= (currentTower->y-60) && y<=(currentTower->y+60))
		{
			fprintf(stderr, "Impossible de placer une tour ici" );
			return 0;
		}
		else{
			currentTower = (*currentTower).next;
		}
	}

	int positionY = 600-y;
	glReadPixels(x,positionY,1,1,GL_RGB, GL_UNSIGNED_BYTE,color);
	if (color[0] != R && color[1] != G && color[2] != B) {}
	{
		fprintf(stderr, "Impossible de placer la tour hors du terrain\n");
		return 0;
	}

	return 1;
}


/* ------- SELECT TOWER ------- */
Tower* overTour(Tower* t, int x, int y) {
	if (t != NULL)
	{
		Tower* currentTower = t;
		while(currentTower != NULL) {
			if (x>=(currentTower->x) && x<=(currentTower->x+60) && y>= (currentTower->y-60) && y<=(currentTower->y))
			{
				return currentTower;
			}
			else {
				currentTower = (*currentTower).next;
			}
		}
	}
}

/* ------- DISPLAY TOWER INFOS ------- */
void drawTowerInformations(Tower* currentTower){
	GLuint towerInfo;
	switch(currentTower->type){
			case RED:
				towerInfo = loadTexture("images/tower_red_info.png");
				break;
			case GREEN:
				towerInfo = loadTexture("images/tower_green_info.png");
				break;
			case YELLOW:
				towerInfo = loadTexture("images/tower_yellow_info.png");
				break;
			case BLUE:
				towerInfo = loadTexture("images/tower_blue_info.png");
				break;
			default:
				break;
	}

	glPushMatrix();
	glTranslatef(500,450,0); //position info bulle image
	drawPicture(towerInfo,200,150); //taille info bulle image
	glPopMatrix();

}

/* ------- DELETE TOWER  ------- */
Tower* deleteTower(Tower* firstElement, Tower* t){
	if (firstElement == NULL)
	{
		return NULL;
	}

	Tower* tower = firstElement;
	Tower* delTower;

	if (t == firstElement)
	{
		delTower = t;

		if (firstElement->next !=NULL)
		{
			firstElement = firstElement->next;
			free(delTower);
			return firstElement;
		}
		else {
			free(delTower);
			return NULL;
		}
	}

	while(firstElement != NULL) {
		if(firstElement->next == t) {
			delTower = firstElement->next;

			if (delTower->next != NULL)
			{
				firstElement->next= delTower->next;
			}
			else {
				firstElement->next = NULL;
				break;
			}
			free(delTower);
		}
		firstElement = firstElement->next;
	}
	return tower;
}

/* ------- DETECT MONSTER AROUND TOWER POSITION ------- */

TowerType detectMonster(Tower* t, int x, int y){
	TowerType type = -1;
	if (t!=NULL)
	{
		Tower* current = t;
		while(current != NULL) {
			//calcul de la portée 
			float distance = sqrt(((current->x - x)*(current->x - x)) + ((current->y - y)*(current->y - y)));

			if (distance <= current->portee) {
				type = current->type;
				glBegin(GL_LINES);
					glLineWidth(10); //tirs
					glVertex2f(current->x,600- current->y); //depart
					glVertex2f(x,600-y);//arrivée
				glEnd();
				return type;

			}
			else {
				type = -1;
			}
			current = current->next;
		}
	}

	return type;
}


