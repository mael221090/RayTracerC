/* \file camera.h
*  \brief La structure caméra qui permet également de définir le viewplane
*  \author Razavet Maël & Klelifa Sarah
*  \version 1.0
*  \date 10/11/10
*  
* fichier contenant toutes les fonctions de définition du viewPlane 
* 
*/

#ifndef CAMERA
#define CAMERA

#include "LectureFichier.h"

/**
 * \struct camera_new
 * \brief structure contenant toute les informations sur la camera et le viewPlane
 *
 */
typedef struct{
	camera cam; /**< struct camera */
	vecteur camVectDir;/**< struct vecteur directeur de la caméra */ 
	vecteur camVectHaut; /**< struct haut de la caméra. Ces 2 premiers vecteurs permettent d'orienter la cam et de la fixer*/
	vecteur camVectDroit;/**< struct vecteur droit de la caméra*/
	vecteur camPointHautGauche;/**< struct point haut gauche de la caméra*/
	float camDistViewplane;/**< struct distance entre la caméra et le viewplane*/
	float viewplaneHeight;/**< struct hauteur du viewplane*/
	float viewplaneWidth;/**< struct largeur du viewplane*/
	vecteur position;/**< struct position de la caméra sous forme de vecteur*/
	vecteur look_at;/**< struct look at de la caméra sous forme de vecteur*/
}camera_new;

/**
 * \fn camera_new creerCameraAvecViewplane(camera cam)
 * \brief fonction de création de la camera
 * 
 * \param cam : camera du fichier.pov
 * \return la nouvelle camera avec le viewplane intégré
 */
camera_new creerCameraAvecViewplane(camera cam);

/**
 * \fn calculPointHautGauche(camera_new* cam)
 * \brief fonction qui calcul le point haut gauche du viewPlane
 * 
 * \param cam : nouvelle camera avec viewplane
 */
void calculPointHautGauche(camera_new* cam);

#endif
