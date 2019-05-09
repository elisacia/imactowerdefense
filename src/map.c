#include "map.h"

/* ------- CRÉATION CARTE + VERIFICATION ------- */

int createMap(FILE* fichierITD, Map* map){

	int x,y;
	//vérification du code ITD
	char codeITD[5];
	fgets(codeITD,5,fichierITD);

	if (strcmp(codeITD,"@ITD")!= 0)
	{
		fprintf(stderr, "Erreur ITD: Code du fichier ITD invalide\n" );
		return 0;
	}

		//vérification commentaire

	//vérification format ppm
	char filename[20];
	fgets(filename,20, fichierITD);
	char* extension = strchr(filename,'.');
	if (strcmp(extension,".ppm\n") !=0)
	{
		fprintf(stderr, "Erreur ITD: Le fichier n'est pas au format .ppm \n" );
		return 0;
	}
	else {
		(*map).map = filename;
	}

	//vérification version
	int version;
	fscanf(fichierITD,"%d\n",version);
	if (version !=1)
	{
		fprintf(stderr,  "Erreur ITD : version\n");
		return 0;
	}

	//vérification de mots clés: initialisation
	char keyword[10];
	int R = 0;
	int G = 0;
	int B = 0;

	//vérification mot clé : "carte"
	fgets(keyword,7, fichierITD);
	if (strcmp(keyword,"carte") !=0)
	{
		fprintf(stderr, "Erreur ITD: Mot-clé différent de \"carte\" \n" );
		return 0;
	}

	//vérification mot clé : "chemin"
	fgets(keyword, 8, fichierITD);
	if (strcmp(keyword,"chemin")== 0)
	{
		fscanf(fichierITD, "%d %d %d\n", &R, &G, &B);
		if (R < 0 || R > 255 || G < 0 || G > 255 || B < 0 || B > 255)
		{
			fprintf(stderr, "Erreur ITD: Couleur clé du chemin \n" );
			return 0;
		}
		else {
			(*map).colorPath = ColorRGB(R, G, B);
		}
	}
	else {
		fprintf(stderr, "Erreur ITD: Mot-clé différent de \"chemin\" \n" );
		return 0;
	}


	//vérification mot clé : "noeud"
	fgets(keyword, 7, fichierITD);
	if (strcmp(keyword,"noeud")==0) 
	{
		fscanf(fichierITD, "%d %d %d\n", &R, &G, &B);
		if (R < 0 || R > 255 || G < 0 || G > 255 || B < 0 || B > 255)
		{
			fprintf(stderr, "Erreur ITD: Couleur clé des noeuds \n" );
			return 0;
		}
		else {
			(*map).colorNode = ColorRGB(R, G, B);
		}
	}
	else {
		fprintf(stderr, "Erreur ITD: Mot-clé différent de \"noeud\" \n" );
		return 0;
	}


	//vérification mot clé : "construct"
	fgets(keyword, 11, fichierITD);
	if (strcmp(keyword,"construct")==0) 
	{
		fscanf(fichierITD, "%d %d %d\n", &R, &G, &B);
		if (R < 0 || R > 255 || G < 0 || G > 255 || B < 0 || B > 255)
		{
			fprintf(stderr, "Erreur ITD: Couleur clé des zones constructibles \n" );
			return 0;
		}
		else {
			(*map).colorConstruct = ColorRGB(R, G, B);
		}
	}
	else {
		fprintf(stderr, "Erreur ITD: Mot-clé différent de \"construct\" \n" );
		return 0;
	}


	//vérification mot clé : "in"
	fgets(keyword, 4, fichierITD);
	if (strcmp(keyword,"in")==0) 
	{
		fscanf(fichierITD, "%d %d %d\n", &R, &G, &B);
		if (R < 0 || R > 255 || G < 0 || G > 255 || B < 0 || B > 255)
		{
			fprintf(stderr, "Erreur ITD: Couleur clé de la zone d'entrée \n" );
			return 0;
		}
		else {
			(*map).colorIn = ColorRGB(R, G, B);
		}
	}
	else {
		fprintf(stderr, "Erreur ITD: Mot-clé différent de \"in\" \n" );
		return 0;
	}


	//vérification mot clé : "out"
	fgets(keyword, 5, fichierITD);
	if (strcmp(keyword,"out")==0) 
	{
		fscanf(fichierITD, "%d %d %d\n", &R, &G, &B);
		if (R < 0 || R > 255 || G < 0 || G > 255 || B < 0 || B > 255)
		{
			fprintf(stderr, "Erreur ITD: Couleur clé de la zone de sortie \n" );
			return 0;
		}
		else {
			(*map).colorOut = ColorRGB(R, G, B);
		}
	}
	else {
		fprintf(stderr, "Erreur ITD: Mot-clé différent de \"out\" \n" );
		return 0;
	}


	//récupération nombres de noeuds
	int nbNoeud;
	fscanf(fichierITD, "%d\n", &nbNoeud);


	//récupération position du curseur
	long position;
	position = ftell(fichierITD);


	//récupération du nombre de coordonnées de noeuds (on compte le nombre de ligne qu'il reste)
	int nbLines = 0;
	while((fgetc(fichierITD)) != EOF) {
		if (fgetc(fichierITD) == '\n') 
		{
			nbLines++;
		}
	}
	nbLines++;
	if (nbNoeud != nbLines)
	{
		fprintf(stderr, "Erreur ITD : Nombre de noeud\n");
		return 0;
	}
	else {
		(*map).nbNodes = nbNoeud;
	}

	fseek(fichierITD, position, SEEK_SET); //place le cuseur au premier noeud

	//suppression du '\n' dans le nom de l'image
	int length = strlen(filename);
	filename[length-1] = '\0';

	//chargement carte 
	char file[30] = "images/";
	strcat(file,filename);
	SDL_Surface* carte = IMG_Load(file);
	if (carte == NULL)
	{
		fprintf(stderr, "Erreur ITD: impossible de charger la carte %s\n",file );
		return 0;
	}

	//vérification
	int i=0;
	while(i<nbLines) {
		fscanf(fichierITD, "%d %d\n", &x, &y);
		if (x > carte->w || y > carte->h || x<0 || y<0)
		{
			fprintf(stderr, "Erreur ITD: erreur de coordonnées %s\n",file );
			return 0;
		}
		i++;
	}
	x=0;
	y=0;


	//liste des noeuds 
	fseek(fichierITD, position, SEEK_SET);
	fscanf(fichierITD, "%d %d\n", &x, &y);
	Node* current = createNode(x, y);
	Node* tmp = current;
	for (int i = 0; i < nbLines; ++i)
	 {
	 	fscanf(fichierITD, "%d %d\n", &x, &y);
	 	Node* node = createNode(x,y);
	 	(*current).next = node;
		current=(*current).next;
	 } 
	 (*current).next = NULL;
	 (*map).listNode = tmp;

	 SDL_FreeSurface(carte);

	 return 1;
}

/* ------- CHARGEMENT CARTE ------- */

Map loadMap(char* nameITD) {
	FILE* fichierITD = fopen(nameITD,"r");
	if (fichierITD == NULL)
	{
		fprintf(stderr, "Erreur dans l'ouverture du fichier ITD %s\n",nameITD );
		exit(1);
	}

	Map map;

	if (createMap(fichierITD, &map))
	{
		return map;
	}
	else {
		fprintf(stderr, "Erreur le fichier ITD %s n'est pas valide\n",nameITD );
		exit(1);
	}
}


/* ------- DESSIN DU CHEMIN ------- */

void drawPath(Node* n) {
	glBegin(GL_LINES);
	while(n->next != NULL) {
		glVertex2d(n->x, 600-n->y);
		glVertex2d(n->next->x, 600-n->next->y);

		n = n-> next;
	}
	glEnd();
}




