/* \file raytracer.c
 *  \author Razavet Maël & Klelifa Sarah
 *  \version 0.1
 *  \date 10/11/10
 *  
 *  \brief Fonction qui permet de lancer le programme
 *
 *
 *
 */
//Inclusion des entêtes de librairie
#include "raytracer.h"

//fonction qui renvoit l'objet qui rentre en premier en contact avec le rayon
int objetLePlusProche(objet obj, vecteur* plusProcheIntersection,objetPlusProche* objetProche, rayon ray, objetCSG objetcsg, listeIntersection lIntersection){
	float t;//variable t de l'équation d'un rayon
	float* distance;//tableau de distance
	int* intersection;//tableau dintersection selon le type
	int type;//type de lobjet intercepté
	int i;//un compteur
	int imin;//indice du minimum du tableau
	int boolIntersection;//booleen pour savoir si il y a intersection ou pas
	float distanceTmpSphere;//distance entre rayon et sphere
	float distanceTmpPlan;//distance entre rayon et plan
	float distanceTmpCylindre;//distance entre rayon et cylindre
	float distanceTmpCone;//distance entre rayon et cone
	float distanceTmpBox;//distance entre rayon et box
	float distanceTmpTriangle;//distance entre rayon et triangle
	float distanceTmpTorus;//distance entre rayon et tore
	//les coordonnées de l'intersection
	vecteur intersectSphere;//coordonnées de l'intersection avec une sphere
	vecteur intersectPlan1;//coordonnées de l'intersection avec un plan
	vecteur intersectionCylindre;//coordonnées de l'intersection avec un cylindre
	vecteur intersectionCone;//coordonnées de l'intersection avec un cone
	vecteur intersectionBox;//coordonnées de l'intersection avec un cube
	vecteur intersectionTriangle;//coordonnées de l'intersection avec un triangle
	vecteur intersectionTorus;//coordonnées de l'intersection avec un tore
	//on initialise les vecteurs qui auront les intersections
	vecteur plusProcheIntersectionSphere;//coordonnées de l'intersection la plus proche avec la sphere
	vecteur plusProcheIntersectionPlan;//coordonnées de l'intersection la plus proche avec le plan
	vecteur plusProcheIntersectionCylindre;//coordonnées de l'intersection la plus proche avec le cylindre
	vecteur plusProcheIntersectionCone;//coordonnées de l'intersection la plus proche avec le cone
	vecteur plusProcheIntersectionBox;//coordonnées de l'intersection la plus proche avec le cube
	vecteur plusProcheIntersectionTriangle;//coordonnées de l'intersection la plus proche avec le triangle
	vecteur plusProcheIntersectionTore;//coordonnées de l'intersection la plus proche avec le tore
	//on initialise le nombre dintersections pour chaque objet
	int nbSphere;//nombre de sphere intercepté
	int nbPlan;//nombre de plan intercepté
	int nbCylindre;//nombre de cylindre intercepté
	int nbCone;//nombre de cone intercepté
	int nbCube;//nombre de cube intercepté
	int nbTriangle;//nombre de triangle intercepté
	int nbTore;//nombre de tore intercepté
	
	//initialisation des variables
	nbSphere=0;
	nbPlan=0;
	nbCylindre=0;
	nbCone=0;
	nbCube=0;
	nbTriangle=0;
	nbTore=0;
	t=0;//on initialise a 0
	imin=-1;
	boolIntersection = 0;
	intersectSphere=vector(0,0,0);
	intersectPlan1=vector(0,0,0);
	intersectionCylindre=vector(0,0,0);
	intersectionCone=vector(0,0,0);
	intersectionBox=vector(0,0,0);
	intersectionTriangle=vector(0,0,0);
	intersectionTorus=vector(0,0,0);
	plusProcheIntersectionSphere=vector(0,0,0);
	plusProcheIntersectionPlan=vector(0,0,0);
	plusProcheIntersectionCylindre=vector(0,0,0);
	plusProcheIntersectionCone=vector(0,0,0);
	plusProcheIntersectionBox=vector(0,0,0);
	plusProcheIntersectionTriangle=vector(0,0,0);
	plusProcheIntersectionTore=vector(0,0,0);
	i=0;
	type=-1;
	
	//allocation de la memoire pour notre tableau de distance dobjet
	distance = malloc(7*sizeof(float));
	//on initialise tout les valeur de la distance a une tres grande valeur 
	for(i=0; i<7; i++){
		distance[i] = 999999;
	}
	//allocation de la memoire pour notre tableau de booleen
	intersection = malloc(7*sizeof(int));
	//on initialise tout les valeur du boolen a 0
	for(i=0; i<7; i++){
		intersection[i] = 0;
	}

	//on regarde qu'elle est la sphere la plus proche si il y en a une
	if(obj.lsphere!=NULL){
		//on initialise le type en fonction de lobjet
		type = 0;
		//declaration et initialisation de la sphere courant
		listeSphere* tmpSphere;
		tmpSphere = obj.lsphere;
		//les coordonnees de la noramle
		vecteur normale;
		//tant qu'il y a de sphere
  		while(tmpSphere!=NULL){
  			//si il y a intersection avec cet objet courant
			if(intersectionSphere(ray,(*tmpSphere).boule, &t, &intersectSphere,&normale)){
				//on initialise la case type a 1
				intersection[type]=1;
				//on incremente le nombre dintersection de cet objet
				nbSphere++;
				//on calcule la distance entre cet objet et lorigine du rayon
				distanceTmpSphere = calculDistance(ray.origine, intersectSphere);
				//si la sphere courante est plus proche que les autres alors on recupere ces informations
				if(distanceTmpSphere<distance[type]){
					//on initialise le tableau de distance a la distance que lon vient de calculer
					distance[type]=distanceTmpSphere;
					//on initialise la valeur de la normale de lobjet courant
					(*tmpSphere).boule.normale = vector(normale.x, normale.y, normale.z);
					//on initalise la sphere la plus proche a la sphere courante
					(*objetProche).spherePlusProche=(*tmpSphere).boule;
					//on initialise la valeur de lintersection la plus proche de cet objet courant
					plusProcheIntersectionSphere =vector( intersectSphere.x, intersectSphere.y, intersectSphere.z);
				}
			}
			//on passe à la sphère suivante
			tmpSphere = (*tmpSphere).suivant;
		}
	}
	if(obj.lplan!=NULL){
		type=1;//on indique que c'est un plan
		//declaration et initialisation du plan courant
		listePlane* tmpPlane;
		tmpPlane = obj.lplan;
		//coordonnée du vecteur normale a lobjet
		vecteur normale;
		//tant qu'il y a de plan
		while(tmpPlane!=NULL){
			//si il y a intersection avec cet objet courant
			if(intersectPlan(ray,&(*tmpPlane).plan,&t,&intersectPlan1,&normale)){
				//on initialise la case type a 1
				intersection[type]=1;
				//on incremente le nombre dintersection de cet objet
				nbPlan++;
				//on calcule la distance entre cet objet et lorigine du rayon
				distanceTmpPlan = calculDistance(ray.origine, intersectPlan1);
				if(distanceTmpPlan<distance[type]){
					//on initialise le tableau de distance a la distance que lon vient de calculer
					distance[type]=distanceTmpPlan;
					//on initialise la valeur de la normale de lobjet courant
					(*tmpPlane).plan.normale = vector(normale.x, normale.y, normale.z);
					//on initalise la sphere la plus proche a la sphere courante
					(*objetProche).planPlusProche=(*tmpPlane).plan;
					//on initialise la valeur de lintersection la plus proche de cet objet courant
					plusProcheIntersectionPlan = intersectPlan1;
				}
			}
			//on passe au plan suivant
			tmpPlane = (*tmpPlane).suivant;
		}
	}
	//on regarde qu'elle est le cylindre le plus proche si il y en a un
	if(obj.lcylindre!=NULL){
		//on initialise le type en fonction de lobjet
		type=2;
		//declaration et initialisation du cylindre courant
		listeCylinder* tmpCylindre;
		tmpCylindre = obj.lcylindre;
		//les coordonnees de la noramle
		vecteur normale;
		//tant qu'il y a de cylindre
		while(tmpCylindre!=NULL){
			//si il y a intersection avec cet objet courant
			if(intersectCylindre(ray,(*tmpCylindre).cylindre,&t,&intersectionCylindre, &normale)){
				//on initialise la case type a 1
				intersection[type]=1;
				//on incremente le nombre dintersection de cet objet
				nbCylindre++;
				//on calcule la distance entre cet objet et lorigine du rayon
				distanceTmpCylindre = calculDistance(ray.origine, intersectionCylindre);
				//si le cylindre courant est plus proche que les autres alors on recupere ces informations
				if(distanceTmpCylindre<distance[type]){
					//on initialise le tableau de distance a la distance que lon vient de calculer
					distance[type]=distanceTmpCylindre;
					//on initialise la valeur de la normale de lobjet courant
					(*tmpCylindre).cylindre.normale = normale;
					//on initalise la sphere la plus proche a la sphere courante
					(*objetProche).cylindrePlusProche=(*tmpCylindre).cylindre;
					//on initialise la valeur de lintersection la plus proche de cet objet courant
					plusProcheIntersectionCylindre = intersectionCylindre;
				}
			}
			//on passe au cylindre suivant
			tmpCylindre = (*tmpCylindre).suivant;
		}
	}
	//on regarde qu'elle est le cone le plus proche si il y en a un
	if(obj.lcone!=NULL){
		//on initialise le type en fonction de lobjet
		type=3;
		//declaration et initialisation du cone courant
		listeCone* tmpCone;
		tmpCone = obj.lcone;
		//tant qu'il y a de cone
		while(tmpCone!=NULL){
			//si il y a intersection avec cet objet courant
			if(intersectCone(ray,(*tmpCone).cone1,&t,&intersectionCone)){
				//on initialise la case type a 1
				intersection[type]=1;
				//on incremente le nombre dintersection de cet objet
				nbCone++;
				//on calcule la distance entre cet objet et lorigine du rayon
				distanceTmpCone = calculDistance(ray.origine, intersectionCone);
				//si le cone courant est plus proche que les autres alors on recupere ces informations
				if(distanceTmpCone<distance[type]){
					//on initialise le tableau de distance a la distance que lon vient de calculer
					distance[type]=distanceTmpCone;
					//on initalise la sphere la plus proche a la sphere courante
					(*objetProche).conePlusProche=(*tmpCone).cone1;
					//on initialise la valeur de lintersection la plus proche de cet objet courant
					plusProcheIntersectionCone = intersectionCone;
				}
			}
			//on passe au cone suivant
			tmpCone = (*tmpCone).suivant;
		}
	}
	//on regarde qu'elle est le cube le plus proche si il y en a un
	if(obj.lbox!=NULL){
		//on initialise le type en fonction de lobjet
		type=4;
		//declaration et initialisation de la box courante
		listeBox* tmpBox;
		tmpBox = obj.lbox;
		//coordonnée du vecteur normale a lobjet
		vecteur normale;
		//tant qu'il y a du cube
		while(tmpBox!=NULL){
			//si il y a intersection avec cet objet courant
			if(intersectCube(ray,(*tmpBox).boite,&t,&intersectionBox,&normale)){
				//on initialise la case type a 1
				intersection[type]=1;
				//on incremente le nombre dintersection de cet objet
				nbCube++;
				//on calcule la distance entre cet objet et lorigine du rayon
				distanceTmpBox = calculDistance(ray.origine, intersectionBox);
				//si le cube courant est plus proche que les autres alors on recupere ces informations
				if(distanceTmpBox<distance[type]){
					//on initialise le tableau de distance a la distance que lon vient de calculer
					distance[type]=distanceTmpBox;
					//on initialise la valeur de la normale de lobjet courant
					(*tmpBox).boite.normale = normale;
					//on initalise la sphere la plus proche a la sphere courante
					(*objetProche).boitePlusProche=(*tmpBox).boite;
					//on initialise la valeur de lintersection la plus proche de cet objet courant
					plusProcheIntersectionBox = intersectionBox;
				}
			}
			//on passe au cube suivant
			tmpBox = (*tmpBox).suivant;
		}
	}
	//on regarde qu'elle est le cube le plus proche si il y en a un
	if(obj.ltriangle!=NULL){
		//on initialise le type en fonction de lobjet
		type=5;
		//declaration et initialisation du triangle courant
		listeTriangle* tmpTriangle;
		tmpTriangle = obj.ltriangle;
		//coordonnée du vecteur normale a lobjet
		vecteur normale;
		//tant qu'il y a de triangle
		while(tmpTriangle!=NULL){
			//si il y a intersection avec cet objet courant
			if(intersectTriangle(ray,(*tmpTriangle).tgle,&t,&intersectionTriangle,1,&normale)){
				//on initialise la case type a 1
				intersection[type]=1;
				//on incremente le nombre dintersection de cet objet
				nbTriangle++;
				//on calcule la distance entre cet objet et lorigine du rayon
				distanceTmpTriangle = calculDistance(ray.origine, intersectionTriangle);
				//si le triangle courant est plus proche que les autres alors on recupere ces informations
				if(distanceTmpTriangle<distance[type]){
					//on initialise le tableau de distance a la distance que lon vient de calculer
					distance[type]=distanceTmpTriangle;
					//on initialise la valeur de la normale de lobjet courant
					(*tmpTriangle).tgle.normale = normale;
					//on initalise la sphere la plus proche a la sphere courante
					(*objetProche).trianglePlusProche=(*tmpTriangle).tgle;
					//on initialise la valeur de lintersection la plus proche de cet objet courant
					plusProcheIntersectionTriangle = intersectionTriangle;
				}
			}
			//on passe au triangle suivant
			tmpTriangle = (*tmpTriangle).suivant;
		}
	}
	
	//on regarde qu'elle est le tore le plus proche si il y en a un
	if(obj.ltore!=NULL){
		//on initialise le type en fonction de lobjet
		type=6;
		//coordonnée du vecteur normale a lobjet
		vecteur normale;
		//declaration et initialisation dutorecourant
		listeTorus* tmpTorus;
		tmpTorus = obj.ltore;
		//tant qu'il y a de tore
		while(tmpTorus!=NULL){
			//si il y a intersection avec cet objet courant
			if(intersectTore(ray,(*tmpTorus).tore,&t,&intersectionTorus,&normale)){
				//on initialise la case type a 1
				intersection[type]=1;
				//on incremente le nombre dintersection de cet objet
				nbTore++;
				//on calcule la distance entre cet objet et lorigine du rayon
				distanceTmpTorus = calculDistance(ray.origine, intersectionTorus);
				//si le tore courant est plus proche que les autres alors on recupere ces informations
				if(distanceTmpTorus<distance[type]){
					//on initialise le tableau de distance a la distance que lon vient de calculer
					distance[type]=distanceTmpTorus;
					//on initialise la valeur de la normale de lobjet courant
					(*tmpTorus).tore.normale = normale;
					//on initalise la sphere la plus proche a la sphere courante
					(*objetProche).torePlusProche=(*tmpTorus).tore;
					//on initialise la valeur de lintersection la plus proche de cet objet courant
					plusProcheIntersectionTore = intersectionTorus;
				}
			}
			//on passe au tore suivant
			tmpTorus = (*tmpTorus).suivant;
		}
	}
	
	
	//on test si il y a au moins une intersection
	for(i=0; i<7; i++){
		//on calcule la valeur du booleen 
		boolIntersection = (distance[i]!=999999) || boolIntersection;
	}
	
	//on cherche l'indice du minimum du tableau pour savoir de quel type est l'objet le plus proche
	//on initialise la valeur du imin au premier indice dont la valeur est non nul
 	if(boolIntersection){
 		//on initialise le imin a 0
 	  	imin = 0;
 	  	//boucle pour parcourir le tableau de distance
		for(i=0; i<7; i++){		
			//si la distance de lobjet de type i est plus petite que celle de lobjet de type imin
			if(distance[i]<distance[imin]){
				//on recupere la valeur du type de lobjet dans imin
				imin=i;
			}
		}	     	   
	}
 	
	//si il y a une intersection de définie
	if(objetcsg.booleenCSG==1){
		//on regarde qu'elle objet est le plus proche et on initialise la valeur de l'intersection
		switch (imin){
		case 0: //si c'est une sphere
			//si cet objet a ete une seule foie
			if(nbSphere==1){
				//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
				if(intersection[1]==0 && intersection[2]==0 && intersection[3]==0 && intersection[4]==0 && intersection[5]==0 && intersection[6]==0){
					//on renvoie -1 ce qui veut dire quon ne prend pas en compte cette intersection
					imin=-1;
				}
				//sinon on renvoie la bonne intersection, cad la plus proche
				else{
					(*plusProcheIntersection) = plusProcheIntersectionBox;
				}
			}
			//sinon on renvoie seulement la plus proche intersection entre les points dintersection commun
			else{
				(*plusProcheIntersection) = plusProcheIntersectionSphere;
			}
			break;
		case 1: //si c'est un plan
			//si cet objet a ete une seule foie
			if(nbPlan==1){
				//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
				if(intersection[0]==0 && intersection[2]==0 && intersection[3]==0 && intersection[4]==0 && intersection[5]==0 && intersection[6]==0){
					imin=-1;
				}
				//sinon on renvoie la bonne intersection, cad la plus proche
				else{
					(*plusProcheIntersection) = plusProcheIntersectionPlan;
				}
			}
			//sinon on renvoie seulement la plus proche intersection 
			else{
				(*plusProcheIntersection) = plusProcheIntersectionPlan;
			}
			break;
		case 2: //si c'est un cylindre
			//si cet objet a ete une seule foie
			if(nbCylindre==1){
				//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
				if(intersection[0]==0 && intersection[1]==0 && intersection[3]==0 && intersection[4]==0 && intersection[5]==0 && intersection[6]==0){
					imin=-1;
				}
				//sinon on renvoie la bonne intersection, cad la plus proche
				else{
					(*plusProcheIntersection) = plusProcheIntersectionCylindre;
				}
			}	
			//sinon on renvoie seulement la plus proche intersection 	
			else{
				(*plusProcheIntersection) = plusProcheIntersectionCylindre;
			}	
			break;
		case 3: //si c'est un cone
			//si cet objet a ete une seule foie
			if(nbCone==1){
				//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
				if(intersection[0]==0 && intersection[1]==0 && intersection[2]==0 && intersection[3]==0 && intersection[5]==0 && intersection[6]==0){
					imin=-1;
				}
				//sinon on renvoie la bonne intersection, cad la plus proche
				else{
					(*plusProcheIntersection) = plusProcheIntersectionCone;
				}
			}	
			//sinon on renvoie seulement la plus proche intersection 
			else{
					(*plusProcheIntersection) = plusProcheIntersectionCone;
			}	
			break;		
		case 4://si cest une box
			//si cet objet a ete une seule foie
			if(nbCube==1){
				//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
				if(intersection[0]==0 && intersection[1]==0 && intersection[2]==0 && intersection[3]==0 && intersection[5]==0 && intersection[6]==0){
					imin=-1;
				}
				//sinon on renvoie la bonne intersection, cad la plus proche
				else{
					(*plusProcheIntersection) = plusProcheIntersectionBox;
				}
			}	
			//sinon on renvoie seulement la plus proche intersection 
			else{
					(*plusProcheIntersection) = plusProcheIntersectionBox;
				}
			break;
		case 5://si cest un triangle
			//si cet objet a ete une seule foie
			if(nbTriangle==1){
				//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
				if(intersection[0]==0 && intersection[1]==0 && intersection[2]==0 && intersection[3]==0 && intersection[4]==0 && intersection[6]==0){
					imin=-1;
				}
				//sinon on renvoie la bonne intersection, cad la plus proche
				else{
					(*plusProcheIntersection) = plusProcheIntersectionTriangle;
				}
			}	
			//sinon on renvoie seulement la plus proche intersection 
			else{
					(*plusProcheIntersection) = plusProcheIntersectionTriangle;
				}
			break;
		case 6://si cest un tore
			//si cet objet a ete une seule foie
			if(nbTore==1){
				//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
				if(intersection[0]==0 && intersection[1]==0 && intersection[2]==0 && intersection[3]==0 && intersection[4]==0 && intersection[5]==0){
					imin=-1;
				}
				//sinon on renvoie la bonne intersection, cad la plus proche
				else{
					(*plusProcheIntersection) = plusProcheIntersectionTore;
				}
			}	
			//sinon on renvoie seulement la plus proche intersection 
			else{
					(*plusProcheIntersection) = plusProcheIntersectionTore;
				}		
			break;		
		default:
			//pour linstant rien ne se passe	
			break;
		}
	}
	//si on a une difference de définie
	else if(objetcsg.booleenCSG==2){
			//on regarde qu'elle objet est le plus proche et on initialise la valeur de l'intersection
			switch (imin){
			case 0: //si c'est une sphere sur lequel on fait une différence
				if(objetcsg.ordreObjet==0){
					//si cet objet a ete une seule foie
					if(nbSphere==1){
						//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
						if((intersection[1]==1 && distance[1]<distance[imin]) || (intersection[2]==1 && distance[2]<distance[imin]) || (intersection[3]==1 && distance[3]<distance[imin]) || (intersection[4]==1 && distance[4]<distance[imin]) || (intersection[5]==1 && distance[5]<distance[imin]) || (intersection[6]==1 && distance[6]<distance[imin])){
							//on renvoie -1 ce qui veut dire quon ne prend pas en compte cette intersection
							imin=-1;
						}
						//sinon on renvoie la bonne intersection, cad la plus proche
						else{
							(*plusProcheIntersection) = plusProcheIntersectionSphere;
						}
					}
					//sinon il n'y a pas d'intersection de garder
					else{
							imin=-1;
					}
				}
				//sinon il n'y a pas d'intersection de garder
				else{
					imin=-1;
				}
				break;	
				
			case 1: //si c'est un plan sur lequel on fait une différence
				if(objetcsg.ordreObjet==1){
					//si cet objet a ete une seule foie
					if(nbPlan==1){
						//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
						if((intersection[0]==1 && distance[0]<distance[imin]) || (intersection[2]==1 && distance[2]<distance[imin]) || (intersection[3]==1 && distance[3]<distance[imin]) || (intersection[4]==1 && distance[4]<distance[imin]) || (intersection[5]==1 && distance[5]<distance[imin]) || (intersection[6]==1 && distance[6]<distance[imin])){
							//on renvoie -1 ce qui veut dire quon ne prend pas en compte cette intersection
							imin=-1;
						}
						//sinon on renvoie la bonne intersection, cad la plus proche
						else{
							(*plusProcheIntersection) = plusProcheIntersectionPlan;
						}
					}
					//sinon il n'y a pas d'intersection de garder
					else{
							imin=-1;
					}
				}
				//sinon il n'y a pas d'intersection de garder
				else{
					imin=-1;
				}
				break;	
			case 2: //si c'est un Cylindre sur lequel on fait une différence
				if(objetcsg.ordreObjet==imin){
					//si cet objet a ete une seule foie
					if(nbCylindre==1){
						//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
						if((intersection[0]==1 && distance[0]<distance[imin]) || (intersection[1]==1 && distance[1]<distance[imin]) || (intersection[3]==1 && distance[3]<distance[imin]) || (intersection[4]==1 && distance[4]<distance[imin]) || (intersection[5]==1 && distance[5]<distance[imin]) || (intersection[6]==1 && distance[6]<distance[imin])){
							//on renvoie -1 ce qui veut dire quon ne prend pas en compte cette intersection
							imin=-1;
						}
						//sinon on renvoie la bonne intersection, cad la plus proche
						else{
							(*plusProcheIntersection) = plusProcheIntersectionCylindre;
						}
					}
					//sinon il n'y a pas d'intersection de garder
					else{
							imin=-1;
					}
				}
				//sinon il n'y a pas d'intersection de garder
				else{
					imin=-1;
				}
				break;		
			case 3: //si c'est un cone sur lequel on fait une différence
				if(objetcsg.ordreObjet==imin){
					//si cet objet a ete une seule foie
					if(nbCone==1){
						//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
						if((intersection[0]==1 && distance[0]<distance[imin]) || (intersection[1]==1 && distance[1]<distance[imin]) || (intersection[2]==1 && distance[2]<distance[imin]) || (intersection[4]==1 && distance[4]<distance[imin]) || (intersection[5]==1 && distance[5]<distance[imin]) || (intersection[6]==1 && distance[6]<distance[imin])){
							//on renvoie -1 ce qui veut dire quon ne prend pas en compte cette intersection
							imin=-1;
						}
						//sinon on renvoie la bonne intersection, cad la plus proche
						else{
							(*plusProcheIntersection) = plusProcheIntersectionCone;
						}
					}
					//sinon il n'y a pas d'intersection de garder
					else{
							imin=-1;
					}
				}
				//sinon il n'y a pas d'intersection de garder
				else{
					imin=-1;
				}
				break;	
							
			case 4://si cest une box sur lequel on fait une différence
				if(objetcsg.ordreObjet==4){
					//si cet objet a ete une seule foie
					if(nbCube==1){
						//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
						if((intersection[1]==1 && distance[1]<distance[imin]) || (intersection[2]==1 && distance[2]<distance[imin]) || (intersection[3]==1 && distance[3]<distance[imin]) || (intersection[0]==1 && distance[0]<distance[imin]) || (intersection[5]==1 && distance[5]<distance[imin]) || (intersection[6]==1 && distance[6]<distance[imin])){
							imin=-1;
						}
						//sinon on renvoie la bonne intersection, cad la plus proche
						else{
							(*plusProcheIntersection) = plusProcheIntersectionBox;
						}
					}	
					//sinon il n'y a pas d'intersection de garder
					else{
							imin=-1;
					}
				}
				//sinon il n'y a pas d'intersection de garder
				else{
					imin=-1;
				}	
				break;	
			case 5://si cest un triangle sur lequel on fait une différence
				if(objetcsg.ordreObjet==imin){
					//si cet objet a ete une seule foie
					if(nbTriangle==1){
						//si il n y a aucun point dintersection commun avec les autres objets alors imin=-1
						if((intersection[1]==1 && distance[1]<distance[imin]) || (intersection[2]==1 && distance[2]<distance[imin]) || (intersection[3]==1 && distance[3]<distance[imin]) || (intersection[0]==1 && distance[0]<distance[imin]) || (intersection[4]==1 && distance[4]<distance[imin]) || (intersection[6]==1 && distance[6]<distance[imin])){
							imin=-1;
						}
						//sinon on renvoie la bonne intersection, cad la plus proche
						else{
							(*plusProcheIntersection) = plusProcheIntersectionTriangle;
						}
					}	
					//sinon il n'y a pas d'intersection de garder
					else{
							imin=-1;
					}
				}
				//sinon il n'y a pas d'intersection de garder
				else{
					imin=-1;
				}	
				break;	
			case 6://si cest un tore sur lequel on fait une différence
				if(objetcsg.ordreObjet==imin){
					//si cet objet a ete une seule foie
					if(nbTore==1){
						//si il y a intersection avec un objet et quil est derriere cet objet courant alors imin=-1
						if((intersection[1]==1 && distance[1]<distance[imin]) || (intersection[2]==1 && distance[2]<distance[imin]) || (intersection[3]==1 && distance[3]<distance[imin]) || (intersection[0]==1 && distance[0]<distance[imin]) || (intersection[4]==1 && distance[4]<distance[imin]) || (intersection[5]==1 && distance[5]<distance[imin])){
							imin=-1;
						}
						//sinon on renvoie la bonne intersection, cad la plus proche
						else{
							(*plusProcheIntersection) = plusProcheIntersectionTore;
						}
					}	
					//sinon il n'y a pas d'intersection de garder
					else{
							imin=-1;
					}
				}
				//sinon il n'y a pas d'intersection de garder
				else{
					imin=-1;
				}	
				break;				
			default:
				break;	
			}
			
	}
	//si aucune csg de définie	
	else{
		//on regarde qu'elle objet est le plus proche et on initialise la valeur de l'intersection selon le type de lobjet le plus proche
		switch (imin){
		case 0: //si c'est une sphere
			(*plusProcheIntersection) = vector(plusProcheIntersectionSphere.x, plusProcheIntersectionSphere.y, plusProcheIntersectionSphere.z);
			break;
		case 1: //si c'est un plan
			(*plusProcheIntersection) = plusProcheIntersectionPlan;	
			break; 
		case 2://si c'est un cylindre
			(*plusProcheIntersection) = plusProcheIntersectionCylindre;
			break;
		case 3://si c'est un cone
			(*plusProcheIntersection) = plusProcheIntersectionCone;
			break;
		case 4://si c'est un cube
			(*plusProcheIntersection) = plusProcheIntersectionBox;
			break;	
		case 5://si c'est un triangle
			(*plusProcheIntersection) = plusProcheIntersectionTriangle;
			break;
		case 6://si c'est un tore
			(*plusProcheIntersection) = plusProcheIntersectionTore;
			break;	
		default:
			//pour linstant rien ne se passe	
			break;
		}
	
	}

	//on libère la mémoire allouée
	free(intersection);
	free(distance);
	//on retourne la valeur du type de l'objet dont on garde l'intersection
	return (imin);
}

