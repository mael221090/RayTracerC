/* \file 
*  \author Razavet Maël & Klelifa Sarah
*  \version 0.1
*  \date 11/12/10
*  
*  \brief fichier gérant l'intersection d'un tore et du rayon
*/
#ifndef TORE
#define TORE
#include "LectureFichier.h"
#include "rayon.h"
#include "vecteur.h"

/**
 * \fn int intersectTore(rayon ray, torus tore, float* t, vecteur* intersection, vecteur* normale)
 * \brief fonction qui calcule le point dintersection et la normale au tore
 * 
 * \param ray : le rayon lancer
 * \param tore : le tore courant
 * \param t : distance entre tore et origine du rayon
 * \param intersection : point d'intersection entre le tore et le rayon
 * \param normale : normale au tore
 * \return booleen indiquant si il y a eu intersection 
 */
int intersectTore(rayon ray, torus tore, float* t, vecteur* intersection, vecteur* normale);

#endif
