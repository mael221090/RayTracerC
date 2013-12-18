/* \file rayon.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date 10/11/10
 * 
 * \brief Fonction qui permet de creer un rayon et de calculer son vecteur directeur
 *
 *
 */

//Inclusion des entetes de librairie
#include "rayon.h"

//fonction qui initialise les parametres d'un rayon
rayon creerRayon(vecteur origine, vecteur vectDir){
	rayon r;//déclaration du rayon
	r.origine = origine;//on initialise l'origine
	r.vectDir=vectDir;//on initialise le vecteur directeur
	//on retourne le rayon
	return (r);
}

//calcul du vecteur directeur du rayon 
vecteur calculvecDirRayon(int x, int  y, int xRes, int yRes, camera_new cam){
	float xIndent, yIndent;//le pas en x et y du pixel
        vecteur res;//le vecteur directeur du rayon
        
	//on calcul le pas en x et y du pixel
	xIndent = cam.viewplaneWidth / xRes;
	yIndent = cam.viewplaneHeight / yRes;
	//on calcul le vecteur directeur du rayon
	res = opMoins(opMoins(opPlus(cam.camPointHautGauche, opProduitScalaire(opProduitScalaire(cam.camVectDroit,xIndent),x)),opProduitScalaire(opProduitScalaire(cam.camVectHaut,yIndent),y)), cam.position);
	//on retourne la valeur du vecteur directeur
	return (res);
}