//fonction qui permet d'émettre un rayon
void envoieRayon(int x, int y,objet obj, objetCSG objetcsg, listeIntersection lIntersection){
	int i;//compteur qui parcours l'écran de pixel dans le sens de la longueur
	int j;//compteur qui parcours l'écran de pixel dans le sens de la hauteur
	FILE* fichierRes;//fichier.ppm qui va nous permettre de visualiser le résultat du raytracring
	char buf[32];//chaine qui va nous permettre de  stocker une chaine de plusieurs entiers pour les couleurs
	vecteur vecteurDirecteurRayon;//le vecteur directeur du rayon
	vecteur vecteurOrigineRayon;//l'origine du rayon
	rayon ray;//nouveau rayon
	objetPlusProche objetProche;//nouvelle objet le plus proche
	vecteur mat;//nouveau vecteur pour récupérer les pigment de lobjet
	vecteur plusProcheIntersection;//nouveau vecteur contenant l'intersection la plus proche
	int type;//type de lobjet que lon considère
	int bool;//booleen qui nous indique si il y a eu intersection
	int typeOmbre;//type de lobjet le plus proche de la lumiere
	rayon rayLumiere;//nouveau rayon
	vecteur plusProcheIntersectionOmbre;//vecteur contenant la plus proche intersection avec la lumiere
	objetPlusProche objetProcheOmbre;//nouvelle objet contenant les objets les plus proches de la lumiere
	camera_new camAvecViewplane; //nouvelle camera ayant les arguments du viewplane egalement
	camAvecViewplane=creerCameraAvecViewplane(obj.cam);//on la creer
	calculPointHautGauche(&camAvecViewplane);//calcule le point haut gauche du viewplane
	
	//initialisation du booleen
        bool=1;
        
	//on ouvre le fichier et/ou on le crée si il n'existe pas
	fichierRes=fopen("ImageFinale.ppm", "w");
	//on stocke dans buf une chaine d'entiers
	sprintf(buf, "P3 %d %d 255", x, y);
	//on écrit la valeur de cette variables dans le fichier res
	fputs(buf, fichierRes);
	//on calcule l'origine du rayon qui reste fixe
	vecteurOrigineRayon = camAvecViewplane.position;
	//on parcours dans le sens de la largeur de l'écran
	for(j=0;j<y;j++){
		//on parcours dans le sens de la longueur
		for(i=0;i<x;i++){
			//bool vrai
			bool = 1;
			//initialisation du vecteur directeur du rayon
			vecteurDirecteurRayon= calculvecDirRayon(i,j,x,y, camAvecViewplane); 
			//on normalise le vecteur directeur
			vecteurDirecteurRayon=normaliser(vecteurDirecteurRayon);
			//on crée un nouveau rayon avec les 2 vecteurs calculés précédemment
			ray=creerRayon(vecteurOrigineRayon, vecteurDirecteurRayon);
			//si le rayon intercepte l'objet
			type = objetLePlusProche(obj, &plusProcheIntersection, &objetProche, ray, objetcsg, lIntersection);
			//declaration et initialisation du vecteur contenant les pigment de lobjet courant
			vecteur pigment;
			//declaration et initialisation dune nouvelle lumiere
			listeLight* tmpLumiere;   
			pigment = vector(0,0,0);
			tmpLumiere = obj.llumiere;
			//on parcours la liste de lumiere
			while(tmpLumiere!=NULL){
				//on va regarder si un objet coupe le rayon lumineux avant l'objet courant, si oui on creer une ombre
				//on creer un nouveau rayon de lumiere
				rayLumiere.origine = (*tmpLumiere).lumiere.location;
				rayLumiere.vectDir = opMoins(plusProcheIntersection,(*tmpLumiere).lumiere.location);
				rayLumiere.vectDir=normaliser(rayLumiere.vectDir);
				//on regarde quel est l'objet le plus proche de la lumiere pour voir si il y a un objet devant l'objet courant
				typeOmbre = objetLePlusProche(obj,&plusProcheIntersectionOmbre,&objetProcheOmbre, rayLumiere,objetcsg, lIntersection);
				//selon le type de lobjet courant
				switch (type){
				case 0: //si c'est une sphere on calcul la couleur du pigment de l'intersection selon qu'il soit dans l'ombre ou non
					mat = objetProche.spherePlusProche.pigment ;	
					//si le type de lombre est bien une sphere et que lombre et la sphere correspondent			
					if((typeOmbre==0 && compareSphere(objetProche.spherePlusProche, objetProcheOmbre.spherePlusProche)) || compareVecteur(plusProcheIntersectionOmbre,plusProcheIntersection)){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,lumierePixel(objetProche.spherePlusProche.normale, plusProcheIntersection, mat,(*tmpLumiere).lumiere,pigment));
					}
					//si il n'y pas d'ombre alors
					else if(typeOmbre!=-1){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,opProduit(mat, opProduitScalaire((*tmpLumiere).lumiere.color_rgb,0.1)));
					}
				break;
				case 1://si c'est un plan on calcul la couleur du pigment de l'intersection selon qu'il soit dans l'ombre ou non
					mat = objetProche.planPlusProche.pigment;
					//si le type de lombre est bien un plan et que lombre et le plan correspondent	
					if((typeOmbre==1 && comparePlan(objetProche.planPlusProche, objetProcheOmbre.planPlusProche)) || compareVecteur(plusProcheIntersectionOmbre,plusProcheIntersection)){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,lumierePixel(objetProche.planPlusProche.normale, plusProcheIntersection, mat,(*tmpLumiere).lumiere,pigment));
					}
					//si il n'y pas d'ombre alors
					else if(typeOmbre!=-1){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,opProduit(mat, opProduitScalaire((*tmpLumiere).lumiere.color_rgb,0.1)));
					}
					break;
				case 2://si c'est un cylindre on calcul la couleur du pigment de l'intersection selon qu'il soit dans l'ombre ou non
					mat = objetProche.cylindrePlusProche.pigment;
					//si le type de lombre est bien un cylindre et que lombre et le cylindre correspondent	
					if((typeOmbre==2 && compareCylindre(objetProche.cylindrePlusProche, objetProcheOmbre.cylindrePlusProche)) || compareVecteur(plusProcheIntersectionOmbre,plusProcheIntersection)){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,lumierePixel(objetProche.cylindrePlusProche.normale, plusProcheIntersection, mat,(*tmpLumiere).lumiere,pigment));
					}
					//si il n'y pas d'ombre alors
					else if(typeOmbre!=-1){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,opProduit(mat, opProduitScalaire((*tmpLumiere).lumiere.color_rgb,0.1)));
					}
					break;
				case 3://si c'est un cone on calcul la couleur du pigment de l'intersection selon qu'il soit dans l'ombre ou non
					mat = objetProche.conePlusProche.pigment;
					//si le type de lombre est bien un cone et que lombre et le cone correspondent	
					if((typeOmbre==3 && compareCone(objetProche.conePlusProche, objetProcheOmbre.conePlusProche)) || compareVecteur(plusProcheIntersectionOmbre,plusProcheIntersection)){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,lumierePixel(objetProche.conePlusProche.coordonneeExtremite1, plusProcheIntersection, mat,(*tmpLumiere).lumiere,pigment));
					}
					//si il n'y pas d'ombre alors
					else if(typeOmbre!=-1){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,opProduit(mat, opProduitScalaire((*tmpLumiere).lumiere.color_rgb,0.1)));
					}
					break;
				case 4://si c'est un cube on calcul la couleur du pigment de l'intersection selon qu'il soit dans l'ombre ou non
					mat = objetProche.boitePlusProche.pigment;
					//si le type de lombre est bien un cube et que lombre et le cube correspondent	
					if((typeOmbre==4 && compareCube(objetProche.boitePlusProche, objetProcheOmbre.boitePlusProche)) || compareVecteur(plusProcheIntersectionOmbre,plusProcheIntersection)){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,lumierePixel(objetProche.boitePlusProche.normale, plusProcheIntersection, mat,(*tmpLumiere).lumiere,pigment));
					}
					//si il n'y pas d'ombre alors
					else if(typeOmbre!=-1){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,opProduit(mat, opProduitScalaire((*tmpLumiere).lumiere.color_rgb,0.1)));
					}
					break;	
				case 5://si c'est un triangle on calcul la couleur du pigment de l'intersection selon qu'il soit dans l'ombre ou non
					mat = objetProche.trianglePlusProche.pigment;
					//si le type de lombre est bien un triangle et que lombre et le triangle correspondent	
					if((typeOmbre==5 && compareTriangle(objetProche.trianglePlusProche, objetProcheOmbre.trianglePlusProche)) || compareVecteur(plusProcheIntersectionOmbre,plusProcheIntersection)){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,lumierePixel(objetProche.trianglePlusProche.normale, plusProcheIntersection, mat,(*tmpLumiere).lumiere,pigment));
					}
					//si il n'y pas d'ombre alors
					else if(typeOmbre!=-1){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,opProduit(mat, opProduitScalaire((*tmpLumiere).lumiere.color_rgb,0.1)));
					}
					break;
				case 6://si c'est un tore on calcul la couleur du pigment de l'intersection selon qu'il soit dans l'ombre ou non
					mat = objetProche.torePlusProche.pigment;
					//si le type de lombre est bien un tore et que lombre et le tore correspondent	
					if((typeOmbre==6 && compareTorus(objetProche.torePlusProche, objetProcheOmbre.torePlusProche)) || compareVecteur(plusProcheIntersectionOmbre,plusProcheIntersection)){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,lumierePixel(objetProche.torePlusProche.normale, plusProcheIntersection, mat,(*tmpLumiere).lumiere,pigment));
					}
					//si il n'y pas d'ombre alors
					else if(typeOmbre!=-1){
						//on calcule la couleur de lobjet
						pigment = opPlus(pigment,opProduit(mat, opProduitScalaire((*tmpLumiere).lumiere.color_rgb,0.1)));
					}
					break; 
				  default:
					bool=0;//aucune intersection
				  break;
				}
				//on passe a la lumiere suivante
				tmpLumiere = (*tmpLumiere).suivant;
			}
			
			if(bool){
				//on multiplie par 22 le vecteur pigment pour pouvoir obtenir un fichier.ppm correct
				pigment = opProduitScalaire(pigment,255);
				//On introduit les 3 pigments de l'objet intersecté dans une chaine pour les ecrire dans le fichier
				sprintf(buf, " %d %d %d", (int)(pigment.x), (int)(pigment.y), (int)(pigment.z));
				//on ecrit dans le fichier les 3 pigments 
			}else{
				//On introduit les 3 pigments de la couleur de fond dans une chaine pour les ecrire dans le fichier
				sprintf(buf, " %d %d %d", (int)(obj.arrierePlan.color_rgb.x)*255, (int)(obj.arrierePlan.color_rgb.y)*255, (int)(obj.arrierePlan.color_rgb.z)*255);
				//on ecrit dans le fichier les 3 pigments 
			}
			//on écrit le buffer dans le fichier résultat
			fputs(buf, fichierRes);
		}
	}
	//on ferme le fichier
	fclose(fichierRes);
}


