#ifndef ITD_MONSTER_H__
#define ITD_MONSTER_H__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include "struct.h"
#include "tower.h"
#include "graphic.h"

/* STRUCTURE OF MONSTERS */
typedef enum{
	CAT_1, CAT_2, CAT_3, CAT_4
}MonsterType;


typedef struct monster {

	//type of the monster 
	MonsterType type;
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
	char* imageMonster;

}Monster;



/* STRUCTURE OF THE LIST OF MONSTERS */


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
Monster* createMonster(MonsterType type, Node* next, float x, float y);
/* CHOOSE THE TYPE OF MONSTER */
MonsterType chooseMonster(Wave wave);
/* CREATE A NEW LIST */
listMonster* createList();

#endif