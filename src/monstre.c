#include "monstre.h"

/* CREATE A NEW MONSTER */
Monster* createMonster(MonsterType type, Node* next, float x, float y){
	if (node_next == NULL)
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
			monster->pointPlayer= 2;
			monster->profit= 50;
			break;

		case CAT_2:
			monster->lifePoint = 50;
			monster->resistance = 2;
			monster->speed = 2;
			monster->imageMonster = "images/cat_2.png";
			monster->pointPlayer= 2;
			monster->profit= 70;
			break;

		case DOG_ROBOT_1:
			monster->lifePoint = 100;
			monster->resistance = 7;
			monster->speed = 2;
			monster->imageMonster = "images/dog_robot_1.png";
			monster->pointPlayer= 2;
			monster->profit= 70;
			break;

		case DOG_ROBOT_2:
			monster->lifePoint = 40;
			monster->resistance = 3;
			monster->speed = 5;
			mmonster->imageMonster = "images/dog_robot_2.png";
			monster->pointPlayer= 2;
			monster->profit= 100;
			break;

		default:
			break;
		}

	monstre->node_next = NULL;
	return monstre;
}

/* CHOOSE THE TYPE OF MONSTER */
MonsterType chooseMonster(Wave wave){
	MonsterType type;
	switch(vague.nbListes){
		case 1:
			type = CAT_1;
		break;
		case 2:
			type =  CAT_2;
		break;
		case 3:
			type =  DOG_ROBOT_1;
		break;
		case 4:
			type = DOG_ROBOT_2;
		break;

		default:
		break;
	}
	return type;
}

/* CREATE A NEW LIST */
listMonster* createList() {
	listMonster* list = (listMonster*)malloc(sizeof(listMonster));
	
	if(list == NULL) {
		fprintf(stderr, "MEMORY ERROR \n");
		exit(1);
	}
	list->monsterr = NULL;
	list->nbMonster = 0;
	return list;
}




