/* \file LectureFichier.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date mond oct 11
 * 
 * \brief Fonction permettant de lire un fichier .pov
 *
 *
 */

//Inclusion des entetes de librairie
#include "LectureFichier.h"

//procédure qui permet d'enlever les espaces du tableau 
void enleveEspace(char* tab){
	int taille;//taille du tableau
	int i;//valeur a incrementer
	int j;//valeur a incrementer
	
	taille = strlen(tab);//taille du tableau
	i=0;
	
	//On va parcourir le tableau afin deliminer chaque espace
	//en decalant les valeurs du tableau de 1 vers la gauche des 
	//qu'on trouve un espace pour ainsi l'ecraser
	while(i != taille){
		if(tab[i]==' '){
			j = i;
			while(j != taille){
				tab[j] = tab[j+1];
				j++;
			}
		}
		i++;
	}
}

//procédure qui permet de lire le fichier et remplir les structures d'objets
void LectureFichier(objet* obj, char* fichier, int tailleFichier, objetCSG* objetcsg, listeIntersection* lIntersection){
	char* tabObj;//tableau qui stocke la valeur du caractère courant
	int i;//un compteur
	int j;//un compteur
	double** matriceTranslate;//matrice qui translate un objet
	double** matriceScale;//matrice qui permet de faire un scale sur un objet
	double** matriceRotate;//matrice qui rotate un objet
	listeMatrice* liste;//une liste des matrices translate, rotate, scale
	
	//initialisation
	i=0;
	
	//on va parcourir le fichier jusqu'a la fin
	while(tailleFichier>=i){
		//on initialise a chaque tour de boucle les variables
		tabObj = malloc(sizeof(char)*1000);
		//on initialise les matrices suivantes
		matriceTranslate = creerMatrice(4);
		matriceScale = creerMatrice(4);
		matriceRotate =creerMatrice(4);
		liste = NULL;
		j=0;
		//on va stocker tout ce qui se trouve avant une accolade afin de 
		// trouver le nom de la structure que l'on va parcourir et stocker
		while(fichier[i]!='{' && tailleFichier >= i){
			//si jamais en tombe sur un commentaire, on l'ignore
			if(fichier[i]=='/'&& fichier[i+1]=='/'){
				while(fichier[i]!='\n'){
					i++;
				}
			}
			tabObj[j]= fichier[i];
			j++;
			i++;
			
		}
		tabObj[j+1]='\0';
		
		//si on a une difference
		if(strstr(tabObj, "difference")!=NULL){
			(*objetcsg).ordreObjet=-1;
			(*objetcsg).booleenCSG=2;
		
		}
		
		//Si c'est une intersection
		if(strstr(tabObj,"intersection")!=NULL){
			(*objetcsg).booleenCSG=1;
			//lireIntersection(obj, tabObj, tailleFichier, &i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, lIntersection, objetcsg);
		}
		
		//Si c'est un union
		if(strstr(tabObj,"union")!=NULL){
			listeUnion* lUnion;//structure a initialiser
			lUnion = malloc(sizeof(listeUnion));//on alloue de la memoire
			//on lit toute l'intersection
			lireUnion(obj, tabObj, tailleFichier, &i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, lUnion, objetcsg);
		}
		//En commentaire car pas pris totalement en compte
		//Si c'est une difference
		/*if(strstr(tabObj,"difference")!=NULL){
			listeDifference* lDifference;//structure a initialiser
			lDifference = malloc(sizeof(listeDifference));//on alloue de la memoire
			//on lit toute l'intersection
			lireDifference(obj, tabObj, tailleFichier, &i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, lDifference, objetcsg);
			
		}*/
				
		//Si c'est une camera
		if(strstr(tabObj,"camera")!=NULL){
			//on lit la caméra
			lireCamera(obj, tabObj, tailleFichier, &i, fichier);

		}

		//Si c'est une lumiere
		if(strstr(tabObj,"light_source")!=NULL){
			//on lit la light source
			lireLightSource(obj, tabObj, tailleFichier, &i, fichier);

		}
		//si c'est un arriere plan
		if(strstr(tabObj,"background")!=NULL){
			//on lit le background
			lireBackground(obj, tabObj, tailleFichier, &i, fichier);

		}
		
		//si c'est un plan 
		if(strstr(tabObj,"plane")!=NULL){
			listePlane* nvPlan;//on creer un nouveau maillon
			//on lit un plan
			nvPlan = malloc(sizeof(listePlane));
			lirePlan(nvPlan, tabObj, tailleFichier, &i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvPlan).suivant = (*obj).lplan;
			//on reactualise l'ancienne liste
			(*obj).lplan = nvPlan;
		}

		//si c'est une sphere 
		if(strstr(tabObj,"sphere")!=NULL){
			listeSphere* nvSphere;//on creer un nouveau maillon
			nvSphere = malloc(sizeof(listeSphere));//on alloue de la memoire a ce nouveau maillon
			//on lit une sphere
			lireSphere(nvSphere, tabObj, tailleFichier, &i, fichier,liste, matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvSphere).suivant = (*obj).lsphere;
			//on reactualise l'ancienne liste
			(*obj).lsphere = nvSphere;
		}
		
		//si c'est un triangle
		if(strstr(tabObj,"triangle")!=NULL){
			listeTriangle* nvTriangle;//on creer un nouveau maillon
			nvTriangle = malloc(sizeof(listeTriangle));//on alloue de la memoire a ce nouveau maillon
			//on lit un triangle
			lireTriangle(nvTriangle, tabObj, tailleFichier, &i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvTriangle).suivant = (*obj).ltriangle;
			//on reactualise l'ancienne liste
			(*obj).ltriangle = nvTriangle;
		}
		// si c'est une boite 
		if(strstr(tabObj,"box")!=NULL){
			listeBox* nvBoite;//on creer un nouveau maillon
			nvBoite = malloc(sizeof(listeBox));//on alloue de la memoire a ce nouveau maillon
			//on lit un cube
			lireCube(nvBoite, tabObj, tailleFichier, &i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvBoite).suivant = (*obj).lbox;
			//on reactualise l'ancienne liste
			(*obj).lbox = nvBoite;	
		}

		// le cylindre 
		if(strstr(tabObj,"cylinder")!=NULL){
			listeCylinder* nvCylindre;//on creer un nouveau maillon
			nvCylindre = malloc(sizeof(listeCylinder));//on alloue de la memoire a ce nouveau maillon
			//on lit un cylindre
			lireCylindre(nvCylindre, tabObj, tailleFichier, &i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvCylindre).suivant = (*obj).lcylindre;
			//on reactualise l'ancienne liste
			(*obj).lcylindre = nvCylindre;
		}

		//le cone 
		if(strstr(tabObj,"cone")!=NULL){
			listeCone* nvCone;//on creer un nouveau maillon
			nvCone = malloc(sizeof(listeCone));//on alloue de la memoire a ce nouveau maillon
			//on lit un cylindre
			lireCone(nvCone, tabObj, tailleFichier, &i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvCone).suivant = (*obj).lcone;
			//on reactualise l'ancienne liste
			(*obj).lcone = nvCone;
		}

		//torus
		if(strstr(tabObj,"torus")!=NULL){
			listeTorus* nvTore;//on creer un nouveau maillon
			nvTore = malloc(sizeof(listeTorus));//on alloue de la memoire a ce nouveau maillon
			//on lit un tore
			lireTore(nvTore, tabObj, tailleFichier, &i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvTore).suivant = (*obj).ltore;
			//on reactualise l'ancienne liste
			(*obj).ltore = nvTore;
		} 
		//on incrémente le compteur
		i++;
		//on libère les allocations suivantes
		free(tabObj);
		libereMatrice(matriceRotate,4);
		libereMatrice(matriceScale,4);
		libereMatrice(matriceTranslate,4);
	}
}

