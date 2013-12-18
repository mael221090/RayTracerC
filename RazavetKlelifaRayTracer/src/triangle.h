/* \file triangle.h
*  \author Razavet Maël & Klelifa Sarah
*  \version 0.1
*  \date 9/12/10
*  
*  \brief La structure triangle qui permet de calculer des intersections avec des triangles
*/

#ifndef TRIANGLE
#define TRIANGLE
#include "LectureFichier.h"
#include  <math.h>
#include "rayon.h"
#include "vecteur.h"

/**
 * \fn int intersectTriangle(rayon ray, triangle tgle, float* t, vecteur* intersection, int triangle, vecteur* normale)
 * \brief fonction qui calcule le point dintersection entre le triangle et le rayon
 * 
 * \param ray : le rayon lancer
 * \param tgle : le triangle courant
 * \param t : distance entre triangle et origine du rayon
 * \param intersection : point d'intersection entre le tore et le rayon
 * \param triangle : booleen indiquant si on calcul l'intersection d'un triangle ou d'un cube
 * \param normale : la normale au cylindre
 * \return booleen indiquant si il y a eu intersection 
 */
int intersectTriangle(rayon ray, triangle tgle, float* t, vecteur* intersection, int triangle, vecteur* normale);

/**
 * \fn triangle newTriangle(vecteur coin1, vecteur coin2, vecteur coin3);
 * \brief fonction qui creer un nouveau triangle
 * 
 * \param coin1 :  coordonnee du premier point du triangle
 * \param coin2 : coordonnee du deuxieme point du triangle
 * \param coin3 : coordonnee du troisieme point du triangle
 * \return le nouveau triangle creer
 */
triangle newTriangle(vecteur coin1, vecteur coin2, vecteur coin3);

#endif
