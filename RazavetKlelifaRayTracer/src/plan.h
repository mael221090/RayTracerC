/* \file plan.h
*  \brief fonction d'intersection entre plan et rayon
*  \author Razavet Maël & Klelifa Sarah
*  \version 0.1
*  \date 10/11/10
*  
*/

#ifndef PLAN
#define PLAN
#include "LectureFichier.h"
#include  <math.h>
#include "rayon.h"

/**
 * \fn int intersectPlan(rayon ray, plane* p, float* t, vecteur* intersectPlan, vecteur* normale)
 * \brief fonction d'intersection entre plan et rayon
 * 
 * \param ray : le rayon lancer
 * \param p : le plan courant
 * \param t : 
 * \param intersectPlan : point d'intersection entre le plan et le rayon
 * \param normale : la normale au cylindre
 * \return booleen indiquant si il y a eu intersection 
 */
int intersectPlan(rayon ray, plane* p, float* t, vecteur* intersectPlan, vecteur* normale);

#endif
