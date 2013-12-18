/* \file sphere.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date 10/11/10
 * 
 * \brief Fonction permettant de calculer lintersection avec une sphere
 *
 *
 */

//Inclusion des entetes de librairie
#include "sphere.h"

//fonction qui calcul l'intersection entre le rayon et une sphère
int intersectionSphere(rayon ray, sphere s, float* t,vecteur* intersectSphere,vecteur* normale){
	//declaration et initialisation des variables
	float a;//coefficient dune equation de degree 2 
	float b;//coefficient dune equation de degree 2 
	float c;//coefficient dune equation de degree 2 
	float delta;//le delta de lequation
	float t1;//racine de lequation
	float t2;//racine de lequation
	int booleen;//nouveau booleen
	vecteur intersection;//vecteur permettant de calculer la normale unitaire
	vecteur4 rayTransfoOrigine;//declare un vecteur pour les transformations
	vecteur4 rayTransfoDirecteur;//declare un vecteur pour les transformations
	vecteur4 normalTransfo;	//vecteur permettant le produit matricielle entre le vecteur normale et la matrice transformation
	vecteur4 intersectSphere4;//vecteur permettant le produit matricielle entre le vecteur intersection et la matrice transformation
		
	//initialisation des variables
	booleen =0;
	
	//opérations sur les transformations 
	//on creer des vecteurs de dimension 4 avec les coordonnees des vecteurs du rayon
	rayTransfoOrigine = vector4(ray.origine.x,ray.origine.y,ray.origine.z,1);
	rayTransfoDirecteur = vector4(ray.vectDir.x,ray.vectDir.y,ray.vectDir.z,0);
	//on le multiplie a la matrice pour le transformer
	rayTransfoOrigine = produitMatriceNonCarree(s.matriceTransfoInverse,rayTransfoOrigine,4);
	rayTransfoDirecteur = produitMatriceNonCarree(s.matriceTransfoInverse,rayTransfoDirecteur,4);
	//on initialise les coordonnees du rayon avec le nouveau rayon transformer
	ray.origine = vector(rayTransfoOrigine.x,rayTransfoOrigine.y,rayTransfoOrigine.z);
	ray.vectDir = vector(rayTransfoDirecteur.x,rayTransfoDirecteur.y,rayTransfoDirecteur.z);
	
	//initialisation des coefficients dune equation du second degree
	a=ray.vectDir.x*ray.vectDir.x+ray.vectDir.y*ray.vectDir.y+ray.vectDir.z*ray.vectDir.z;
	b=2*(ray.vectDir.x*ray.origine.x+ray.vectDir.y*ray.origine.y+ray.vectDir.z*ray.origine.z);
	//car sphere unitaire
	c=ray.origine.x*ray.origine.x+ray.origine.y*ray.origine.y+ray.origine.z*ray.origine.z - s.rayon*s.rayon;
	//calcul du delta
	delta=b*b-4*a*c;
	//initialisation des racines 
	t1=0;
	t2=0;
	//initialisation du booleen
	booleen=0;
	//il n'y a pas dintersection si le delta<0
	if(delta<0){
		booleen=0;//pas d'intersectionvecteur* normale){
	}
	//si le delta=0
	else if(delta==0){
		//il y a intersection
		booleen=1;
		//calcul du t
		*t=((-b)/(2*a));
	}
	//si le delta>0
	else{
		//il y a intersection
		booleen=1;
		//calcul des racines
		t1=(-b+sqrt(delta))/(2*a);
		t2=(-b-sqrt(delta))/(2*a);
		//on prend la plus petite des racines
		if(t1<t2){
			*t=t1;
		}
		else{
			*t=t2;
		}
	}
	//on calcul l'intersection unitaire
	intersection = opPlus(ray.origine, opProduitScalaire(ray.vectDir, *t));
	//on initialise le vecteur normale a la sphere
	(*normale) = vector(intersection.x,intersection.y, intersection.z);
	
	//on change la valeur de l'intersection	et de la normale
	
	//on calcul l'intersection transformé
	intersectSphere4 = opPlus4(rayTransfoOrigine, opProduitScalaire4(rayTransfoDirecteur, *t));
	intersectSphere4 = produitMatriceNonCarree(s.matriceTransfo, intersectSphere4,4);
	*intersectSphere = vector(intersectSphere4.x, intersectSphere4.y, intersectSphere4.z);
	//on calcul la normale transformé
	normalTransfo = vector4((*normale).x, (*normale).y, (*normale).z,0);
	normalTransfo = produitMatriceNonCarree(s.matriceTransfo, normalTransfo,4);
	(*normale)=vector(normalTransfo.x, normalTransfo.y, normalTransfo.z);
	*normale = normaliser(*normale);
	
	//on retourne le booleen
	return (booleen);
}
