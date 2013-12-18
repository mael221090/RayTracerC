/* \file rayon.h
*  \brief La structure rayon et déclaration de ses fonctions
*  \author Razavet Maël & Klelifa Sarah
*  \version 1.0
*  \date 10/11/10
*  
*
*/

#ifndef RAYON
#define RAYON


#include <math.h>
#include <stdio.h>
#include <string.h>
#include "camera.h"
#include "vecteur.h"

/**
 * \struct rayon
 * \brief composants d'un rayon
 *
 */
typedef struct{
	vecteur origine;/**< struct origine du rayon */ 
	vecteur vectDir;/**< struct vecteur directeur du rayon */ 
}rayon;

/**
 * \fn rayon creerRayon(vecteur origine, vecteur vectDir)
 * \brief fonction de création d'un rayon
 * 
 * \param origine : l'origine du rayon
 * \param vectDir : le vecteur directeur du rayon
 * \return le nouveau rayon creer
 */
rayon creerRayon(vecteur origine, vecteur vectDir);

/**
 * \fn vecteur calculvecDirRayon(int x, int  y, int xRes, int yRes, camera_new cam)
 * \brief fonction qui calcul le vecteur directeur du rayon
 * 
 * \param x : numero du pixel en largeur
 * \param y : numero du pixel en hauteur
 * \param xRes : resolution rentrer par l'utilisateur ou celle par défaut en largeur 
 * \param yRes : resolution rentrer par l'utilisateur ou celle par défaut en hauteur
 * \param cam : camera avec viewPlane intégré 
 * \return vecteur directeur du rayon
 */
vecteur calculvecDirRayon(int x, int  y, int xRes, int yRes, camera_new cam);

#endif
