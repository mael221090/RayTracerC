/* \file plan.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date 10/11/10
 * 
 * \brief Fonction permettant de calculer lintersection avec un plan
 *
 *
 */

//Inclusion des entetes de librairie
#include "plan.h"

//calcul le point dintersection avec un plan
int intersectPlan(rayon ray, plane* p, float* t, vecteur* intersectPlan, vecteur* normale){
	int booleen;//nouveau booleen
	vecteur4 rayTransfoOrigine;//declare un vecteur pour les transformations
	vecteur4 rayTransfoDirecteur;//declare un vecteur pour les transformations
	vecteur4 normalTransfo;	//vecteur permettant le produit matricielle entre le vecteur normale et la matrice transformation
	vecteur4 intersectPlan4;//vecteur permettant le produit matricielle entre le vecteur intersection et la matrice transformation
	
	//initialisation des variables
	booleen =0;
	
	//opérations sur les transformations 

	//on creer des vecteurs de dimension 4 avec les coordonnees des vecteurs du rayon
	rayTransfoOrigine = vector4(ray.origine.x,ray.origine.y,ray.origine.z,1);
	rayTransfoDirecteur = vector4(ray.vectDir.x,ray.vectDir.y,ray.vectDir.z,0);
	//on le multiplie a la matrice pour le transformer
	rayTransfoOrigine = produitMatriceNonCarree((*p).matriceTransfoInverse,rayTransfoOrigine,4);
	rayTransfoDirecteur = produitMatriceNonCarree((*p).matriceTransfoInverse,rayTransfoDirecteur,4);
	//on initialise les coordonnees du rayon avec le nouveau rayon transformer
	ray.origine = vector(rayTransfoOrigine.x,rayTransfoOrigine.y,rayTransfoOrigine.z);
	ray.vectDir = vector(rayTransfoDirecteur.x,rayTransfoDirecteur.y,rayTransfoDirecteur.z);
		
	//si la coordonnee x du vecteur directeur du rayon = 0
	if(ray.vectDir.x == 0){
		//il n'y a pas d'intersection
		booleen=0;
	}
	//sinon 
	else{
		//on calcule le t
		*t=-(ray.origine.x/ray.vectDir.x);
		//si il est >0
		if(*t>0.000000000000000000001){
			//il y a intersection
			booleen=1;
		}
		//sinon il n y a pas d'intersection
		else{
			booleen=0;	
		}
	}
	
	//on change la valeur de l'intersection	et de la normale
	
	//on calcule l'intersection transformé
	intersectPlan4 = opPlus4(rayTransfoOrigine, opProduitScalaire4(rayTransfoDirecteur, *t));
	intersectPlan4 = produitMatriceNonCarree((*p).matriceTransfo, intersectPlan4,4);
	*intersectPlan = vector(intersectPlan4.x, intersectPlan4.y, intersectPlan4.z);
	//on calcul la normale transformé
	(*normale) = (*p).location;
	normalTransfo = vector4((*normale).x, (*normale).y, (*normale).z,0);
	normalTransfo = produitMatriceNonCarree((*p).matriceTransfo, normalTransfo,4);
	*normale =vector(normalTransfo.x, normalTransfo.y, normalTransfo.z);
	*normale = normaliser(*normale);
	
	//on retourne le booleen
	return (booleen);
}

