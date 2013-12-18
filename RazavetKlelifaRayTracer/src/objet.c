/* \file objet.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date mond oct 11
 * 
 * \brief Fonction permet de comparer deux ojets entre eux
 *
 *
 */

//Inclusion des entetes de librairie
#include "objet.h"

//fonction qui compare deux cubes entre eux
int compareCube(box cube1, box cube2){
	return (compareVecteur(cube1.coordonneePoint1,cube2.coordonneePoint1) && compareVecteur(cube1.coordonneePoint2,cube2.coordonneePoint2) && compareVecteur(cube1.pigment, cube2.pigment) && compareMatrice(cube1.matriceTransfo, cube2.matriceTransfo));
}

//fonction qui compare deux spheres entre eux
int compareSphere(sphere sphere1, sphere sphere2){
	return (compareVecteur(sphere1.location,sphere2.location) && sphere1.rayon==sphere2.rayon && compareVecteur(sphere1.pigment, sphere2.pigment) && compareMatrice(sphere1.matriceTransfo, sphere2.matriceTransfo));
}

//fonction qui compare deux triangles entre eux
int compareTriangle(triangle triangle1, triangle triangle2){
	return (compareVecteur(triangle1.coin1,triangle2.coin1) && compareVecteur(triangle1.coin2,triangle2.coin2)&& compareVecteur(triangle1.coin3,triangle2.coin3) && compareVecteur(triangle1.pigment, triangle2.pigment) && compareMatrice(triangle1.matriceTransfo, triangle2.matriceTransfo));
}

//fonction qui compare deux plans entre eux
int comparePlan(plane plan1, plane plan2){
	return (compareVecteur(plan1.location,plan2.location) && plan1.distance==plan2.distance && compareVecteur(plan1.pigment, plan2.pigment) && compareMatrice(plan1.matriceTransfo, plan2.matriceTransfo));
}

//fonction qui compare deux cones entre eux
int compareCone(cone cone1, cone cone2){
	return (compareVecteur(cone1.coordonneeExtremite1,cone2.coordonneeExtremite1) && compareVecteur(cone1.coordonneeExtremite1,cone2.coordonneeExtremite1) && cone1.rayon1==cone2.rayon1 && cone1.rayon2==cone2.rayon2 &&compareVecteur(cone1.pigment, cone2.pigment) && compareMatrice(cone1.matriceTransfo, cone2.matriceTransfo));
}

//fonction qui compare deux cylindres entre eux
int compareCylindre(cylinder cylindre1, cylinder cylindre2){
	return (compareVecteur(cylindre1.coordonneeExtremite1,cylindre2.coordonneeExtremite1) && compareVecteur(cylindre1.coordonneeExtremite2,cylindre2.coordonneeExtremite2) && cylindre1.rayon==cylindre2.rayon && compareVecteur(cylindre1.pigment, cylindre2.pigment) && compareMatrice(cylindre1.matriceTransfo, cylindre2.matriceTransfo));
}

//fonction qui compare deux tores entre eux
int compareTorus(torus torus1, torus torus2){
	return (torus1.rayon1==torus2.rayon1 && torus1.rayon2==torus2.rayon2 && compareVecteur(torus1.pigment, torus2.pigment) && compareMatrice(torus1.matriceTransfo, torus2.matriceTransfo));
}
	
