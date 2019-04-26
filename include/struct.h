#ifndef ITD_OUTILS__
#define ITD_OUTILS__

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
	struct str_node* next;				
}Node;


typedef struct str_list
{
	unsigned int size;
	int value;
	Node* prev;
	Node* next;			
}List;


/* ------- FONCTIONS ------- */

Color ColorRGB(float r, float g, float b);
Node* createNode(int x, int y);

#endif