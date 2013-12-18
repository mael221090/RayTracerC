/* \file camera.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date 10/11/10
 * 
 * \brief Fichiers qui permet de traiter la camera avec le viewplane
 *
 *
 */

//Inclusion des entetes de librairie
#include "camera.h"


//fonction qui creer le viewplane a l'aide des paramètres de la camera
camera_new creerCameraAvecViewplane(camera cam){
	camera_new cam_new;//on declare une nouvelle camera avec viewplane intégré
	//initialisation des composants dune camera
	cam_new.camDistViewplane=1;
	cam_new.viewplaneHeight=1;
	cam_new.viewplaneWidth=1;
	cam_new.camVectHaut=vector(0,1,0);
	cam_new.position=cam.location;
	cam_new.look_at=cam.look_at;
	//on retourne la nouvelle caméra
	return (cam_new);
}

//fonction qui calcul le point haut gauche du viewPlane
void calculPointHautGauche(camera_new* cam){
	// Nous calculons le vecteur directeur de la camera 
	(*cam).camVectDir = opMoins((*cam).look_at,(*cam).position);
	//on le normalise 
	(*cam).camVectDir=normaliser((*cam).camVectDir);              
	// on calcule le vecteur droit de la camera
	(*cam).camVectDroit=opProduitVectorielle((*cam).camVectHaut, (*cam).camVectDir);
	
	// on calcule le vecteur haut de la camera  
	(*cam).camVectHaut=opProduitVectorielle((*cam).camVectDir, (*cam).camVectDroit);

	// Maintenant nous avons toutes les informations pour détérminer la position du point en haut à gauche du viewplane.
	(*cam).camPointHautGauche = opPlus((*cam).position, opMoins((opPlus(opProduitScalaire((*cam).camVectDir, (*cam).camDistViewplane),(opProduitScalaire((*cam).camVectHaut, ((*cam).viewplaneHeight/2))))), (opProduitScalaire((*cam).camVectDroit, ((*cam).viewplaneWidth/2)))));
}

