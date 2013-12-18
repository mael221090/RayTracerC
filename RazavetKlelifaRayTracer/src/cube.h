/* \file cube.h
*  \author Razavet Maël & Klelifa Sarah
*  \version 0.1
*  \date 11/12/10
*  
*  \brief La structure cube 
* 
*/
#ifndef CUBE
#define CUBE
#include "LectureFichier.h"
#include "rayon.h"
#include "vecteur.h"
#include "triangle.h"


/**
 * \fn int intersectCube(rayon ray, box b, float* t, vecteur* intersection, vecteur* normale)
 * \brief fonction d'intersection entre le cube et rayon
 * 
 * \param ray : le rayon lancer
 * \param b : le cube courant
 * \param t : distance entre le cube et le sol  
 * \param intersection : point d'intersection entre le cube et le rayon
 * \param normale : la normale au cube
 * \return booleen indiquant si il y a eu intersection 
 */
int intersectCube(rayon ray, box b, float* t, vecteur* intersection, vecteur* normale);

#endif
