/* \file transformation.h
 *  \brief gestion lecture de fichier et création des structures objets
 *  \author Razavet Maël & Klelifa Sarah
 *  \version 0.1
 *  \date 10/11/10
 *  
 */
 
//Inclusion des entêtes de librairie
#ifndef TRANSFORMATION
#define TRANSFORMATION
#include "vecteur.h"


/**
 * \struct listeMatrice
 * \brief structure définissant une liste de lumiere
 *
 */
typedef struct listeMatrice{
        double*** matrice;/**< struct pointeur sur matrice courante*/
        struct listeMatrice* suivant;/**< struct pointeur sur le pointeur de la matrice suivante*/
}listeMatrice;

/**
 * \fn double** transposer(double** matrice)
 * \brief Fonction qui permet de calculer la transposer d'une matrice
 *
 * \param matrice : matrice que l'on veut transposer
 *
 * \return la transposer de la matrice
 *
 */
double** transposer(double** matrice);

/**
 * \fn int compareMatrice(double** matrice1, double** matrice2)
 * \brief Fonction qui compare deux matrices entre elles
 *
 * \param matrice1 première matrice que l'on veut comparer
 * \param matrice2 seconde matrice que l'on veut comparer
 *
 * \return renvoit 1 si ce sont les même, 0 sinon
 *
 */
int compareMatrice(double** matrice1, double** matrice2);

/**
 * \fn listeMatrice* ajouterEnTete(listeMatrice* l, double*** valeur)
 * \brief fonction qui ajoute une matrice en tete d'une liste
 * 
 * \param l la liste a laquelle on veut ajouter la matrice
 * \param valeur la matrice a ajouter
 * \return la liste modifiee
 */
listeMatrice* ajouterEnTete(listeMatrice* l, double*** valeur);

/**
 * \fn double ** transformation(int typeTransfo, vecteur vecteurTransfo)
 * \brief Fonction qui permet de calculer la matrice transformation associer a un objet
 *
 * \param typeTransfo entier indiquant quel est le type de transformation(scale, rotate ou translate)
 * \param vecteurTransfo vecteur contenant les coordonnées de la transformation
 *
 * \return la matrice transformation
 *
 */
double** transformation(int typeTransfo, vecteur vecteurTransfo);

/**
 * \fn double ** creerMatrice(int n)
 * \brief Fonction qui creer une matrice
 *
 * \param n taille de la matrice
 * \return la matrice identité
 *
 */
double ** creerMatrice(int n);

/**
 * \fn double** produitMatricielle(double** pmatrice, double** dmatrice,int n)
 * \brief Fonction qui permet de calculer le produit matricielle entre deux matrices
 *
 * \param pmatrice première matrice dont on veut faire le produit
 * \param dmatrice seconde matrice dont on veut faire le produit 
 * \param n taille de la matrice
 *
 * \return la matrice résultat du produit matricielle
 *
 */
double** produitMatricielle(double** pmatrice, double** dmatrice,int n);

/**
 * \fn void afficheMatrice(double** matrice, int n)
 * \brief Fonction qui permet d'afficher une matrice
 *
 * \param matrice matrice a afficher
 * \param n taille de la matrice a afficher
 *
 */
void afficheMatrice(double** matrice, int n);

/**
 * \fn double** remplitMatrice(double** matrice, int n)
 * \brief Fonction qui remplit une matrice de zéro
 *
 * \param matrice a remplir
 * \param n taille de la matrice
 * \return la matrice remplit de zéro
 *
 */
double** remplitMatrice(double** matrice, int n);

/**
 * \fn double** matriceIdentite(double** matriceTransfo, int n)
 * \brief Fonction qui initialise une matrice identitée
 *
 * \param matriceTransfo : matrice a remplir
 * \param n taille de la matrice
 * \return la matrice identité
 *
 */
double** matriceIdentite(double** matriceTransfo, int n);

/**
 * \fn double** sousMatrice(double** matrice, int k, int l, int n)
 * \brief Fonction qui calcule la sous matrice d'une matrice
 *
 * \param matrice : matrice dont on veut la sous matrice
 * \param n : taille de la matrice
 * \param k : indice de ligne
 * \param l : indice de colonne
 * \return sous matrice correspondante
 *
 */
double** sousMatrice(double** matrice, int k, int l, int n);

/**
 * \fn double** matriceInverse(double** matrice, int n)
 * \brief Fonction qui calcul la matrice inverse d'une matrice
 *
 * \param matrice : matrice dont on veut calculer la matrice inverse
 * \param n taille de la matrice
 * \return la matrice inverse
 *
 */
double** matriceInverse(double** matrice, int n);

/**
 * \fn double determinant(double** matrice, int n);
 * \brief Fonction qui calcul le déterminant
 *
 * \param matrice : matrice dont on veut calculer le determinant
 * \param n taille de la matrice
 * \return la matrice inverse
 *
 */
double determinant(double** matrice, int n);

/**
 * \fn vecteur4 produitMatriceNonCarree(double** pmatrice, vecteur4 vecteur,int n)
 * \brief Fonction qui permet de calculer le produit matricielle entre deux matrices
 *
 * \param pmatrice première matrice dont on veut faire le produit
 * \param vecteur dont on veut faire le produit
 * \param n taille de la matrice
 *
 * \return la matrice résultat du produit entre le vecteur et la matrice
 *
 */
vecteur4 produitMatriceNonCarree(double** pmatrice, vecteur4 vecteur,int n);

/**
 * \fn void libereMatrice (double** matrice, int n)
 * \brief Fonction qui libere une matrice en mémoire
 *
 * \param matrice : matrice dont on veut liberer la mémoire
 * \param n taille de la matrice
 *
 */
void libereMatrice (double** matrice, int n);

#endif
