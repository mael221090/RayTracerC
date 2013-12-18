/* \file triangle.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date 9/12/10
 * 
 * \brief Fonction qui permet de calculer lintersection avec un triangle
 *
 *
 */

//Inclusion des entetes de librairie
#include "triangle.h"

//calcul l'intersection avec un triangle
int intersectTriangle(rayon ray, triangle tgle, float* t, vecteur* intersection, int triangle, vecteur* normale){
	//Déclaration de variables
	float D;//un coefficient de lequation
	float u;//un coefficient de lequation
	float v;//un coefficient de lequation
	vecteur coin2MoinsCoin1;//vecteur distance entre coin2 et coin1
	vecteur coin3MoinsCoin1;//vecteur distance entre coin3 et coin1
	float x1;//coin2-coin1 en x
	float y1;//coin2-coin1 en y
	float z1;//coin2-coin1 en z
	float x2;//coin3-coin1 en x
	float y2;//coin3-coin1 en y
	float z2;//coin3-coin1 en z
	float x3;//ray.vectDir en x
	float y3;//ray.vectDir en y
	float z3;//ray.vectDir en z
	float x4;//ray.origine en x
	float y4;//ray.origine en y
	float z4;//ray.origine en z
	float booleen;//un booleen pour savoir si il y a intersection ou non
	vecteur4 rayTransfoOrigine;//declare un vecteur pour les transformations
	vecteur4 rayTransfoDirecteur;//declare un vecteur pour les transformations
	vecteur4 normalTransfo;	//vecteur permettant le produit matricielle entre le vecteur normale et la matrice transformation
	vecteur4 intersectTriangle4;//vecteur permettant le produit matricielle entre le vecteur intersection et la matrice transformation
	
	//initialisation des variables
	booleen =0;
	//on initialise les vecteur du triangle
	D=0.0f;
	u=0.0f;
	v=0.0f;
	
	//on transforme le rayon
	if(triangle){//on test si c'est un triangle car, le carree ce sert aussi de l'intersection d'un triangle cependant les transformations du carree s'applique dans intersectCube
			//on creer des vecteurs de dimension 4 avec les coordonnees des vecteurs du rayon
			rayTransfoOrigine = vector4(ray.origine.x,ray.origine.y,ray.origine.z,1);
			rayTransfoDirecteur = vector4(ray.vectDir.x,ray.vectDir.y,ray.vectDir.z,0);
			//on le multiplie a la matrice pour le transformer
			rayTransfoOrigine = produitMatriceNonCarree(tgle.matriceTransfoInverse,rayTransfoOrigine,4);
			rayTransfoDirecteur = produitMatriceNonCarree(tgle.matriceTransfoInverse,rayTransfoDirecteur,4);
			//on initialise les coordonnees du rayon avec le nouveau rayon transformer
			ray.origine = vector(rayTransfoOrigine.x,rayTransfoOrigine.y,rayTransfoOrigine.z);
			ray.vectDir = vector(rayTransfoDirecteur.x,rayTransfoDirecteur.y,rayTransfoDirecteur.z);
	}
	//Initialisation de variables
	coin2MoinsCoin1=vector(tgle.coin2.x-tgle.coin1.x,tgle.coin2.y-tgle.coin1.y,tgle.coin2.z-tgle.coin1.z);
	coin3MoinsCoin1=vector(tgle.coin3.x-tgle.coin1.x,tgle.coin3.y-tgle.coin1.y,tgle.coin3.z-tgle.coin1.z);
	x1=coin2MoinsCoin1.x;
	y1=coin2MoinsCoin1.y;
	z1=coin2MoinsCoin1.z;
	x2=coin3MoinsCoin1.x;
	y2=coin3MoinsCoin1.y;
	z2=coin3MoinsCoin1.z;
	x3=ray.vectDir.x;
	y3=ray.vectDir.y;
	z3=ray.vectDir.z;
	x4=ray.origine.x;
	y4=ray.origine.y;
	z4=ray.origine.z;
	
	//initialisation des coefficients de l'équation
	D=-z1*y3*x2+y1*z3*x2+x3*z1*y2+y3*x1*z2-z3*x1*y2-x3*y1*z2;
	u = -(-y3*x2*tgle.coin1.z-y3*x4*z2+y3*x2*z4+y3*tgle.coin1.x*z2+x3*y2*tgle.coin1.z-x3*y2*z4+x2*z3*tgle.coin1.y-x2*z3*y4+x4*z3*y2+x3*y4*z2-x3*tgle.coin1.y*z2-tgle.coin1.x*z3*y2)/D;
	v=(-x3*z1*tgle.coin1.y-x3*y1*z4+x3*z1*y4+x3*y1*tgle.coin1.z+z3*x1*tgle.coin1.y+y1*z3*x4+z1*y3*tgle.coin1.x-z3*x1*y4-y3*x1*tgle.coin1.z-y1*z3*tgle.coin1.x+y3*x1*z4-z1*y3*x4)/D;
	//calcule du t grace aux coefficients et vecteur définis avant
	*t = (-x4*z1*y2+x4*y1*z2+tgle.coin1.x*z1*y2-tgle.coin1.x*y1*z2-x1*y2*tgle.coin1.z+x1*y2*z4-x1*y4*z2+x1*tgle.coin1.y*z2-x2*z1*tgle.coin1.y-x2*y1*z4+x2*z1*y4+x2*y1*tgle.coin1.z)/D;
	//on initialise le booleen a faux
	booleen=0;
	
	//pour quil y ait intersection il faut que:
	if(D!=0 && u>=0 && v>=0 && u+v<=1){
		//le booleen est donc vrai
		booleen=1;
		//si c'est un triangle (effectivement nous utilisons cette intersection pour le cube également)
		if(triangle){
			//calcul de la normal du triangle
			*normale = opProduitVectorielle(opMoins(tgle.coin3, tgle.coin1),opMoins(tgle.coin2, tgle.coin1));	
			//si il y a une transformation sur le triangle
			
			//on calule l'intersection transformée
			intersectTriangle4 = opPlus4(rayTransfoOrigine, opProduitScalaire4(rayTransfoDirecteur, *t));
			intersectTriangle4 = produitMatriceNonCarree(tgle.matriceTransfo, intersectTriangle4,4);
			//on calcule l'intersection finale
			*intersection = vector(intersectTriangle4.x, intersectTriangle4.y, intersectTriangle4.z);
			//on calcul la normale transformé
			normalTransfo = vector4((*normale).x, (*normale).y, (*normale).z,0);
			normalTransfo = produitMatriceNonCarree(tgle.matriceTransfo, normalTransfo,4);
			//on calcule la normale finale
			*normale=vector(normalTransfo.x, normalTransfo.y, normalTransfo.z);
			//on normalise la normale
			*normale = normaliser(*normale);
		}
		//si ce n'est pas un triangle (si c'est un cube par exemple)
		else{
			//on calcule l'intersection
			*intersection=opPlus(ray.origine, opProduitScalaire(ray.vectDir, *t));
		}
	}
	
	//on retourne le booleen
	return (booleen);
}


//création dun nouveau triangle
triangle newTriangle(vecteur coin1, vecteur coin2, vecteur coin3){
	triangle tgle;//nouveau triangle
	//initialisation des composantes d'un triangle
	tgle.coin1=coin1;
	tgle.coin2=coin2;
	tgle.coin3=coin3;
	//on retourne le triangle
	return (tgle);
}
