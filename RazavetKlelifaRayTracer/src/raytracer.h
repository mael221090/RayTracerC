/* \file raytracer.h
*  \author Razavet Maël & Klelifa Sarah
*  \version 0.1
*  \date 10/11/10
*  
*  \brief Fonction qui permet de lancer le programme
*
*
*
*/

#ifndef RAYTRACER
#define RAYTRACER
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "mappage.h"
#include "sphere.h"
#include "plan.h"
#include "camera.h"
#include "LectureFichier.h"
#include "lumiere.h"
#include "triangle.h"
#include "cylindre.h"
#include "cube.h"
#include "cone.h"
#include "tore.h"
#include "objet.h"

#include <values.h>

/**
 * \fn int main(int argc, const char* argv[])
 * \brief main, fonction qui lance le programme
 * 
 * \param argc
 * \param argv
 * \return la bonne execution du programme
 */
int main(int argc, const char* argv[]);

/**
 * \fn void envoieRayon(int x, int y,objet obj, objetCSG objetcsg, listeIntersection lIntersection)
 * \brief fonction qui gère l'envoie des rayons
 * 
 * \param x : resolution de l'ecran en largeur
 * \param y : resolution de l'ecran en hauteur
 * \param obj : la structure contenant les objets que contient la scène
 * \param objetcsg : structure contenant les objets ayant une csg définie
 * \param lIntersection: ma liste d'intersection contenant les primitives
 */
void envoieRayon(int x, int y,objet obj, objetCSG objetcsg, listeIntersection lIntersection);

/**
 * \fn int objetLePlusProche(objet obj, vecteur* plusProcheIntersection, objetPlusProche* objetProche, rayon ray, objetCSG objetcsg, listeIntersection lIntersection)
 * \brief fonction qui calcul l'objet le plus proche du rayon
 * 
 * \param obj : structure contenant tout les objets de la scène
 * \param plusProcheIntersection : la plus proche intersection
 * \param objetProche : structure contenant tout les objets les plus proches du rayon
 * \param ray : le rayon envoyé
 * \param objetcsg: la structure d'objets possédant une csg de définie
 * \param lIntersection: ma liste d'intersection contenant les primitives
 */
int objetLePlusProche(objet obj, vecteur* plusProcheIntersection, objetPlusProche* objetProche, rayon ray, objetCSG objetcsg, listeIntersection lIntersection);

#endif
