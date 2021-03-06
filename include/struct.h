#ifndef ITD_STRUCT__
#define ITD_STRUCT__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <stdio.h>

/* ------- STRUCTURES ------- */

typedef struct str_color3ub
{
	unsigned char r;				
	unsigned char g;				
	unsigned char b;				
}Color;


typedef struct str_position
{
	float x;
	float y;				
}Position;


typedef struct str_node
{
	Color color;
	float x;
	float y;
	int id;
	int id_successeur;
	int type;
	struct str_node* next;				
}Node;


typedef struct str_list
{
	unsigned int size;
	int value;
	Node* prev;
	Node* next;			
}List;

typedef struct jeu {
	int start;
	int win;
	int lose;
	int pause;
	int help;
	int red;
	int green;
	int blue;
	int yellow;
}Jeu;

/* ------- FONCTIONS ------- */

Color ColorRGB(float r, float g, float b);
Node* createNode(int x, int y, int next);

#endif