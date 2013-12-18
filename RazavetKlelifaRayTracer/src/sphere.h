/* \file sphere.h
*  \author Razavet Maël & Klelifa Sarah
*  \version 0.1
*  \date 10/11/10
*  
*  \brief La structure sphere et déclaration des fonctions
*/

#ifndef SPHERE
#define SPHERE

#include  <math.h>
#include  "LectureFichier.h"
#include "rayon.h"

/**
 * \fn int intersectionSphere(rayon ray, sphere s, float* t, vecteur* intersectSphere,vecteur* normale)
 * \brief fonction d'intersection entre la sphere et rayon
 * 
 * \param ray : le rayon lancer
 * \param s : la sphere courante
 * \param t : distance entre sphere et origine du rayon 
 * \param intersectSphere : point d'intersection entre la sphere et le rayon
 * \param normale: la normale au point d'intersection
 * \return booleen indiquant si il y a eu intersection 
 */
int intersectionSphere(rayon ray, sphere s, float* t,vecteur* intersectSphere,vecteur* normale);

#endif

