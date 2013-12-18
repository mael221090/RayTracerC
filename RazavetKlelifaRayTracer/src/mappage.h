/* \file test.h
*  \author Razavet Maël & Klelifa Sarah
*  \version 0.1
*  \date 10/11/10
*  
*  \brief Permet de mapper un fichier en mémoire
*
*
*
*/

#ifndef LECTUREFICHIER2
#define LECTUREFICHIER2
#include "LectureFichier.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

/**
 * \fn int ouvre(char* chemin_fichier, int x, int y, objet* obj, objetCSG* objetcsg, listeIntersection* lIntersection)
 * \brief fonction qui gère l'envoie des rayons
 * 
 * \param chemin_fichier: le chemin du fichier à mapper
 * \param x : resolution de l'ecran en largeur
 * \param y : resolution de l'ecran en hauteur
 * \param obj : la structure contenant les objets que contient la scène
 * \param objetcsg : structure contenant les objets ayant une csg définie
 * \param lIntersection: liste dintersection
 * \return EXIT_SUCCESS
 */
int ouvre(char* chemin_fichier, int x, int y, objet* obj, objetCSG* objetcsg, listeIntersection* lIntersection);

#endif

