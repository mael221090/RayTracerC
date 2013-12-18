/* \file vecteur.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date 10/11/10
 * 
 * \brief Fonction qui permet d'effectuer des opérations sur les vecteurs
 *
 *
 */

//Inclusion des entetes de librairie
#include "vecteur.h"

//creation d'un nouveau vecteur de taille 3
vecteur vector(float a, float b, float c){
	vecteur v;//declaration du vecteur
	v.x=a;
	v.y=b;
	v.z=c;
	return (v);
}

//creation d'un nouveau vecteur de taille 4
vecteur4 vector4(float a, float b, float c, float d){
	vecteur4 v;//declaration du vecteur
	v.x=a;
	v.y=b;
	v.z=c;
	v.w=d;
	return (v);
}

//fonction qui normalise un vecteur
vecteur normaliser(vecteur v){
	//déclaration de variables
	static vecteur res;//vecteur résultat
	float norme;//la norme du vecteur en entrée
	//initialisation des variables avant utilisation
	norme=0;
	res.x=0;
	res.y=0;
	res.z=0;
	//on calcule la longueur du vecteur
	norme=sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
	//on normalise
	if(norme==0){
		norme=1; //car la division par zéro est impossible
	}
	res=opDivise(v,norme);	
	return (res);
}

//fonction qui soustraie deux vecteur de taille 3
vecteur opMoins(vecteur tmp1, vecteur tmp2){
	vecteur resultat;//est le résultat de  tmp1-tmp2
	resultat.x=tmp1.x-tmp2.x;
	resultat.y=tmp1.y-tmp2.y;
	resultat.z=tmp1.z-tmp2.z;
	return (resultat);
}

//produit vectorielle entre deux vecteur de taille 3
vecteur opProduitVectorielle(vecteur tmp1, vecteur tmp2){
	vecteur resultat;//est le résultat de tmp1*tmp2
	resultat.x=tmp1.y*tmp2.z-tmp1.z*tmp2.y;
	resultat.y=tmp1.z*tmp2.x-tmp1.x*tmp2.z;
	resultat.z=tmp1.x*tmp2.y-tmp1.y*tmp2.x;
	return(resultat);
}

//produit de deux vecteur de taille 3
vecteur opProduit(vecteur tmp1, vecteur tmp2){
	vecteur resultat;//est le résultat de tmp1*tmp2
	resultat.x=tmp1.x*tmp2.x;
	resultat.y=tmp1.y*tmp2.y;
	resultat.z=tmp1.z*tmp2.z;
	return (resultat);
}

//fonction qui permet de diviser deux vecteurs entre eux
vecteur diviseVecteur(vecteur tmp1, vecteur tmp2){
	vecteur resultat;//est le résultat de tmp1/tmp2
	resultat.x=tmp1.x/tmp2.x;
	resultat.y=tmp1.y/tmp2.y;
	resultat.z=tmp1.z/tmp2.z;
	return (resultat);
}

//addition de deux vecteur de taille 3
vecteur opPlus(vecteur tmp1, vecteur tmp2){
	vecteur resultat;//est le résultat de tmp1+tmp2
	resultat.x=tmp1.x+tmp2.x;
	resultat.y=tmp1.y+tmp2.y;
	resultat.z=tmp1.z+tmp2.z;
	return (resultat);
}

//addition de deux vecteurs de taille 4
vecteur4 opPlus4(vecteur4 tmp1, vecteur4 tmp2){
	vecteur4 resultat;//est le résultat de tmp1+tmp2
	resultat.x=tmp1.x+tmp2.x;
	resultat.y=tmp1.y+tmp2.y;
	resultat.z=tmp1.z+tmp2.z;
	resultat.w=tmp1.w+tmp2.w;
	return (resultat);
}

//addition d'un vecteur de taille 3 avec un scalaire
vecteur opPlusVecteurScalaire(vecteur tmp1, float k){
	vecteur resultat;//est le résultat de tmp1 + k
	resultat.x=tmp1.x + k;
	resultat.y=tmp1.y + k;
	resultat.z=tmp1.z + k;
	return (resultat);

}

//division entre deux vecteurs de taille 3
vecteur opDivise(vecteur tmp1, float k){
	vecteur resultat;//est le résultat de tmp1/k
	resultat.x=tmp1.x/k;
	resultat.y=tmp1.y/k;
	resultat.z=tmp1.z/k;
	return (resultat);
}

//produit d'un vecteur de taille 3 avec un scalaire
vecteur opProduitScalaire(vecteur tmp, float k){
	vecteur resultat;//est le résultat de tmp*k

	resultat.x=tmp.x*k;
	resultat.y=tmp.y*k;
	resultat.z=tmp.z*k;
		
	return (resultat);
}

//produit d'un vecteur de taille 4 avec un scalaire
vecteur4 opProduitScalaire4(vecteur4 tmp, float k){
	vecteur4 resultat;//est le résultat de tmp*k

	resultat.x=tmp.x*k;
	resultat.y=tmp.y*k;
	resultat.z=tmp.z*k;
	resultat.w=tmp.w*k;
		
	return (resultat);
}

//calcule de la distance entre deux vecteurs de taille 3
float calculDistance(vecteur A, vecteur B){
	vecteur result;
	result = opMoins(B,A);
	
	return (sqrt(dot(result,result)));
}

//calcul la distance entre deux points
float calculDistancePoint(vecteur A, vecteur B){
	return (sqrt(pow(A.x-B.x, 2) +pow(A.y-B.y, 2)+pow(A.z-B.z, 2)));
}

//compare deux vecteurs entre eux 
int compareVecteur(vecteur A, vecteur B){
	int bol;
	float distanceAxBx;
	float distanceAyBy;
	float distanceAzBz;
	//on calcul la distance entre chaque composante pour nous laisser une marge d'erreur
	distanceAxBx = fabs(A.x-B.x);
	distanceAyBy = fabs(A.y-B.y);
	distanceAzBz = fabs(A.z-B.z);
	
	bol = ((distanceAxBx <= 0.001)&&(distanceAxBx >= -0.001) && (distanceAyBy <= 0.001)&&(distanceAyBy >= -0.001) && (distanceAzBz <= 0.001)&&(distanceAzBz >= -0.001));

	return bol;
}

//calcule du produit scalaire entre deux vecteurs
float dot(vecteur A, vecteur B){
	return (A.x*B.x + A.y*B.y + A.z*B.z);
}
