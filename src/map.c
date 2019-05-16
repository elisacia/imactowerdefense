#include "map.h"
#include "image.h"

/* ------- LIRE IMAGE ------- */ 

int newImage(Image *image, unsigned int width, unsigned int height)
{
  // memory allocation
  image->data = (unsigned char*) malloc(sizeof(unsigned char) * 3 * width * height);
  if(image->data == NULL){
    printf("newImage : error bad memory allocation.\n");
    return EXIT_FAILURE;
  }

  // update width and height
  image->width  = width;
  image->height = height;

  return EXIT_SUCCESS;
}

void freeImage(Image *image)
{
  if(image != NULL) {
    if(image->data != NULL)	{
	    free(image->data);
      image->data= NULL;
    }

    image->width  = 0;
    image->height = 0;
	}
}

int loadImagePPM(Image *image, char *filename)
{
  FILE *myFile = NULL;
  char chaine[255];
  unsigned int width,height;

  // open the file
  if (!(myFile = fopen(filename, "rt")))
    {
      printf("loadImagePPM : error opening file %s.\n",filename);
      return EXIT_FAILURE;
    }

  // read header
  fscanf(myFile,"%s\n",chaine);

  // read comments ...
  do{ 
    fgets(chaine,255,myFile);
  } while (chaine[0]=='#');
  
  // read width and height
  sscanf(chaine,"%d %d",&width,&height);
  printf("width:  %d\nheight: %d\n",width,height);

  // read the "255"
  fscanf(myFile,"%s\n",chaine);

  // memory allocation
  if(newImage(image,width,height) == EXIT_FAILURE){
    printf("loadImagePPM : memory allocation error\n");
    return EXIT_FAILURE;
  }

  // read the data
  fread(image->data, sizeof (unsigned char), width*height * 3, myFile);

  // close the file
  fclose(myFile);

  return EXIT_SUCCESS;
}



/* ------- CRÉATION CARTE + VERIFICATION ------- */

int createMap(FILE* fichierITD, Map* map){

	int x,y,next;
	//vérification du code ITD
	char codeITD[5];
	fgets(codeITD,5,fichierITD);

	if (strcmp(codeITD,"@ITD")!= 0)
	{
		fprintf(stderr, "Erreur ITD: Code du fichier ITD invalide\n" );
		return 0;
	}

		//vérification version
	int version;

	fscanf(fichierITD,"%d\n",&version);

	if (version !=1)
	{
		fprintf(stderr,  "Erreur ITD : version\n");
		return 0;
	}

		//vérification commentaire

	char diese[0];
	fscanf(fichierITD,"%c",&diese);
	if (strcmp(diese,"#") !=0)
	{
		fprintf(stderr,  "Erreur ITD : Ligne de commentaire\n");
		return 0;
	}

		char commentaire[100];
		fgets(commentaire,100,fichierITD);

	//vérification de mots clés: initialisation
	char keyword[4];
	int R = 0;
	int G = 0;
	int B = 0;

	//vérification mot clé : "carte"
	fgets(keyword,7, fichierITD);

	if (strcmp(keyword,"carte ") !=0)
	{
		fprintf(stderr, "Erreur ITD: Mot-clé différent de \"carte\" \n" );
		return 0;
	}

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

fprintf(stderr, "%s\n",filename );
	//vérification mot clé : "chemin"
	fgets(keyword, 7, fichierITD);
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
	fgets(keyword, 6, fichierITD);
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
	fgets(keyword, 10, fichierITD);
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
	fgets(keyword, 3, fichierITD);
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
	fgets(keyword, 4, fichierITD);
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

	if(nbNoeud < 2) 
	{
		printf("Erreur ITD: Trouvé %d noeuds : au moins %d noeuds nécessaires.\n", nbNoeud, 2);
		return 0;
	}

	//récupération du nombre de coordonnées de noeuds (on compte le nombre de ligne qu'il reste)
	unsigned int nbLines = 1;
	int c;
	while((c = fgetc(fichierITD)) != EOF) {
		if (c == '\n') 
		{
			nbLines++;
		}
	}

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
	char file[30] = "img/";
	strcat(file,filename);
	SDL_Surface* carte = IMG_Load(file);
	if (carte == NULL)
	{
		fprintf(stderr, "Erreur ITD: impossible de charger la carte %s\n",file );
		return 0;
	}

	//vérification si les coordonnés sont bien dans la carte
	int i=0;


	while(i<nbLines) {
		fscanf(fichierITD, "%*d %*d %d %d %d\n", &x, &y,&next);
		// fprintf(stderr, "%d %d\n",x,y );
		// fprintf(stderr, "%d\n",next );
		if (x > carte->w || y > carte->h || x<0 || y<0)
		{
			fprintf(stderr, "Erreur ITD: erreur de coordonnées sur le carte %s\n, des coordonnées sont hors de la taille de la carte",file );
			return 0;
		}
		i++;
	}

	x=0;
	y=0;
	
	int j=0;
	//liste des noeuds 
	fseek(fichierITD, position, SEEK_SET);
	fscanf(fichierITD,  "%*d %*d %d %d %d\n", &x, &y,&next);
	Node* current = createNode(x, y, next);
	Node* tmp = current;
	

	while(j<nbLines) {
		fscanf(fichierITD,  "%*d %*d %d %d %d\n", &x, &y,&next);
		Node* node = createNode(x,y, next);
	 	(*current).next = node;
		current=(*current).next;
			 // fprintf(stderr, "bla" );
		j++;
	}


	 (*current).next = NULL;
	 (*map).listNode = tmp;

	// Image image;
	//  newImage(image,600,600);

	//  //get data de l'image
	//  loadImagePPM(image,filename);

	 



	//  freeImage(image);
	 SDL_FreeSurface(carte);

	 return 1;
}







//verifier si coordonés noeuds itd = point noir sur image



//verifier si les points de la ligne entre deux noeud = blanc sur image


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




