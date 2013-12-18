/* \file lumiere.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date 20/11/12
 * 
 * \brief Fonction de générer la lumiere 
 *
 *
 */

//Inclusion des entetes de librairie
#include "lumiere.h"

//fonction qui calcul la couleur d'un pixel
vecteur lumierePixel(vecteur normal, vecteur intersection, vecteur mat,light_source lumiere, vecteur pigment){
	vecteur vecteurLumiere;//déclaration du vecteur lumiere
	float angle;//declation de l'angle entre le vecteur lumiere et la normal
	/**
	 * pour la lumiere spéculaire qui n'est pas traité
	 **
	vecteur reflection;// declaration du vecteur reflechie
	float angleReflectionIntersection;//declaration de l'angle entre le vecteur reflechi et l'intersection
	vecteur resultSpec;//lumiere speculaire*/
	
	//on calcul le vecteur lumiere et on le normalise
	vecteurLumiere = opMoins(intersection,lumiere.location);
	vecteurLumiere = normaliser(vecteurLumiere);
	
	//calcul lumiere ambiante 
	vecteur couleurAmbiante;
	couleurAmbiante = opProduit(mat, opProduitScalaire(lumiere.color_rgb,0.1));
	
	//calcul lumiere diffuse
	//on calcul l'angle entre le vecteur lumiere et la normal a l'objet
	angle = -dot(vecteurLumiere,normal);
	
	//si l'angle est inférieur ou égale a zéro l'intersection a une orientation tel que le pigment est noirci
	if(angle <= 0){
		pigment = vector(0,0,0);
	}else{//sinon on calcul la couleur du pixel selon l'angle incident,la couleur de la lumiere et la couleur de l'objet 
		vecteur result;
		result = opProduitScalaire(lumiere.color_rgb,angle);
		pigment =  opProduit(mat,result);
	}
	
	
	/* lumiere speculaire qui ne fonctionne pas correctement erreur de stack over flow
	reflection = opMoins(opProduitScalaire(normal, 2*angle), vecteurLumiere);
	angleReflectionIntersection = dot(reflection, intersection);
	if(angleReflectionIntersection <= 0){
		resultSpec = vector(0,0,0);
	}else{
	//brillance de la sphere
		angleReflectionIntersection = pow(angleReflectionIntersection, 300);
		
		if(angleReflectionIntersection*255 >= MAXFLOAT) {
			angleReflectionIntersection = MAXFLOAT;
	 	}
		
		resultSpec = opProduitScalaire(lumiere.color_rgb,angleReflectionIntersection);
		resultSpec = opProduit(resultSpec, mat);
		pigment = opPlus(pigment, resultSpec);
	}
	*/
	
	//on somme la lumiere diffuse et la lumiere ambiante
	pigment = opPlus(pigment, couleurAmbiante);

	return pigment;
}
