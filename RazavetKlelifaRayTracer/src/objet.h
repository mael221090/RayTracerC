/* \file objet.h
 *  \brief fichier gérant la comparaison entre les objets
 *  \author Razavet Maël & Klelifa Sarah
 *  \version 0.1
 *  \date 10/11/10
 *  
 */
//Inclusion des entêtes de librairie

#ifndef OBJET
#define OBJET
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "LectureFichier.h"

/**
 * \fn int compareCube(box cube1, box cube2)
 * \brief fonction permettant de comparer deux cubes
 * 
 * \param cube1 : le premier cube à comparer 
 * \param cube2 : le deuxième cube à comparer
 * \return 1 si ce sont les même, 0 sinon
 */
int compareCube(box cube1, box cube2);

/**
 * \fn int compareSphere(sphere sphere1, sphere sphere2)
 * \brief fonction permettant de comparer deux sphères
 * 
 * \param sphere1 : le premier sphere à comparer 
 * \param sphere2 : le deuxième sphere à comparer
 * \return 1 si ce sont les même, 0 sinon
 */
int compareSphere(sphere sphere1, sphere sphere2);

/**
 * \fn int compareTriangle(triangle triangle1, triangle triangle2)
 * \brief fonction permettant de comparer deux triangles
 * 
 * \param triangle1 : le premier triangle à comparer 
 * \param triangle2 : le deuxième triangle à comparer
 * \return 1 si ce sont les même, 0 sinon
 */
int compareTriangle(triangle triangle1, triangle triangle2);

/**
 * \fn int comparePlan(plane plan1, plane plan2)
 * \brief fonction permettant de comparer deux plans
 * 
 * \param plan1 : le premier plan à comparer 
 * \param plan2 : le deuxième plan à comparer
 * \return 1 si ce sont les même, 0 sinon
 */
int comparePlan(plane plan1, plane plan2);

/**
 * \fn int compareCone(cone cone1, cone cone2)
 * \brief fonction permettant de comparer deux cones
 * 
 * \param cone1 : le premier cone à comparer 
 * \param cone2 : le deuxième cone à comparer
 * \return 1 si ce sont les même, 0 sinon
 */
int compareCone(cone cone1, cone cone2);

/**
 * \fn int compareCylindre(cylinder cylindre1, cylinder cylindre2)
 * \brief fonction permettant de comparer deux cylindres
 * 
 * \param cylindre1 : le premier cylindre à comparer 
 * \param cylindre2 : le deuxième cylindre à comparer
 * \return 1 si ce sont les même, 0 sinon
 */
int compareCylindre(cylinder cylindre1, cylinder cylindre2);

/**
 * \fn int compareTorus(torus torus1, torus torus2)
 * \brief fonction permettant de comparer deux cubes
 * 
 * \param torus1 : le premier tore à comparer 
 * \param torus2 : le deuxième tore à comparer
 * \return 1 si ce sont les même, 0 sinon
 */
int compareTorus(torus torus1, torus torus2);

#endif
