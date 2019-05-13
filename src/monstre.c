#include "monstre.h"

/* CREATE  NEW MONSTER */
Monster* createMonster(MonsterType type, Node* next, float x, float y){
	if (next == NULL)
	{
		fprintf(stderr, "ERROR\n");
		exit(1);
	}

	Monster* monster = (Monster*)malloc(sizeof(Monster));

	if(monster == NULL) {
		fprintf(stderr, "MEMORY ERROR\n");
		exit(1);
	}

	monster->type = type;
	monster->x = x;
	monster->y = y;
	monster->node_next = next;

	switch(type){

		case CAT_1 :
			monster->lifePoint = 40;
			monster->resistance = 1;
			monster->speed = 1;
			monster->imageMonster = "images/cat_1.png";
			monster->profit= 50;
			break;

		case CAT_2:
			monster->lifePoint = 50;
			monster->resistance = 2;
			monster->speed = 2;
			monster->imageMonster = "images/cat_2.png";
			monster->profit= 70;
			break;

		case CAT_3:
			monster->lifePoint = 100;
			monster->resistance = 7;
			monster->speed = 2;
			monster->imageMonster = "images/cat_3.png";
			monster->profit= 70;
			break;

		case CAT_4:
			monster->lifePoint = 40;
			monster->resistance = 3;
			monster->speed = 5;
			monster->imageMonster = "images/cat_4.png";
			monster->profit= 100;
			break;

		default:
			break;
		}

	monster->node_next = NULL;
	return monster;
}

/* CHOOSE THE TYPE OF MONSTER */
MonsterType chooseMonster(Wave wave){
	MonsterType type;
	switch(wave.nbLists){
		case 1:
			type = CAT_1;
		break;
		case 2:
			type =  CAT_2;
		break;
		case 3:
			type =  CAT_3;
		break;
		case 4:
			type = CAT_4;
		break;

		default:
		break;
	}
	return type;
}

/* CREATE A NEW LIST */
int createList(Wave wave, Jeu* jeu) {
	Monster* m;
	
	for (int i = 0; i < wave.nbLists; ++i)
	{
		m = wave.list[i].m;
		while(m!=NULL) {
			m = m->next;
		}
	}

return 1;
}

/* DRAW MONSTER */
int drawMonster(Monster* monster, Jeu* jeu){
	SDL_Surface* Monster= loadImage(monster->imageMonster);
	GLuint monsterTex= loadTexture(monster->imageMonster);
	if(monster->node_next != NULL)
	{
		if(monster->node_next->y == monster->y)
		{
			if(monster->node_next->x > monster->x)
			{
				monster->x +=1 * monster->speed;
			}
			else{
				monster->x -=1 * monster->speed;
			}
		}
		
		else{
			if(monster->node_next->y > monster->y)
			{
				monster->y +=1 * monster->speed;
			}
			else{
				monster->y -=1 * monster->speed;
			}
		}
		if(monster->node_next->x == monster->x && monster->node_next->y == monster->y)
		{
			monster->node_next=monster->node_next->next;
		}
	
	if(monster->node_next == NULL)
	{
		printf("PERDU :(\n");
		jeu->lose=1;
	}




return 1;

}
else return 0;
}


Monster* newMonster(Monster* listMonster, Monster* newMonster) {
	if (listMonster == NULL)
	{
		fprintf(stderr, "listMonster is NULL" );
		return NULL;
	}

	if (newMonster == NULL)
	{
		fprintf(stderr, "newMonster is NULL" );
		exit(1);
	}

	newMonster->next = listMonster;

	return newMonster;
}

Monster* delMonster(Monster* listMonster, Monster* monster){
	if (listMonster == NULL){
		fprintf(stderr, "listmonster is NULL" );
		exit(1);
	}

	Monster* m = listMonster;
	Monster* delMonster;

	if (listMonster == monster)
	{
		delMonster = listMonster;
		if (listMonster->next != NULL) 
		{
			listMonster = listMonster->next;
			free(delMonster);
			return listMonster;
		}
		else {
			free(delMonster);
			return NULL;
		}
	}

	while(listMonster->next != NULL){
		if(listMonster->next == monster) {
			delMonster = listMonster->next;
			if (delMonster->next != NULL)
			{
				listMonster->next = delMonster->next;
			}
			else {
				listMonster->next = NULL;
				break;
			}
			free(delMonster);
		}
		listMonster = listMonster->next;
	}
	return m;
}