#ifndef ITD_MAP__
#define ITD_MAP__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>

#include "struct.h"

/* ------- STRUCTURES ------- */

typedef struct map
{
	char* map;				// Nom du fichier image.ppm représentant la carte
	Node* listNode;			// Liste de noeuds
	unsigned int nbNodes;		// Nombre noeuds
	Color colorPath;			// Couleur chemin
	Color colorNode;			// Couleur noeuds
	Color colorConstruct;		// Couleur zones constructibles
	Color colorIn;				// Couleur zone entrée
	Color colorOut;				// Couleur zone de sortie
}Map;

/* ------- FONCTIONS ------- */

Map loadMap(char* fileNameMapITD);
int createMap(FILE* fichierITD, Map* map);
void drawPath(Node* n);

#endif