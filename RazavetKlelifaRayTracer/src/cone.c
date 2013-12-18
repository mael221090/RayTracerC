/* \file cone.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date11/12/10
 * 
 * \brief Fonction qui permet de calculer lintersection avec un cone
 *
 *
 */

//Inclusion des entetes de librairie
#include "cone.h"

//calcule l'intersection entre un rayon et un cone
int intersectCone(rayon ray, cone con, float* t, vecteur* intersection){
	//declaration de variables
	float a;//coefficient dune equation de degree 2 
	float b;//coefficient dune equation de degree 2 
	float c;//coefficient dune equation de degree 2 
	float delta;//le delta de lequation de degree2
	float t1;//racine de lequation
	float t2;//racine de lequation
	int booleen;//booleen pour savoir si il y a intersection ou pas
	vecteur4 rayTransfoOrigine;//vecteurs permettant le produit matricielle avec la matrice Transformation
	vecteur4 rayTransfoDirecteur;
	vecteur4 intersectBox4;//vecteurs permettant le produit matricielle entre le vecteur intersection et la matrice transformation
		
	//initialisation des variables
	booleen =0;
	
	//opérations sur les transformations 
	//on creer des vecteurs de dimension 4 avec les coordonnees des vecteurs du rayon
	rayTransfoOrigine = vector4(ray.origine.x,ray.origine.y,ray.origine.z,1);
	rayTransfoDirecteur = vector4(ray.vectDir.x,ray.vectDir.y,ray.vectDir.z,0);
	//on le multiplie a la matrice pour le transformer
	rayTransfoOrigine = produitMatriceNonCarree(con.matriceTransfoInverse,rayTransfoOrigine,4);
	rayTransfoDirecteur = produitMatriceNonCarree(con.matriceTransfoInverse,rayTransfoDirecteur,4);
	//on initialise les coordonnees du rayon avec le nouveau rayon transformer
	ray.origine = vector(rayTransfoOrigine.x,rayTransfoOrigine.y,rayTransfoOrigine.z);
	ray.vectDir = vector(rayTransfoDirecteur.x,rayTransfoDirecteur.y,rayTransfoDirecteur.z);
	
	//initialisation des vairables
	a=ray.vectDir.y*ray.vectDir.y+ray.vectDir.z*ray.vectDir.z-ray.vectDir.x*ray.vectDir.x;
	b=2*(ray.origine.y*ray.vectDir.y+ray.origine.z*ray.vectDir.z-ray.origine.x*ray.vectDir.x);
	c=ray.origine.y*ray.origine.y+ray.origine.z*ray.origine.z-ray.origine.x*ray.origine.x;
	//calcul du discriminant
	delta=b*b-4*a*c;
	//si le delta est négatif	
	if(delta<0){
		booleen=0;//pas d'intersection
	}
	//sinon c'est quil y a des intersections
	else{
		//calcul des deux racines
		t1=(-b+sqrt(delta))/(2*a);
		t2=(-b-sqrt(delta))/(2*a);
		//on garde la plus petite des racines
		if(t1<t2){
			*t=t1;
		}else{
			*t=t2;
		}
		//on calcule le point dintersection en fonction du t
		*intersection=opPlus(ray.origine, opProduitScalaire(ray.vectDir, *t));
		//si l'intersection est compris entre 0 et 1 alors elle se trouve dans le cone quil soit fini ou non
		if((*intersection).x>=0 && (*intersection).x<=1){
			booleen=1;
		}
	}
	
	//on change la valeur de l'intersection 
	intersectBox4 = opPlus4(rayTransfoOrigine, opProduitScalaire4(rayTransfoDirecteur, *t));//on calcul l'intersection en vecteur de taille 4
	intersectBox4 = produitMatriceNonCarree(con.matriceTransfo, intersectBox4,4);//on fait le produit entre ce vecteur et la matrice transformation
	*intersection = vector(intersectBox4.x, intersectBox4.y, intersectBox4.z);//puis on initialise les composantes du vecteur de taille 3 de l'intersection avec le resultat du produit
	
	//on retourne le booleen
	return (booleen);
}
