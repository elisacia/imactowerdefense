#include "struct.h"

Color ColorRGB(float r, float g, float b){
	Color color;

	color.r = r;
	color.g = g;
	color.b = b;

	return color;
}

Node* createNode(int x, int y, int type, int id) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
	{
		fprintf(stderr, "Pas d'espace alloué au noeud\n");
		exit(1);
	}
	(*node).x = x;
	(*node).y = y;
	(*node).type = type;
	(*node).id = id;
	(*node).next = NULL;

	return node;
}