#ifndef ITD_MONSTER_H__
#define ITD_MONSTER_H__

#include "image.h"

/* STRUCTURE OF MONSTERS */

typedef struct monster {

	//type of the monster 
	char* type;
	//position of the monster
	float x;
	float y;
	//previous node on the map
	Node* node_prev;
	//next node on the map 
	Node* node_next;
	//point de vie
	int lifePoint;
	//speed of movement 
	int speed;
	//resistance of the monster (it increases)
	int resistance;
	//points earned by the player when he kills a monster 
	int pointPlayer;
	//the profit done when the monster is killed (money)
	int profit;
	//image associated to the monster
	Image* imageMonster;

}Monster;



/* STRUCTURE OF THE LIST OF MONSTERS */

typedef enum{
	CAT_1, CAT_2, DOG_ROBOT_1, DOG_ROBOT_2
}MonsterType;

typedef struct listMonster {
	Monster* monsterr;
	int nbMonster;
}listMonster;

typedef struct wave {
	listMonster list;
	int nbLists;
}Wave;



/* FUNCTIONS */

/* CREATE A NEW MONSTER */
Monster* createMonster(MonsterType type, Node* next, float x, float y)
/* CHOOSE THE TYPE OF MONSTER */
MonsterType chooseMonster(Wave wave)
/* CREATE A NEW LIST */
listMonster* createList();

#endif