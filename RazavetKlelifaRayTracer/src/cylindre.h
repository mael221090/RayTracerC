/* \file cylindre.h
*  \author Razavet Maël & Klelifa Sarah
*  \version 0.1
*  \date 11/12/10
*  
*  \brief La structure cylindre 
*
*/

#ifndef CYLINDRE
#define CYLINDRE
#include "LectureFichier.h"
#include "rayon.h"
#include "vecteur.h"
#include "plan.h"
#include <math.h>

/** \fn int intersectCylindre(rayon ray, cylinder cylindre, float* t, vecteur* intersection, vecteur* normale)
 *  \brief  calcul de l'intersection entre un cylindre et le rayon
 *
 * \param ray :le rayon lancer
 * \param cylindre : le cylindre courant
 * \param t : le paramètre du rayon calculé
 * \param intersection : l'intersection entre le cylindre et le rayon
 * \param normale : la normale au cylindre
 * \return booleen indiquant si il y a eu intersection 
 */
int intersectCylindre(rayon ray, cylinder cylindre, float* t, vecteur* intersection, vecteur* normale);

#endif
