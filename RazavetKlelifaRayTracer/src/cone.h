/* \file cone.h
*  \brief La structure cone
*  \author Razavet Maël & Klelifa Sarah
*  \version 1.0
*  \date 11/12/10
*  
*/

#ifndef CONE
#define CONE
#include "LectureFichier.h"
#include "rayon.h"
#include "vecteur.h"

/** \fn double int intersectCone(rayon ray, cone con, float* t, vecteur* intersection)
 *  \brief  calcul de l'intersection entre un cone et le rayon
 *
 * \param ray :le rayon lancer
 * \param con: le cone courant
 * \param t : le paramètre du rayon calculé
 * \param intersection : l'intersection entre le cone et le rayon
 * \return booleen indiquant si il y a eu intersection 
 */
int intersectCone(rayon ray, cone con, float* t, vecteur* intersection);

#endif
