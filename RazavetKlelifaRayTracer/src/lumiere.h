/* \file lumiere.c
 * \brief Fonction permettant de gerer la lumiere
 * \author Razavet Mael, Klelifa Sarah
 * \version 1.0
 * \date 20/11/10
 * 
 */
#ifndef LUMIERE
#define LUMIERE
#include "vecteur.h"
#include "LectureFichier.h"
#include "rayon.h"
#include <values.h>

/**
 * \fn vecteur lumierePixel(vecteur normal, vecteur intersection, vecteur mat, light_source lumiere, vecteur pigment)
 * \brief calcul de la couleur d'un pixel
 * 
 * \param normal :  la normal a l'objet au pixel corespondant
 * \param intersection : l'intersection entre le rayon et l'objet
 * \param mat : la couleur du matériel
 * \param lumiere : la lumiere du fichier.pov
 * \param pigment : la couleur du pixel
 * \return la nouvelle couleur du pixel
 */
vecteur lumierePixel(vecteur normal, vecteur intersection, vecteur mat, light_source lumiere, vecteur pigment);

#endif