//fonction qui lit une intersection
void lireIntersection(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, listeIntersection* lIntersection,  objetCSG* objetcsg){
	int j;
	j=0;
	//faire tant quon est pas a la fin de lintersection
	do{
		if(strstr(tabObj,"plane")!=NULL){
			//on lit un plan
			listePlane* nvPlan;//on creer un nouveau maillon
			//nvPlan = NULL;
			nvPlan=malloc(sizeof(listePlane));
			lirePlan(nvPlan, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvPlan).suivant = (*lIntersection).obj.lplan;
			(*lIntersection).obj.lplan = nvPlan;
			
		}
		
		if(strstr(tabObj,"sphere")!=NULL){
			listeSphere* nvSphere;//on creer un nouveau maillon
			nvSphere = malloc(sizeof(listeSphere));//on alloue de la memoire a ce nouveau maillon
			//on lit une sphere
			lireSphere(nvSphere, tabObj, tailleFichier, i, fichier,liste, matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvSphere).suivant = (*lIntersection).obj.lsphere;
			(*lIntersection).obj.lsphere = nvSphere;
			(*nvSphere).suivant = (*obj).lsphere;
			//on reactualise l'ancienne liste
			(*obj).lsphere = nvSphere;
		}
		
		if(strstr(tabObj,"triangle")!=NULL){
			listeTriangle* nvTriangle;//on creer un nouveau maillon
			nvTriangle=NULL;
			//on lit un triangle
                	lireTriangle(nvTriangle, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
                	(*nvTriangle).suivant = (*lIntersection).obj.ltriangle;
			(*lIntersection).obj.ltriangle = nvTriangle;
		}
		if(strstr(tabObj,"box")!=NULL){
			listeBox* nvBoite;
			nvBoite=NULL;
			//on lit un cube
			lireCube(nvBoite, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvBoite).suivant = (*lIntersection).obj.lbox;
			(*lIntersection).obj.lbox = nvBoite;
		}
		if(strstr(tabObj,"cylinder")!=NULL){
			listeCylinder* nvCylindre;
			nvCylindre=NULL;
			//on lit un cylindre
			lireCylindre(nvCylindre, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvCylindre).suivant = (*lIntersection).obj.lcylindre;
			(*lIntersection).obj.lcylindre = nvCylindre;
		}
		if(strstr(tabObj,"cone")!=NULL){
			listeCone* nvCone;
			nvCone=NULL;
			//on lit un cylindre
			lireCone(nvCone, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvCone).suivant = (*lIntersection).obj.lcone;
			(*lIntersection).obj.lcone = nvCone;
		}
		if(strstr(tabObj,"tore")!=NULL){
			listeTorus* nvTore;
			nvTore=NULL;
			//on lit un tore
			lireTore(nvTore, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvTore).suivant = (*lIntersection).obj.ltore;
			(*lIntersection).obj.ltore = nvTore;
		}
		//En commentaire car pas pris totalement en compte
		//Si c'est une intersection on a mis en commentaire le faite de traiter une intersection dans une intersection car elle est a finir
		/*if(strstr(tabObj,"intersection")!=NULL){
			listeIntersection* nvIntersection;//nouveau maillon
			nvIntersection=malloc(sizeof(listeIntersection));//on alloue de la memoire;
			//on lit toute l'intersection
			lireIntersection(obj, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, nvIntersection, objetcsg);printf("oui");
			//(*nvIntersection).suivant=lIntersection;
			//lIntersection=nvIntersection;
			
		}*/
		/*if(strstr(tabObj,"union")!=NULL){
			//on lit toute lunion
			lireUnion(obj, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, lUnion);
		}
		if(strstr(tabObj,"difference")!=NULL){
			//on lit toute la difference
			lireDifference(obj, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, lDifference);*/
		(*i)++;
		tabObj[j]= fichier[*i];
                j++;
	}
	while(fichier[*i]!='}');
}

//fonction qui lit une union
void lireUnion(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, listeUnion* lUnion, objetCSG* objetcsg){
	//faire tant quon est pas a la fin de lunion
	do{
		if(strstr(tabObj,"plane")!=NULL){
			//on lit un plan
			listePlane* nvPlan;//on creer un nouveau maillon
			nvPlan = NULL;
			lirePlan(nvPlan, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvPlan).suivant = (*lUnion).obj.lplan;
			(*lUnion).obj.lplan = nvPlan;
			
		}
		
		if(strstr(tabObj,"sphere")!=NULL){
			listeSphere* nvSphere;//on creer un nouveau maillon
			nvSphere=NULL;
			//on lit une sphere
			lireSphere(nvSphere, tabObj, tailleFichier, i, fichier,liste, matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvSphere).suivant = (*lUnion).obj.lsphere;
			(*lUnion).obj.lsphere = nvSphere;
		}
		
		if(strstr(tabObj,"triangle")!=NULL){
			listeTriangle* nvTriangle;//on creer un nouveau maillon
			nvTriangle=NULL;
			//on lit un triangle
                	lireTriangle(nvTriangle, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
                	(*nvTriangle).suivant = (*lUnion).obj.ltriangle;
			(*lUnion).obj.ltriangle = nvTriangle;
		}
		if(strstr(tabObj,"box")!=NULL){
			listeBox* nvBoite;
			nvBoite=NULL;
			//on lit un cube
			lireCube(nvBoite, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvBoite).suivant = (*lUnion).obj.lbox;
			(*lUnion).obj.lbox = nvBoite;
		}
		if(strstr(tabObj,"cylinder")!=NULL){
			listeCylinder* nvCylindre;
			nvCylindre=NULL;
			//on lit un cylindre
			lireCylindre(nvCylindre, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvCylindre).suivant = (*lUnion).obj.lcylindre;
			(*lUnion).obj.lcylindre = nvCylindre;
		}
		if(strstr(tabObj,"cone")!=NULL){
			listeCone* nvCone;
			nvCone=NULL;
			//on lit un cylindre
			lireCone(nvCone, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvCone).suivant = (*lUnion).obj.lcone;
			(*lUnion).obj.lcone = nvCone;
		}
		if(strstr(tabObj,"tore")!=NULL){
			listeTorus* nvTore;
			nvTore=NULL;
			//on lit un tore
			lireTore(nvTore, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvTore).suivant = (*lUnion).obj.ltore;
			(*lUnion).obj.ltore = nvTore;
		}
		//En commentaire car pas pris totalement en compte
		/*if(strstr(tabObj,"intersection")!=NULL){
			//on lit toute l'intersection
			lireIntersection(obj, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, lUnion);
		}
		//Si c'est une union
		if(strstr(tabObj,"union")!=NULL){
			//on lit toute lunion
			lireUnion(obj, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, lUnion);
		}
		if(strstr(tabObj,"difference")!=NULL){
			//on lit toute la difference
			lireDifference(obj, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, lDifference);
		}*/	
		(*i)++;
	}
	while(fichier[*i]!='}');
}

//fonction qui lit une difference
void lireDifference(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, listeDifference* lDifference, objetCSG* objetcsg){
	//faire tant quon est pas a la fin de la difference
	do{
		if(strstr(tabObj,"plane")!=NULL){
			//on lit un plan
			listePlane* nvPlan;//on creer un nouveau maillon
			nvPlan = NULL;
			lirePlan(nvPlan, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvPlan).suivant = (*lDifference).obj.lplan;
			(*lDifference).obj.lplan = nvPlan;
			
		}
		
		if(strstr(tabObj,"sphere")!=NULL){
			listeSphere* nvSphere;//on creer un nouveau maillon
			nvSphere=NULL;
			//on lit une sphere
			lireSphere(nvSphere, tabObj, tailleFichier, i, fichier,liste, matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvSphere).suivant = (*lDifference).obj.lsphere;
			(*lDifference).obj.lsphere = nvSphere;
		}
		
		if(strstr(tabObj,"triangle")!=NULL){
			listeTriangle* nvTriangle;//on creer un nouveau maillon
			nvTriangle=NULL;
			//on lit un triangle
                	lireTriangle(nvTriangle, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
                	(*nvTriangle).suivant = (*lDifference).obj.ltriangle;
			(*lDifference).obj.ltriangle = nvTriangle;
		}
		if(strstr(tabObj,"box")!=NULL){
			listeBox* nvBoite;
			nvBoite=NULL;
			//on lit un cube
			lireCube(nvBoite, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvBoite).suivant = (*lDifference).obj.lbox;
			(*lDifference).obj.lbox = nvBoite;
		}
		if(strstr(tabObj,"cylinder")!=NULL){
			listeCylinder* nvCylindre;
			nvCylindre=NULL;
			//on lit un cylindre
			lireCylindre(nvCylindre, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvCylindre).suivant = (*lDifference).obj.lcylindre;
			(*lDifference).obj.lcylindre = nvCylindre;
		}
		if(strstr(tabObj,"cone")!=NULL){
			listeCone* nvCone;
			nvCone=NULL;
			//on lit un cylindre
			lireCone(nvCone, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvCone).suivant = (*lDifference).obj.lcone;
			(*lDifference).obj.lcone = nvCone;
		}
		if(strstr(tabObj,"tore")!=NULL){
			listeTorus* nvTore;
			nvTore=NULL;
			//on lit un tore
			lireTore(nvTore, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, objetcsg);
			(*nvTore).suivant = (*lDifference).obj.ltore;
			(*lDifference).obj.ltore = nvTore;
		}
		//En commentaire car pas pris totalement en compte
		//Si c'est une intersection
		/*if(strstr(tabObj,"intersection")!=NULL){
			//on lit toute l'intersection
			lireIntersection(obj, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, lIntersection);
		}
		if(strstr(tabObj,"union")!=NULL){
			//on lit toute lDifference
			lireUnion(obj, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, lDifference);
		}
		if(strstr(tabObj,"difference")!=NULL){
			//on lit toute la difference
			lireDifference(obj, tabObj, tailleFichier, i, fichier,liste,matriceTranslate, matriceScale, matriceRotate, lDifference);
		}*/
		(*i)++;
	}
	while(fichier[*i]!='}');
}

//fonction qui lit une caméra
void lireCamera(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier){
	int j;//valeur a incrementer
	int rentrerLocation;//permet de voir s'il a bien initialiser les deux variables
	int rentrerLookAt;
	//tant qu'on est pas a la fin de la structure
	while(fichier[*i]!='}' && tailleFichier >= *i){
		j=0;
		//on parcours le fichier tant qu'on trouve pas la location et le
		//look_at
		while((fichier[*i]!='<' && fichier[*i+1]!='}') && tailleFichier >= *i){
			tabObj[j] = fichier[*i];
			(*i)++;
			j++;
		}
		tabObj[j+1]='\0';
		if(strstr(tabObj, "location")!= NULL){
			rentrerLocation = 1;
			j=0;
			while(fichier[*i-1]!='>' && tailleFichier >= *i){
				tabObj[j]=fichier[*i];
				(*i)++;
				j++;
			}
                              
			enleveEspace(tabObj);
			//on stocke les valeurs du vecteur trouver dans la structure camera
			if(!(sscanf(tabObj,"<%f,%f,%f>",&(*obj).cam.location.x, &(*obj).cam.location.y, &(*obj).cam.location.z)==3)){
				printf("fichier eronne location camera\n");
				exit(EXIT_FAILURE);
			}
		} else {
				if(strstr(tabObj, "look_at")!= NULL){
				rentrerLookAt = 1;
				j=0;
				while(fichier[*i-1]!='>' && tailleFichier >= *i){
					tabObj[j]=fichier[*i];
					(*i)++;
					j++;
				}               
				enleveEspace(tabObj);
				if(!(sscanf(tabObj, "<%f,%f,%f>",&(*obj).cam.look_at.x, &(*obj).cam.look_at.y, &(*obj).cam.look_at.z)==3)){
					printf("fichier eronne look at camera\n");
					exit(EXIT_FAILURE);
				}
			}
		}
		(*i)++;
	}
			
	if(!rentrerLocation || !rentrerLookAt){
		printf("Le fichier est éronné au niveau de la caméra\n");
		exit(EXIT_FAILURE);
	} 
}

//fonction qui lit une light source
void lireLightSource(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier){
	int j;//valeur a incrementer
	light_source lumiere;//structure a initialiser
	listeLight* nvLumiere;//on creer un nouveau maillon
	nvLumiere = malloc(sizeof(listeLight));//on alloue de la memoire a ce nouveau maillon
                        
	j=0;
	while(fichier[*i]!='<' && tailleFichier != *i){//on parcours le fichier jusqu'a trouver un vecteur
		(*i)++;
	}
                        
	while(fichier[*i-1]!='>' && tailleFichier != *i){
		tabObj[j]=fichier[*i];
		(*i)++;
		j++;
	}       
	enleveEspace(tabObj);
	if(!(sscanf(tabObj,"<%f,%f,%f>",&lumiere.location.x,&lumiere.location.y, &lumiere.location.z)==3)){//si le vecteur position n'est pas correct on arrete le programme et on averti l'utilisateur
		printf("le fichier est eronne (location light_source)\n");
		exit(EXIT_FAILURE);
	}

	j=0;
	while(fichier[*i]!='<' && tailleFichier != *i){//on boucle ensuite jusqu'a trouver la couleur, on réalise ensuite la même chose que pour la location
		tabObj[j] = fichier[*i];
		(*i)++;
		j++;
	}
	if(strstr(tabObj, "rgb")!= NULL){
		j=0;
		while(fichier[*i-1]!='>' && tailleFichier != *i){
			tabObj[j]=fichier[*i];
			(*i)++;
			j++;
		}               
		enleveEspace(tabObj);
		if(!(sscanf(tabObj, "<%f,%f,%f>",&lumiere.color_rgb.x, &lumiere.color_rgb.y, &lumiere.color_rgb.z)==3)){
			printf("Le fichier est érroné color rgb light source\n");
			exit(EXIT_FAILURE);
		}

		}else{
			printf("le fichier est eronne color rgb light_source\n");
			exit(EXIT_FAILURE);
		}
		
		//on traite le fait qu'il y est plusieurs lampes
		//on defini le nouveau maillon et on l'ajoute a la tete de la liste
		(*nvLumiere).lumiere = lumiere;
		(*nvLumiere).suivant = (*obj).llumiere;
		//on reactualise l'ancienne liste
		(*obj).llumiere = nvLumiere;	
}

//fonction qui lit le background
void lireBackground(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier){
	int j;//valeur a incrementer
	j=0;
	while(fichier[*i]!='<' && tailleFichier != *i){//on boucle jusqu'a qu'on trouve la couleur du background
		tabObj[j] = fichier[*i];
		(*i)++;
		j++;
	}
	if(strstr(tabObj, "rgb")!= NULL){
		j=0;
		while(fichier[*i-1]!='>' && tailleFichier != *i){//on boucle jusqu'a la fin du vecteur couleur
			tabObj[j]=fichier[*i];
			(*i)++;
			j++;
		}               
		enleveEspace(tabObj);
		if((!sscanf(tabObj, "<%f,%f,%f>",&(*obj).arrierePlan.color_rgb.x, &(*obj).arrierePlan.color_rgb.y, &(*obj).arrierePlan.color_rgb.z)==3)){//si le vecteur est mal ecris on arrete le programme est on indique qu'il y a un problème à l'utilisateur
			printf("pb color rgb background\n");
			exit(EXIT_FAILURE);
		}
	}
}

//fonction qui lit un plan
void lirePlan(listePlane* nvPlan, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg){
	
	char* tabPigment;//tableau de caractere qui va stocker le pigment du plan
	int j;//valeur a incrementer
	plane plan;//structure a initialiser

	j=0;
	(*i)++;//on parcourt la structure du plan tant qu'on ne rencontre rien
	while(((fichier[*i]=='\n' || fichier[*i]==' ')&&(fichier[*i]!=',')) && tailleFichier != *i){
		(*i)++;
		tabObj[j] = fichier[*i];
	}
	
	//on creer les matrices nécessaires aux transformations	                   
	plan.matriceTransfo = creerMatrice(4);//matrice transformation
	plan.matriceTransfoInverse = creerMatrice(4);//matrice inverse de la transformation
	/*on les initialises a la matrice identité pour que quand il n'y a aucune transformation, le produit de la matrice et du
	rayon reste inchanger*/
	plan.matriceTransfo = matriceIdentite(plan.matriceTransfo,4);
	plan.matriceTransfoInverse = matriceIdentite(plan.matriceTransfo,4);
        
        //si la matrice est selon y
	if(strstr(tabObj, "y")!=NULL || strstr(tabObj, "<0,1,0>")!= NULL){
		//on boucle jusqu'a trouver la distance au sol
		(*i)++;
		while(((fichier[*i]=='\n' || fichier[*i]==' ')&&(fichier[*i]!=',')) && tailleFichier != *i){
			(*i)++;
		}
		if(fichier[*i]==','){
			(*i)++;
		}	
		plan.distance = strtof(&fichier[*i],NULL);
				
		//si la distance au sol n'est pas egale a 0, le plan a subit une translation en plus de la rotation
		if(plan.distance != 0){
			double** matriceTmp;
			matriceTmp = transformation(1,vector(0,plan.distance,0));//on translate le plan de la distance indiquer
			plan.matriceTransfo=transformation(3,vector(0,0,90));//on le tourne selon les z (notre plan unitaire etant en x)
			plan.matriceTransfo=produitMatricielle(matriceTmp,plan.matriceTransfo,4);//on fait le produit des deux matrices afin de creer notre matrice transformation finale
			libereMatrice(matriceTmp,4);//on libere la matrice dont on a plus besoin
		}else{//on fait une rotation selon l'axe des z pour pouvoir avoir un plan normal a y
			plan.matriceTransfo=transformation(3,vector(0,0,90));
		}
		//on transforme le plan en plan unitaire pour faciliter le calcul de l'intersection
		plan.location=vector(1,0,0);
		plan.distance = 0;
	}else if(strstr(tabObj, "x")!=NULL || strstr(tabObj, "<1,0,0>")!= NULL){//si le plan est selon les x 
		plan.location = vector(1,0,0);//on initialise sa location 
		(*i)++;
		while(((fichier[*i]=='\n' || fichier[*i]==' ')&&(fichier[*i]!=',')) && tailleFichier != *i){//on boucle jusqu'a trouver la distance au plan
			(*i)++;
		}
		if(fichier[*i]==','){
			(*i)++;
		}	
		plan.distance = strtof(&fichier[*i],NULL);//on initialise la distance au plan
		//si la distance au sol n'est pas egale a 0, le plan a subit une translation
		if(plan.distance != 0){
			plan.matriceTransfo = transformation(1,vector(plan.distance,0,0));//on initialise la matrice transformation d'un vecteur translation de la distance indiquer
		}
	}else if(strstr(tabObj, "z")!=NULL || strstr(tabObj, "<0,0,1>")!= NULL){//si le plan est selon les z
		(*i)++;
		while(((fichier[*i]=='\n' || fichier[*i]==' ')&&(fichier[*i]!=',')) && tailleFichier != *i){//on boucle jusqu'a trouver la distance au sol
			(*i)++;
		}
		if(fichier[*i]==','){
			(*i)++;
		}	
		plan.distance = strtof(&fichier[*i],NULL);//une fois trouver on l'initialise		
		//si la distance au sol n'est pas egale a 0, le plan a subit une translation en plus de la rotation
		if(plan.distance != 0){
			double** matriceTmp;
			matriceTmp = transformation(1,vector(0,0,plan.distance));//on translate le plan de la distance indiquer
			plan.matriceTransfo=transformation(3,vector(0,-90,0));//on le tourne selon les z (notre plan unitaire etant en x)
			plan.matriceTransfo=produitMatricielle(plan.matriceTransfo,matriceTmp,4);//on fait le produit des deux matrices afin de creer notre matrice transformation finale
			libereMatrice(matriceTmp,4);//on libere la matrice dont on a plus besoin
		}else{//on fait une rotation selon l'axe des y pour pouvoir avoir un plan normal a z
			plan.matriceTransfo=transformation(3,vector(0,-90,0));
		}
		//on initialise notre plan avec les coordonnees unitaires
		plan.distance = 0;
		plan.location=vector(1,0,0);
	}else{//si il ne lit aucun axe le plan est mal ecris, il arrete le programme et l'indique a l'utilisateur
		printf("fichier errone plan, axe ambigue\n");
		exit(EXIT_FAILURE);
	}
		          
	j=0;
	//on cherche ensuite la couleur du plan, on boucle jusqua la fin du fichier et si on trouve un pigment on initialise la couleur de l'objet avec le pigment
	while(fichier[*i]!='}' && tailleFichier != *i){
		tabObj[j]= fichier[*i];
		j++;
		(*i)++;
	}
	
	if(strstr(tabObj, "pigment")!=NULL){
		tabPigment = strstr(tabObj, "<");
		if(tabPigment !=NULL){
			enleveEspace(tabPigment);
			sscanf(tabPigment,"<%f,%f,%f>",&plan.pigment.x,&plan.pigment.y,&plan.pigment.z);
		}else{
			printf("problème pigment plan\n");
			exit(EXIT_FAILURE);
		}
	}
	//on creer une liste de transformation qui contient toutes les transformations ajouter par l'utilisateur
	liste = getTransformation(tabObj,tailleFichier, i,fichier,liste,matriceTranslate, matriceScale, matriceRotate);
        if(liste!=NULL){//si cette liste n'est pas nul on multiplie la matrice transformation du plan unitaire par la nouvelle
                   plan.matriceTransfo = produitMatricielle(initialiseMatrice(liste),plan.matriceTransfo, 4);
        }
	plan.matriceTransfoInverse = matriceInverse(plan.matriceTransfo,4);//on calcule l'inverse de la matrice de transformation
	
	//on defini le nouveau maillon et on l'ajoute a la tete de la liste
	(*nvPlan).plan = plan;
	
	//si il est dans une intersection
	if((*objetcsg).booleenCSG==1){
		plan.booleenCSG=1;
	}
	else if((*objetcsg).booleenCSG==2){
		plan.booleenCSG=2;
		(*objetcsg).ordreObjet=1;
		(*objetcsg).lplan=nvPlan;
	}
}

//fonction qui lit une sphere
void lireSphere(listeSphere* nvSphere, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste,double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg){
	int j;//valeur a incrementer
	char* tabPigment;//tableau de caractere qui va stocker le pigment de la sphere
	sphere boule;//structure a initialiser
	
	liste = NULL;//on initialise la liste d'intersection a NULL
	j=0;//on initialise la valeur de j           
	 
	while(fichier[*i]!='<' && tailleFichier != *i){//on boucle jusqu'a trouver la location de la sphere
		(*i)++;
	}
                      
	while(fichier[*i-1]!='>' && tailleFichier != *i){
		tabObj[j]=fichier[*i];
		(*i)++;
		j++;
	}       
	enleveEspace(tabObj);
                      
	if(!(sscanf(tabObj,"<%f,%f,%f>",&boule.location.x,&boule.location.y, &boule.location.z)==3)){
		printf("le fichier est eronne (sphere centre de la sphere)\n");
	}
 	
	j=0;//puis on boucle jusqu'a trouver le rayon de la sphere
	while(((fichier[*i]=='\n' || fichier[*i]==' ')&&(fichier[*i]!=',')) && tailleFichier != *i){
		(*i)++;
	}
	if(fichier[*i]==','){
		(*i)++;
	}
	boule.rayon = strtof(&fichier[*i], NULL);//on initalise le rayon
        
	j=0;
	while(fichier[*i]!='}' && tailleFichier != *i){
		tabObj[j]= fichier[*i];
		j++;
		(*i)++;
	}
	//on cherche ensuite la couleur du plan, on boucle jusqua la fin du fichier et si on trouve un pigment on initialise la couleur de l'objet avec le pigment
	if(strstr(tabObj, "pigment")!=NULL){
		tabPigment = strstr(tabObj, "<");
		if(tabPigment !=NULL){
			enleveEspace(tabPigment);
			sscanf(tabPigment,"<%f,%f,%f>",&boule.pigment.x,&boule.pigment.y,&boule.pigment.z);//on initialise la couleur de la sphere 
		}else{
			printf("pb pigment boule\n");
			exit(EXIT_FAILURE);
		}
	}
        
   	//on creer les matrices nécessaires aux transformations	
	boule.matriceTransfo = creerMatrice(4);//matrice transformation
	boule.matriceTransfoInverse = creerMatrice(4);//matrice inverse de la transformation
	/*on les initialises a la matrice identité pour que quand il n'y a aucune transformation, le produit de la matrice et du rayon reste inchanger*/
	boule.matriceTransfo = matriceIdentite(boule.matriceTransfo,4);
        boule.matriceTransfoInverse =  matriceIdentite(boule.matriceTransfo,4);
                        
	//Si la sphere n'est pas unitaire d'origine, on applique les transformations du vecteur position a sa matrice
	int boolTransformation;//on creer un booleen pour pourvoir indiquer si il y a plus d'une transformation
	boolTransformation = 0;//on l'initialise a faux
	//si la position n'est pas <0,0,0> la sphère subit donc une translation
	if(boule.location.x !=0 || boule.location.y !=0 || boule.location.z !=0 ){
		boule.matriceTransfo =  transformation(1,boule.location);//on initialise la matrice transformation avec la position de la sphere
		boule.location = vector(0,0,0);//puis on lui met les coordonnees unitaire
		boolTransformation = 1;//on indique qu'on a deja proceder a une transformation en metant le bouleen transformation a vrai
	}
                      
	//si le rayon n'est pas de 1 la sphere subit un scale
	if(boule.rayon!=1){
		if(boolTransformation){//si on a deja fait une transformation au préalable on va devoir multiplier les deux matrices transformations
			double** matriceTmp;
			matriceTmp = transformation(2,vector(boule.rayon,boule.rayon,boule.rayon));//on initialise la deuxieme transformation avec les coordonnees du scale qui est la taille du rayon
			boule.matriceTransfo = produitMatricielle(boule.matriceTransfo,matriceTmp,4);//on multiplie les deux matrices entre elles
			libereMatrice(matriceTmp,4);//puis on libere la matrice dont on n'a plus besoin
		}else{//sinon on initialise juste la deuxieme transformation avec les coordonnees du scale qui est la taille du rayon
			boule.matriceTransfo = transformation(2,vector(boule.rayon,boule.rayon,boule.rayon));
		}
		boule.rayon = 1;//on met le rayon a une taille unitaire 
	}
	//on creer une liste de transformation qui contient toutes les transformations ajouter par l'utilisateur             
	liste = getTransformation(tabObj,tailleFichier, i,fichier,liste,matriceTranslate, matriceScale, matriceRotate);
        if(liste!=NULL){//si cette liste n'est pas nul on multiplie la matrice transformation de la sphere unitaire par la nouvelle
              	boule.matriceTransfo = produitMatricielle(boule.matriceTransfo, initialiseMatrice(liste), 4);
        }
        
        //on calcule l'inverse de la matrice de transformation
        boule.matriceTransfoInverse = matriceInverse(boule.matriceTransfo,4);
	//on defini le nouveau maillon et on l'ajoute a la tete de la liste
	(*nvSphere).boule = boule;
	//si il est dans une intersection
	if((*objetcsg).booleenCSG==1){
		boule.booleenCSG=1;
	}
	else if((*objetcsg).booleenCSG==2){
		boule.booleenCSG=2;
		(*objetcsg).ordreObjet=0;
		(*objetcsg).lsphere=nvSphere;
	}
}

//fonction qui lit un triangle
void lireTriangle(listeTriangle* nvTriangle, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg){
	int j;//valeur a incrementer
	char* tabPigment;//tableau de caractere qui va stocker le pigment du triangle
	triangle tgle;//structure a initialiser
            
        //on va parcourir la structure du plan afin d'initialiser les trois coordonnees de ses 3coins     
        j=0;
        while(fichier[*i]!='<' && tailleFichier != *i){
 		(*i)++;
        }
                        
        while(fichier[*i-1]!='>' && tailleFichier != *i){
    	         tabObj[j]=fichier[*i];
                 (*i)++;
                 j++;
    	}       
        enleveEspace(tabObj);
        if(!(sscanf(tabObj,"<%f,%f,%f>",&tgle.coin1.x,&tgle.coin1.y, &tgle.coin1.z)==3)){
        	printf("le fichier est eronne (triangle coin 1)\n");
                exit(EXIT_FAILURE);
       	}

        j=0;
       	while(fichier[*i]!='<' && tailleFichier != *i){
                (*i)++;
       }
       while(fichier[*i-1]!='>' && tailleFichier != *i){
                tabObj[j]=fichier[*i];
                (*i)++;
      	        j++;
       }  
       if(!(sscanf(tabObj,"<%f,%f,%f>",&tgle.coin2.x,&tgle.coin2.y, &tgle.coin2.z)==3)){
      	        printf("le fichier est eronne (triangle coin 2)\n");
                exit(EXIT_FAILURE);
       }

       j=0;
       while(fichier[*i]!='<' && tailleFichier != *i){
                (*i)++;
       }
       while(fichier[*i-1]!='>' && tailleFichier != *i){
                tabObj[j]=fichier[*i];
                (*i)++;
                j++;
       }  
       if(!(sscanf(tabObj,"<%f,%f,%f>",&tgle.coin3.x,&tgle.coin3.y, &tgle.coin3.z)==3)){
                printf("le fichier est eronne (triangle coin 3)\n");
                exit(EXIT_FAILURE);
       }
                        
       j=0;
       while(fichier[*i]!='}' && tailleFichier != *i){//on boucle ensuite jusqu'a la fin du fichier et on regarde si l'utilisateur a indiquer une couleur si oui on initialise la couleur du triangle a avec le pigment indiquer
                tabObj[j]= fichier[*i];
                j++;
                (*i)++;
       }

       if(strstr(tabObj, "pigment")!=NULL){
                tabPigment = strstr(tabObj, "<");
                if(tabPigment !=NULL){
       		         enleveEspace(tabPigment);
                         sscanf(tabPigment,"<%f,%f,%f>",&tgle.pigment.x,&tgle.pigment.y,&tgle.pigment.z);
                         }else{
                               	printf("pb pigment triangle\n");
                               	 exit(EXIT_FAILURE);
                        }
                }
                //on creer les matrices nécessaires aux transformations	
		tgle.matriceTransfo = creerMatrice(4);//matrice transformation
		tgle.matriceTransfoInverse = creerMatrice(4);//matrice inverse de la transformation
		/*on les initialises a la matrice identité pour que quand il n'y a aucune transformation, le produit de la matrice et du
	rayon reste inchanger*/
		tgle.matriceTransfo = matriceIdentite(tgle.matriceTransfo,4);
                tgle.matriceTransfoInverse =  matriceIdentite(tgle.matriceTransfoInverse,4);
                
                //on creer une liste de transformation qui contient toutes les transformations ajouter par l'utilisateur 
		liste = getTransformation(tabObj,tailleFichier, i,fichier,liste,matriceTranslate, matriceScale, matriceRotate);
                if(liste!=NULL){//si cette liste n'est pas nul on multiplie la matrice transformation du triangle par la nouvelle
                      	tgle.matriceTransfo = produitMatricielle(initialiseMatrice(liste),tgle.matriceTransfo, 4);
                }
                //on calcule l'inverse de la matrice de transformation       
		tgle.matriceTransfoInverse = matriceInverse(tgle.matriceTransfo,4);
			
                //on defini le nouveau maillon et on l'ajoute a la tete de la liste
                (*nvTriangle).tgle = tgle;
              //si il est dans une intersection
	if((*objetcsg).booleenCSG==1){
		tgle.booleenCSG=1;
	}
	else if((*objetcsg).booleenCSG==2){
		tgle.booleenCSG=2;
		(*objetcsg).ordreObjet=5;
		(*objetcsg).ltriangle=nvTriangle;
	}
}

//fonction qui lit un cube
void lireCube(listeBox* nvBoite, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate,  objetCSG* objetcsg){
	box boite;//structure a initialiser
	int j;//valeur a incrementer
	char* tabPigment;//tableau de caractere qui va stocker le pigment du cube
               	
	j=0;
	while(fichier[*i]!='<' && tailleFichier != *i){//on parcourt le fichier afin de trouver les deux coordonnees des extremites opposé du cube
		(*i)++;
	}
                      
	while(fichier[*i-1]!='>' && tailleFichier != *i){
		tabObj[j]=fichier[*i];
		(*i)++;
		j++;
	}       
	if(!(sscanf(tabObj,"<%f,%f,%f>",&boite.coordonneePoint1.x,&boite.coordonneePoint1.y, &boite.coordonneePoint1.z)==3)){
		printf("le fichier est eronne (cube coordonnee point 1)\n");
		 exit(EXIT_FAILURE);
	}
	
                        
	j=0;
	while(fichier[*i]!='<' && tailleFichier != *i){
		(*i)++;
	}
        
	while(fichier[*i-1]!='>' && tailleFichier != *i){
		tabObj[j]=fichier[*i];
		(*i)++;
		j++;
	}       
	if(!(sscanf(tabObj,"<%f,%f,%f>",&boite.coordonneePoint2.x,&boite.coordonneePoint2.y, &boite.coordonneePoint2.z)==3)){
		printf("le fichier est eronne (cube coordonnee point 2 )\n");
		 exit(EXIT_FAILURE);
	}
                
	j=0;
	while(fichier[*i]!='}' && tailleFichier != *i){//on boucle jusqu'a la fin du fichier et on regarde si il y a un pigment si oui on initialise la couleur du cube avec le pigment trouver
		tabObj[j]= fichier[*i];
		j++;
		(*i)++;
	}

	if(strstr(tabObj, "pigment")!=NULL){
		tabPigment = strstr(tabObj, "<");
		if(tabPigment !=NULL){
			sscanf(tabPigment,"<%f,%f,%f>",&boite.pigment.x,&boite.pigment.y,&boite.pigment.z);
		}else{
			printf("pb pigment box\n");
			 exit(EXIT_FAILURE);
		}
	}
	
	//on creer les matrices nécessaires aux transformations	
	boite.matriceTransfo = creerMatrice(4);//matrice transformation
	boite.matriceTransfoInverse = creerMatrice(4);//matrice inverse de la transformation
	/*on les initialises a la matrice identité pour que quand il n'y a aucune transformation, le produit de la matrice et du
	rayon reste inchanger*/
	boite.matriceTransfo = matriceIdentite(boite.matriceTransfo,4);
        boite.matriceTransfoInverse =  matriceIdentite(boite.matriceTransfo,4);
        
        //on creer quatres test qui nous indiquera si notre cube est unitaire          
        int test1;
        int test2;
        int test3;
        int test4;
        
        //on compare chaque coordonnnee avec les coordoonnees unitaire et si elles sont egales alors le cube est unitaire, on le lui associe donc pas de transformation
        test1 = compareVecteur(boite.coordonneePoint1, vector(-0.5,-0.5,-0.5));
        test2 = compareVecteur(boite.coordonneePoint2, vector(0.5,0.5,0.5));
        test3 = compareVecteur(boite.coordonneePoint1, vector(0.5,0.5,0.5));
        test4 = compareVecteur(boite.coordonneePoint1, vector(-0.5,-0.5,-0.5));
                          
        //si ce n'est pas un cube unitaire
        if(!((test1&&test2) && (test2&&test3))){
        	double** matriceTmp;//matrice temporaire, permettant de faire des calcules temporaires sur les matrices
       		vecteur centre;//on creer un vecteur centre
       		matriceTmp = creerMatrice(4);
       		centre = opDivise(opPlus(boite.coordonneePoint1, boite.coordonneePoint2),2);//on calcul le centre du cube
                boite.matriceTransfo = transformation(1,centre);//on creer la matrice translation du cube grace au coordonnee du centre car le cube est unitialement a zero 
                //on scale ensuite le cube de la distance entre deux coté opposé, si elle est egale a 1 le cube a une taille unitaire
                matriceTmp = transformation(2,vector(fabs(boite.coordonneePoint1.x-boite.coordonneePoint2.x),fabs(boite.coordonneePoint1.y-boite.coordonneePoint2.y),fabs(boite.coordonneePoint1.z-boite.coordonneePoint2.z)));
                //on multiplie les deux matrice entre elles
                boite.matriceTransfo = produitMatricielle(boite.matriceTransfo,matriceTmp,4); 
                libereMatrice(matriceTmp, 4);//on libere la matrice qui ne nous sert plus
        }
        
        //on creer une liste de transformation qui contient toutes les transformations ajouter par l'utilisateur  
	liste = getTransformation(tabObj,tailleFichier, i,fichier,liste,matriceTranslate, matriceScale, matriceRotate);
        if(liste!=NULL){//si cette liste n'est pas nul on multiplie la matrice transformation du cube unitaire par la nouvelle
               	boite.matriceTransfo = produitMatricielle(initialiseMatrice(liste),boite.matriceTransfo, 4);
        }
	
	//on calcule l'inverse de la matrice de transformation		
	boite.matriceTransfoInverse = matriceInverse(boite.matriceTransfo,4);
	//on defini le nouveau maillon et on l'ajoute a la tete de la liste
	(*nvBoite).boite = boite;
	//si il est dans une intersection
	if((*objetcsg).booleenCSG==1){
		boite.booleenCSG=1;
	}
	else if((*objetcsg).booleenCSG==2){
		boite.booleenCSG=2;
		(*objetcsg).ordreObjet=4;
		(*objetcsg).lbox=nvBoite;
	}
}

//fonction qui lit un cylindre
void lireCylindre(listeCylinder* nvCylindre, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg){
	cylinder cylindre;//structure a initialiser
	int j;//valeur a incrementer
	char* tabPigment;//tableau de caractere qui va stocker le pigment du cylindre
                 
	j=0;
	while(fichier[*i]!='<' && tailleFichier != *i){//on parcourt la structure jusqu'a trouver les deux extremites du cylindre, et le rayon
		(*i)++;
	}
                       
	while(fichier[*i-1]!='>' && tailleFichier != *i){
		tabObj[j]=fichier[*i];
		(*i)++;
		j++;
	}       
	if(!(sscanf(tabObj,"<%f,%f,%f>",&cylindre.coordonneeExtremite1.x,&cylindre.coordonneeExtremite1.y, &cylindre.coordonneeExtremite1.z)==3)){
		printf("le fichier est eronne (coordonnee extrémité 1 cylindre)\n");
		exit(EXIT_FAILURE);
	}
    
	j=0;
	while(fichier[*i]!='<' && tailleFichier != *i){
		(*i)++;
	}
                        
	while(fichier[*i-1]!='>' && tailleFichier != *i){
		tabObj[j]=fichier[*i];
		(*i)++;
		j++;
	}       
	if(!(sscanf(tabObj,"<%f,%f,%f>",&cylindre.coordonneeExtremite2.x,&cylindre.coordonneeExtremite2.y, &cylindre.coordonneeExtremite2.z)==3)){
		printf("le fichier est eronne (coordonnee extrémité 2 cylindre)\n");
		exit(EXIT_FAILURE);
	}
        
	while(((fichier[*i]=='\n' || fichier[*i]==' ')&&(fichier[*i]!=',')) && tailleFichier != *i){
		(*i)++;
	}
	if(fichier[*i]==','){
		(*i)++;
	}	

	cylindre.rayon = strtof(&fichier[*i],NULL);
                       
	j=0;
	while(fichier[*i]!='}' && tailleFichier != *i){//on parcourt la structure jusqu'a la fin est on regarde si uen couleur est indiquer, si oui on initialise la couleur du cylindre avec
		tabObj[j]= fichier[*i];
		j++;
		(*i)++;
	}

	if(strstr(tabObj, "pigment")!=NULL){
		tabPigment = strstr(tabObj, "<");
		if(tabPigment !=NULL){
			sscanf(tabPigment,"<%f,%f,%f>",&cylindre.pigment.x,&cylindre.pigment.y,&cylindre.pigment.z);
		}else{
			printf("pb pigment cylindre\n");
			 exit(EXIT_FAILURE);
		}
	}
	
	//on creer les matrices nécessaires aux transformations	
	cylindre.matriceTransfo = creerMatrice(4);//matrice transformation
	cylindre.matriceTransfoInverse = creerMatrice(4);//matrice inverse de la transformation
	/*on les initialises a la matrice identité pour que quand il n'y a aucune transformation, le produit de la matrice et du
	rayon reste inchanger*/
	cylindre.matriceTransfo = matriceIdentite(cylindre.matriceTransfo,4);
	cylindre.matriceTransfoInverse = matriceIdentite(cylindre.matriceTransfo,4);
        
        //on creer les matrices necessaire au calcul de la rotation du cylindre
	double** matriceRotateY;//matrice temporaire
	double** matriceRotateZ;//matrice temporaire
	double** matriceRotation;//matrice finale
	//vecteurs permettant de faire les calculs de rotation
	vecteur tmp;//vecteur temporaire
	vecteur tmp2;//vecteur temporaire
	vecteur centre;//vecteur ayant les coordonnes du centre du cylindre
	double** matriceTmp;//matrice temporaire pour le scale du cylindre
	
	//on calcul la valeur du centre du cylidnre
	centre = opDivise(opPlus(cylindre.coordonneeExtremite2,cylindre.coordonneeExtremite1),2);
	tmp = opMoins(cylindre.coordonneeExtremite2, centre);//on calcul le vecteur allant du centre de la matrice jusuqu'au point d'intersection2
	tmp2 = vector(tmp.x, 0, tmp.z);//on initialise les deux vecteurs qui calcul l'angle au vecteur x
	tmp = vector(tmp.x,tmp.y, 0);
	//on normalise c'est deux vecteurs
	tmp = normaliser(tmp);
	tmp2 = normaliser(tmp2);
	
	//si un des vecteus est nulle cela signifie que le vecteur est selon les x
	if(compareVecteur(tmp, vector(0,0,0))){
		tmp = vector(1,0,0);
	}
	if(compareVecteur(tmp2, vector(0,0,0))){
		tmp2 = vector(1,0,0);
	}
	
	//on calcul la rotation selon les z et les y, on transforme l'angle trouvé en degré 
	matriceRotateZ = transformation(3, vector(0,0,180*acos(dot(vector(1,0,0),tmp))/M_PI));
	matriceRotateY = transformation(3, vector(0,180*acos(dot(vector(1,0,0),tmp2))/M_PI,0));
			
	//on fait le produit des deux afins d'obtenir la valeur de la rotation finale
	matriceRotation = produitMatricielle(matriceRotateY,matriceRotateZ, 4);
	//on libere les matrices inutilisé
	libereMatrice(matriceRotateZ,4);
	libereMatrice(matriceRotateY,4);
	
	//ensuite on s'occupe de la translation et du scale du cylindre
	cylindre.matriceTransfo=transformation(1, centre);//on le translate du centre car le cylindre unitaire est centré en (0,0,0)
	//on calcul le vecteur scale du cylindre en regarde la distance entre les deux extremites
	matriceTmp = transformation(2,vector(calculDistancePoint(cylindre.coordonneeExtremite1,cylindre.coordonneeExtremite2),1,1));
	//on multiplie toutes les matrices entres elles
	matriceTmp = produitMatricielle(matriceRotation,matriceTmp,4);
        cylindre.matriceTransfo = produitMatricielle(cylindre.matriceTransfo,matriceTmp,4); 
        //on libere les matrices qui ne nous servent plus
        libereMatrice(matriceTmp, 4);
	libereMatrice(matriceRotation,4);
	
	//on creer une liste de transformation qui contient toutes les transformations ajouter par l'utilisateur	
	liste = getTransformation(tabObj,tailleFichier, i,fichier,liste,matriceTranslate, matriceScale, matriceRotate);
        if(liste!=NULL){//si cette liste n'est pas nul on multiplie la matrice transformation du cylindre par la nouvelle
               	cylindre.matriceTransfo = produitMatricielle(initialiseMatrice(liste),cylindre.matriceTransfo, 4);
        }
        //on calcule l'inverse de la matrice de transformation
	cylindre.matriceTransfoInverse = matriceInverse(cylindre.matriceTransfo,4);
	//on defini le nouveau maillon et on l'ajoute a la tete de la liste
	(*nvCylindre).cylindre = cylindre;
	//si il est dans une intersection
	if((*objetcsg).booleenCSG==1){
		cylindre.booleenCSG=1;
	}	
	else if((*objetcsg).booleenCSG==2){
		cylindre.booleenCSG=2;
		(*objetcsg).ordreObjet=2;
		(*objetcsg).lcylindre=nvCylindre;
	}	
}

//fonction qui lit un cone
void lireCone(listeCone* nvCone, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg){
	int j;//valeur a incrementer
	char* tabPigment;//tableau de caractere qui va stocker le pigment du cone
	cone coneTmp;//structure a initialiser
	
        //on parcourt le fichier jusqu'a trouver les coordonnees des extremites et des rayons du cone
	j=0;
	while(fichier[*i]!='<' && tailleFichier != *i){
		(*i)++;
	}
                      
	while(fichier[*i-1]!='>' && tailleFichier != *i){
		tabObj[j]=fichier[*i];
		(*i)++;
		j++;
	}       
	if(!(sscanf(tabObj,"<%f,%f,%f>",&coneTmp.coordonneeExtremite1.x,&coneTmp.coordonneeExtremite1.y, &coneTmp.coordonneeExtremite1.z)==3)){
		printf("le fichier est eronne (cone extremite 1)\n");
		 exit(EXIT_FAILURE);
	}
                        
	while(((fichier[*i]=='\n' || fichier[*i]==' ')&&(fichier[*i]!=',')) && tailleFichier != *i){
		(*i)++;
	}
	if(fichier[*i]==','){
		(*i)++;
	}	
				
	coneTmp.rayon1 = strtof(&fichier[*i],NULL);

	j=0;
	while(fichier[*i]!='<' && tailleFichier != *i){
		(*i)++;
	}
                       
	while(fichier[*i-1]!='>' && tailleFichier != *i){
		tabObj[j]=fichier[*i];
		(*i)++;
		j++;
	}       
	if(!(sscanf(tabObj,"<%f,%f,%f>",&coneTmp.coordonneeExtremite2.x,&coneTmp.coordonneeExtremite2.y, &coneTmp.coordonneeExtremite2.z)==3)){
		printf("le fichier est eronne (cone extremite 2)\n");
		 exit(EXIT_FAILURE);
	}
                       
	while(((fichier[*i]=='\n' || fichier[*i]==' ')&&(fichier[*i]!=',')) && tailleFichier != *i){
		(*i)++;
	}
	if(fichier[*i]==','){
		(*i)++;
	}	
		
	coneTmp.rayon2 = strtof(&fichier[*i],NULL);

        j=0;
	while(fichier[*i]!='}' && tailleFichier != *i){//on boucle jusqu'a la fin du fichier et on regarde si l'utilisateur a rentrer une couleur si oui on initialise la couleur du cone avec celle ci
		tabObj[j]= fichier[*i];
		j++;
		(*i)++;
	}
	if(strstr(tabObj, "pigment")!=NULL){
		tabPigment = strstr(tabObj, "<");
		if(tabPigment !=NULL){
			sscanf(tabPigment,"<%f,%f,%f>",&coneTmp.pigment.x,&coneTmp.pigment.y,&coneTmp.pigment.z);
		}else{
			printf("pb pigment cone\n");
			 exit(EXIT_FAILURE);
		}
	}
	
	//on creer les matrices nécessaires aux transformations		
	coneTmp.matriceTransfo = creerMatrice(4);//matrice transformation
	coneTmp.matriceTransfoInverse = creerMatrice(4);//matrice inverse de la transformation
	/*on les initialises a la matrice identité pour que quand il n'y a aucune transformation, le produit de la matrice et du
	rayon reste inchanger*/
	coneTmp.matriceTransfo = matriceIdentite(coneTmp.matriceTransfo,4);
	coneTmp.matriceTransfoInverse = matriceIdentite(coneTmp.matriceTransfo,4);
	
	//on creer une liste de transformation qui contient toutes les transformations ajouter par l'utilisateur
	liste = getTransformation(tabObj,tailleFichier, i,fichier,liste,matriceTranslate, matriceScale, matriceRotate);
        if(liste!=NULL){//si cette liste n'est pas nul on multiplie la matrice transformation du cone unitaire par la nouvelle
                    	coneTmp.matriceTransfo = produitMatricielle(initialiseMatrice(liste),coneTmp.matriceTransfo, 4);
        }
        //on calcule l'inverse de la matrice de transformation
	coneTmp.matriceTransfoInverse = matriceInverse(coneTmp.matriceTransfo,4);
	//on defini le nouveau maillon et on l'ajoute a la tete de la liste
	(*nvCone).cone1 = coneTmp;
	//si il est dans une intersection
	if((*objetcsg).booleenCSG==1){
		coneTmp.booleenCSG=1;
	}
	else if((*objetcsg).booleenCSG==2){
		coneTmp.booleenCSG=2;
		(*objetcsg).ordreObjet=3;
		(*objetcsg).lcone=nvCone;
	}
}

//fonction qui lit un tore
void lireTore(listeTorus* nvTore, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg){
	torus tore;//structure a initialiser
	int j;//valeur a incrementer
	char* tabPigment;//tableau de caractere qui va stocker le pigment du tore
               
        //on parcourt la structure du cone jusqu'a trouver les deux rayons 	
        (*i)++;
	while(((fichier[*i]=='\n' || fichier[*i]==' ')&&(fichier[*i]!=',')) && tailleFichier != *i){
		(*i)++;
	}
	if(fichier[*i]==','){
		(*i)++;
	}	
			
	tore.rayon1 = strtof(&fichier[*i],NULL);

		
	//on boucle jusqu'a la fin du premier rayon
	while(((fichier[*i]!='\n' && fichier[*i]!=' ' && fichier[*i]!=',')) && tailleFichier != *i){	
		(*i)++;
	}
	
	//on boucle jusqu'a trouver le deuxieme rayon
	while(((fichier[*i]=='\n' || fichier[*i]==' ')&&(fichier[*i]!=',')) && tailleFichier != *i){
		(*i)++;
	}
	if(fichier[*i]==','){
		(*i)++;
	}	
			
	tore.rayon2 = strtof(&fichier[*i],NULL);

	j=0;
	while(fichier[*i]!='}' && tailleFichier != *i){//on boucle jusqu'a la fin du fichier pour voir si le tore contient un pigment si oui on initialise la couleur du tore avec le pigment trouvé
		tabObj[j]= fichier[*i];
		j++;
		(*i)++;
	}

	if(strstr(tabObj, "pigment")!=NULL){
		tabPigment = strstr(tabObj, "<");
		if(tabPigment !=NULL){
			sscanf(tabPigment,"<%f,%f,%f>",&tore.pigment.x,&tore.pigment.y,&tore.pigment.z);
		}else{
			printf("pb pigment tore\n");
			 exit(EXIT_FAILURE);
		}
	}
	
	//on creer les matrices nécessaires aux transformations	
	tore.matriceTransfo = creerMatrice(4);//matrice transformation
	tore.matriceTransfoInverse = creerMatrice(4);//matrice inverse de la transformation
	/*on les initialises a la matrice identité pour que quand il n'y a aucune transformation, le produit de la matrice et du
	rayon reste inchanger*/
	tore.matriceTransfo = matriceIdentite(tore.matriceTransfo,4);
	tore.matriceTransfoInverse = matriceIdentite(tore.matriceTransfo,4);
			
	//comme povray on initialise le tore selon l'axe y
	tore.matriceTransfo = transformation(3,vector(-90,0,0));
	
	//on creer une liste de transformation qui contient toutes les transformations ajouter par l'utilisateur	
	liste = getTransformation(tabObj,tailleFichier, i,fichier,liste,matriceTranslate, matriceScale, matriceRotate);
        if(liste!=NULL){//si cette liste n'est pas nul on multiplie la matrice transformation du tore par la nouvelle
                 tore.matriceTransfo = produitMatricielle(initialiseMatrice(liste),tore.matriceTransfo, 4);
        }
        
        //on calcule l'inverse de la matrice de transformation
	tore.matriceTransfoInverse = matriceInverse(tore.matriceTransfo,4);

	//on defini le nouveau maillon et on l'ajoute a la tete de la liste
	(*nvTore).tore = tore;
	//si il est dans une intersection
	if((*objetcsg).booleenCSG==1){
		tore.booleenCSG=1;
	}
	else if((*objetcsg).booleenCSG==2){
		tore.booleenCSG=2;
		(*objetcsg).ordreObjet=6;
		(*objetcsg).ltore=nvTore;
	}
}

//fonction permettant de parcourir la structure de l'objet ou elle est appelé et de trouver les transformations rentrer manuellement par l'utilsateur
//elle renvoit la matrice produit
listeMatrice* getTransformation(char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate ){
	vecteur vecteurTmp;//vecteur temporaire permettant de stocker les coordonnees des transformations
	int j;//indice a incrementé
	(*i)++;
	while(fichier[*i]!='}' && tailleFichier >= *i){//tant qu'on est pas a la fin de la structure de l'objet courant on parcourt cette structure
		j=0;
          
		while((fichier[(*i)]!='<' && fichier[(*i)+1]!='}') && tailleFichier >= (*i)){//tant qu'on ne trouve pas un vecteur associer a une transformation on continue de boucler
			tabObj[j] = fichier[(*i)];
			(*i)++;
			j++;
		}
		tabObj[j+1]='\0';
		//si la transformation trouver est un translate
		if(strstr(tabObj, "translate")!= NULL){
			j=0;
			while(fichier[(*i)-1]!='>' && tailleFichier != (*i)){
				tabObj[j]=fichier[(*i)];
				(*i)++;
				j++;
			}               
			enleveEspace(tabObj);
			if(!(sscanf(tabObj, "<%f,%f,%f>",&vecteurTmp.x, &vecteurTmp.y, &vecteurTmp.z)==3)){//on initialise les coordonnees du vecteur temporaire avec les coordonnees du translate
				printf("probleme translate\n");
			}
                	//on initialise la matrice de translation puis on l'ajoute a la liste de transformation
			matriceTranslate = transformation(1,vecteurTmp);
			liste = ajouterEnTete(liste, &matriceTranslate);
		}
        	
        	//si la transformation est un scale
		if(strstr(tabObj, "scale")!= NULL){
			j=0;
			while(fichier[(*i)-1]!='>' && tailleFichier != (*i)){
				tabObj[j]=fichier[(*i)];
				(*i)++;
				j++;
			}               
			enleveEspace(tabObj);
			if(!(sscanf(tabObj, "<%f,%f,%f>",&vecteurTmp.x, &vecteurTmp.y, &vecteurTmp.z)==3)){//on initialise les coordonnees du vecteur temporaire avec les coordonnees du scale
				printf("probleme scale\n");
			}
                	
                	//on initialise la matrice scale puis on l'ajoute a la liste de transformation
			matriceScale = transformation(2,vecteurTmp);
			liste = ajouterEnTete(liste, &matriceScale);
		}
        	
        	//si la transformation est un rotate
		if(strstr(tabObj, "rotate")!= NULL){
			j=0;
			while(fichier[(*i)-1]!='>' && tailleFichier != (*i)){
				tabObj[j]=fichier[(*i)];
				(*i)++;
				j++;
			}               
			enleveEspace(tabObj);
			if(!(sscanf(tabObj, "<%f,%f,%f>",&vecteurTmp.x, &vecteurTmp.y, &vecteurTmp.z)==3)){//on initialise les coordonnees du vecteur temporaire avec les coordonnees du rotate
				printf("probleme rotate\n");
			}
                	//on initialise la matrice de rotation puis on l'ajoute a la liste de transformation
			matriceRotate = transformation(3,vecteurTmp);
			liste = ajouterEnTete(liste, &matriceRotate);
		}
		(*i)++;
	}
	return liste;//on retourne la liste de toutes les transformations
}

//fonction permettant d'initialiser la matrice transformation finale grace au produit de toutes les matrices transformations calculer
double** initialiseMatrice(listeMatrice* liste){
	double** matriceTmp;//matrice temporaire pour le calcule du produit
	listeMatrice* tmp=liste;//on initialise un maillon permettant de parcourir la liste 
	
	/** 
	 *ici on considère que l'utilisateur a rentrer un seul vecteur, par transformation donc on fera au maximum 3 produits
	 */
        if(tmp->suivant !=NULL){//si la liste possède une matrice suivante
        	//on fait le produit de la matrice en cours et de la matrice suivante
		matriceTmp = produitMatricielle(*(tmp->matrice),(*tmp->suivant->matrice),4); 
		tmp = tmp->suivant;//on passe au suivant
		if(tmp->suivant!=NULL){//si le suivant est different de null on fait le produit de la matrice calculer précédemment avec la matrice suivante
			matriceTmp = produitMatricielle(matriceTmp, (*tmp->suivant->matrice),4);
		}		
	}else{//sinon si il y a au moins une matrice dans la liste on l'ajoute a la matrice résultat
		if(tmp!=NULL){
			matriceTmp = *(tmp->matrice);
		}
	}
	return matriceTmp;//on renvoit la matrice résultat
}
