/* \file cube.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date mond oct 11
 * 
 * \brief Fonction qui permet de calculer lintersection avec un cube
 *
 *
 */

//Inclusion des entetes de librairie
#include "cube.h"

//calcule l'intersection entre un rayon et un cube
int intersectCube(rayon ray, box b, float* t, vecteur* intersection, vecteur* normale){
	//declaration et initialisation des variables
	vecteur a1;//un coin du cube
	vecteur a2;//un coin du cube
	vecteur a3;//un coin du cube
	vecteur a4;//un coin du cube
	vecteur a5;//un coin du cube
	vecteur a6;//un coin du cube
	vecteur a7;//un coin du cube
	vecteur a8;//un coin du cube
	float cote;//côté du cube
	float distance;//distance entre origine du rayon et l'intersection calculée
	float distanceTmp;//une distance temporaire 
	int booleen;//booleen pour renvoyer si il y a intersection ou non
	float T_tmp;//t temporaire
	vecteur4 rayTransfoOrigine;//vecteurs permettant le produit matricielle avec la matrice Transformation
	vecteur4 rayTransfoDirecteur;
	vecteur4 normalTransfo;	//vecteur permettant le produit matricielle entre le vecteur normale et la matrice transformation
	vecteur4 intersectBox4;//vecteur permettant le produit matricielle entre le vecteur intersection et la matrice transformation
	
	
	//initialisation des variables
	T_tmp=0;
	T_tmp=*t;
	booleen =0;
	
	//opérations sur les transformations 
	//on creer des vecteurs de dimension 4 avec les coordonnees des vecteurs du rayon
	rayTransfoOrigine = vector4(ray.origine.x,ray.origine.y,ray.origine.z,1);
	rayTransfoDirecteur = vector4(ray.vectDir.x,ray.vectDir.y,ray.vectDir.z,0);
	//on le multiplie a la matrice pour le transformer
	rayTransfoOrigine = produitMatriceNonCarree(b.matriceTransfoInverse,rayTransfoOrigine,4);
	rayTransfoDirecteur = produitMatriceNonCarree(b.matriceTransfoInverse,rayTransfoDirecteur,4);
	//on initialise les coordonnees du rayon avec le nouveau rayon transformer
	ray.origine = vector(rayTransfoOrigine.x,rayTransfoOrigine.y,rayTransfoOrigine.z);
	ray.vectDir = vector(rayTransfoDirecteur.x,rayTransfoDirecteur.y,rayTransfoDirecteur.z);
	
	//cube unitaire
	cote=1;
	//initialisation des coordonnées de chaque coin du cube avec le côté
	a1 = vector(cote/2, cote/2, -cote/2);
	a2 = vector(cote/2, cote/2, cote/2);
	a3 = vector(cote/2 , -cote/2 , cote/2);
	a4 = vector(cote/2, -cote/2, -cote/2);
	a5 = vector(-cote/2 , -cote/2 , -cote/2);
	a6 = vector(-cote/2 , cote/2 , -cote/2);
	a7 = vector(-cote/2 , cote/2 , cote/2);
	a8 = vector(-cote/2 , -cote/2 , cote/2);
	//initialisation des autres variables
	distance=20000;
	booleen=0;
	distanceTmp=0;

	
	//initialisation de nouveaux triangles grace aux coins du cube
	triangle tgle1=newTriangle(a1,a2,a4);
	triangle tgle2=newTriangle(a6,a7,a5);
	triangle tgle3=newTriangle(a1,a2,a6);
	triangle tgle4=newTriangle(a2,a7,a3);
	triangle tgle5=newTriangle(a3,a8,a4);
	triangle tgle6=newTriangle(a4,a5,a1);
	triangle tgle7=newTriangle(a3,a4,a2);
	triangle tgle8=newTriangle(a8,a7,a5);
	triangle tgle9=newTriangle(a7,a2,a6);
	triangle tgle10=newTriangle(a8,a7,a3);
	triangle tgle11=newTriangle(a5,a8,a4);
	triangle tgle12=newTriangle(a6,a5,a1);
	
	
	/**
	 *On calcul pour chaque triangle composant le cube, si il y a intersection
	 *Puis on regarde quelle intersection et la plus proche 
	 */
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle1,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen=1; 
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale 
			(*normale) = vector(1,0,0);
		}
	}
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle2,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen=1; 
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale
			(*normale) = vector(-1,0,0);
		}
	}
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle3,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen=1; 
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale
			(*normale)=vector(0,1,0);
		}
	}
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle4,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen=1; 
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale
			(*normale)=vector(0,0,1);
		}
	}
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle5,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen = 1;
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale
			(*normale)=vector(0,-1,0);
		}
	}
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle6,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen=1; 
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale
			(*normale)=vector(0,0,-1);
		}
	}
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle7,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen=1; 
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale
			(*normale)=vector(1,0,0);
		}
	}
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle8,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen=1; 
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale
			(*normale)=vector(-1,0,0);
		}
	}
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle9,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen=1; 
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale
			(*normale)=vector(0,1,0);
		}
	}
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle10,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen=1; 
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale
			(*normale)=vector(0,0,1);
		}
	}
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle11,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen=1; 
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale
			(*normale)=vector(0,-1,0);
		}
	}
	//si il y a intersection avec ce triangle
	if(intersectTriangle(ray, tgle12,&T_tmp,intersection,0,normale)){
		//on calcule la distance entre l'origine et l'intersection
		distanceTmp=calculDistance(ray.origine, *intersection);
		//si la distance est plus courte
		if(distanceTmp<distance){
			//alors on change la valeur de distance
			distance=distanceTmp;
			//il y a intersection donc booleen est vrai
			booleen=1; 
			//on stocke la valeur du t
			*t = T_tmp;
			//on initialise la valeur de la normale
			(*normale)= vector(0,0,-1);
		}
	}
	
	//on change la valeur de l'intersection	et de la normale
	
	//on calcule l'intersection transformé
	intersectBox4 = opPlus4(rayTransfoOrigine, opProduitScalaire4(rayTransfoDirecteur, *t));
	intersectBox4 = produitMatriceNonCarree(b.matriceTransfo, intersectBox4,4);
	*intersection = vector(intersectBox4.x, intersectBox4.y, intersectBox4.z);
	//on calcul la normale transformé
	normalTransfo = vector4((*normale).x, (*normale).y, (*normale).z,0);
	normalTransfo = produitMatriceNonCarree(b.matriceTransfo, normalTransfo,4);
	*normale=vector(normalTransfo.x, normalTransfo.y, normalTransfo.z);
	*normale = normaliser(*normale);
		
	//on retourne la valeur du booleen
	return (booleen);

}
