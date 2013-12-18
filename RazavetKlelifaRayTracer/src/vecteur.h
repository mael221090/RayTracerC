/* \file vecteur.h
 *  \brief structure et opération sur vecteur de taille 3 et 4
 *  \author Razavet Maël & Klelifa Sarah
 *  \version 0.1
 *  \date 10/11/10
 *  
 */

#ifndef VECTEUR
#define VECTEUR

#include <math.h>
#include <values.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * \struct vecteur
 * \brief structure définissant un vecteur de taille 3
 *
 */
typedef struct{
	float x;/**< struct composante x */
	float y;/**< struct composante y */
 	float z;/**< struct composante z */
}vecteur;

/**
 * \struct vecteur4
 * \brief structure définissant un vecteur de taille 4
 *
 */
typedef struct{
	float x;/**< struct composante x */
	float y;/**< struct composante y */
 	float z;/**< struct composante z */
 	float w;/**< struct composante w */
}vecteur4;

/**
 * \fn vecteur diviseVecteur(vecteur tmp1, vecteur tmp2)
 * \brief fonction permettant de faire la division de deux vecteurs
 * 
 * \param tmp1 : vecteur de taille 3
 * \param tmp2 : vecteur de taille 3
 * \return le vecteur résultat
 */
vecteur diviseVecteur(vecteur tmp1, vecteur tmp2);

/**
 * \fn vecteur vector(float a, float b, float c)
 * \brief fonction de création d'un vecteur de taille 3
 * 
 * \param a : composante en x
 * \param b : composante en y
 * \param c : composante en z
 * \return un vecteur de taille 3
 */
vecteur vector(float a, float b, float c);

/**
 * \fn vecteur vector4(float a, float b, float c, float d)
 * \brief fonction de création d'un vecteur de taille 4
 * 
 * \param a : composante en x
 * \param b : composante en y
 * \param c : composante en z
 * \param d : composante en w
 * \return un vecteur de taille 4
 */
vecteur4 vector4(float a, float b, float c, float d);

/**
 * \fn vecteur normaliser(vecteur v)
 * \brief fonction permettant de normaliser un vecteur de taille 3
 * 
 * \param v : vecteur de taille 3
 * \return le vecteur normaliser
 */
vecteur normaliser(vecteur v);

/**
 * \fn vecteur4 opProduitScalaire4(vecteur4 tmp, float k)
 * \brief fonction permettant de multiplier un nombre a un vecteur de taille 4
 * 
 * \param tmp : vecteur de taille 4
 * \param k : nombre a multiplier
 * \return le vecteur résultat
 */
vecteur4 opProduitScalaire4(vecteur4 tmp, float k);

/**
 * \fn vecteur opProduitScalaire(vecteur tmp, float k)
 * \brief fonction permettant de multiplier un nombre a un vecteur de taille 3
 * 
 * \param tmp : vecteur de taille 3
 * \param k : nombre a multiplier
 * \return le vecteur résultat
 */
vecteur opProduitScalaire(vecteur tmp, float k);

/**
 * \fn vecteur4 opPlus4(vecteur4 tmp1, vecteur4 tmp2)
 * \brief fonction permettant d'additionner deux vecteurs de taille 4
 * 
 * \param tmp1 : vecteur de taille 4
 * \param tmp2 : vecteur de taille 4
 * \return le vecteur résultat
 */
vecteur4 opPlus4(vecteur4 tmp1, vecteur4 tmp2);

/**
 * \fn vecteur opPlus(vecteur tmp1, vecteur tmp2)
 * \brief fonction permettant d'additionner deux vecteurs de taille 3
 * 
 * \param tmp1 : vecteur de taille 3
 * \param tmp2 : vecteur de taille 3
 * \return le vecteur résultat
 */
vecteur opPlus(vecteur tmp1, vecteur tmp2);

/**
 * \fn vecteur opMoins(vecteur tmp1, vecteur tmp2)
 * \brief fonction permettant de soustraire deux vecteurs de taille 3
 * 
 * \param tmp1 : vecteur de taille 3
 * \param tmp2 : vecteur de taille 3
 * \return le vecteur résultat
 */
vecteur opMoins(vecteur tmp1, vecteur tmp2);

/**
 * \fn vecteur opProduitVectorielle(vecteur tmp1, vecteur tmp2)
 * \brief fonction permettant de faire le produit vectorielle entre deux vecteurs de taille 3
 * 
 * \param tmp1 : vecteur de taille 3
 * \param tmp2 : vecteur de taille 3
 * \return le vecteur résultat
 */
vecteur opProduitVectorielle(vecteur tmp1, vecteur tmp2);

/**
 * \fn vecteur opPlusVecteurScalaire(vecteur tmp1, float k)
 * \brief fonction permettant de diviser par un nombre un vecteur de taille 3
 * 
 * \param tmp1 : vecteur de taille 3
 * \param k : nombre a additionner
 * \return le vecteur résultat
 */
vecteur opPlusVecteurScalaire(vecteur tmp1, float k);

/**
 * \fn vecteur opProduit(vecteur tmp1, vecteur tmp2)
 * \brief fonction permettant de multiplier deux vecteurs de taille 3 entre eux
 * 
 * \param tmp1 : vecteur de taille 3
 * \param tmp2 : vecteur de taille 3
 * \return le vecteur résultat
 */
vecteur opProduit(vecteur tmp1, vecteur tmp2);

/**
 * \fn vecteur opDivise(vecteur tmp1, float k)
 * \brief fonction permettant de diviser par un nombre un vecteur de taille 3
 * 
 * \param tmp1 : vecteur de taille 3
 * \param k : nombre a multiplier
 * \return le vecteur résultat
 */
vecteur opDivise(vecteur tmp1, float k);

/**
 * \fn float calculDistance(vecteur A, vecteur B)
 * \brief fonction permettant de calculer la distance entre deux vecteurs de taille 3
 * 
 * \param A : vecteur de taille 3
 * \param B : vecteur de taille 3
 * \return la distance
 */
float calculDistance(vecteur A, vecteur B);

/**
 * \fn float calculDistancePoint(vecteur A, vecteur B)
 * \brief fonction permettant de calculer la distance entre deux points
 * 
 * \param A : vecteur de taille 3
 * \param B : vecteur de taille 3
 * \return la distance
 */
float calculDistancePoint(vecteur A, vecteur B);

/**
 * \fn float dot(vecteur A, vecteur B)
 * \brief fonction permettant de calculer le produit scalaire entre deux vecteur de taille 3
 * 
 * \param A : vecteur de taille 3
 * \param B : vecteur de taille 3
 * \return le nombre résultat
 */
float dot(vecteur A, vecteur B);

/**
 * \fn int compareVecteur(vecteur A, vecteur B)
 * \brief fonction permettant de comparer deux vecteurs de taille 3
 * 
 * \param A : vecteur de taille 3
 * \param B : vecteur de taille 3
 * \return 1 si ils sont egaux, 0 sinon
 */
int compareVecteur(vecteur A, vecteur B);

#endif