//fonction qui lance le programme
int main(int argc, const char* argv[]){
	//Déclaration de variables
	int x;//longueur
	int y;//largeur
	char chemin_fichier[200];// chaine de caractère pour le chemin du fichier
	objet obj;//nouvelle objet 
	objetCSG objetcsg;//nouvelle objet contenant des objets définit avec des CSG
	
	//initialisation de l'objet à NULL
	obj.llumiere = NULL;
	obj.lsphere = NULL;
	obj.lbox = NULL;
	obj.lcylindre = NULL;
	obj.ltore = NULL;
	obj.lcone = NULL;
	obj.lplan = NULL;
	obj.ltriangle=NULL;
	obj.arrierePlan.color_rgb = vector(0,0,0);
	//initialisation du booleen a faux
	objetcsg.booleenCSG=0;
	//nouvelle liste et initialisation d'objet qui ont été définis avec une intersection
	//**cette version n'a pas besoin de cette liste car pas encore complètement pris en compte
	listeIntersection lIntersection;
	lIntersection.suivant=NULL;
	lIntersection.obj.llumiere=NULL;

	
	//si l'utilisateur a saisie un argument 
	if(argv[1]!= NULL){
		// permet de copier le tableau en arguments
		strcpy(chemin_fichier, argv[1]);
	}else{
		//on affiche une erreur et on quitte
		printf("Fichier introuvable ou inexistant, veuillez resaisir le nom du fichier\n");
		return (EXIT_FAILURE);
	}

	//Si l'utilisateur saisie la résolution à l'éxecution et qu'il saisie la largeur et la longueur sinon ce sont les coordonnées par défaut
	if(argv[2]!=NULL && argv[3]!=NULL){     
		//x et y prennent les valeurs saisies
		x=atoi(argv[2]);
		y=atoi(argv[3]);
	}
	else{
		//On prédéfinit la résolution par défaut si l'utilisateur ne saisie aucune données.
		x=1000;
		y=1000;
	}
	//nouvelle objet initialisé grâce à lectureFichier.c
	ouvre(chemin_fichier, x, y,&obj, &objetcsg, &lIntersection);
	
	//envoyer des rayons sur toute la surface de lecran et dessine le fichier résultat en .ppm
	envoieRayon(x, y, obj, objetcsg, lIntersection);
	
	
        
	//on quitte avec succés
	return (EXIT_SUCCESS);

}
