/* \file LectureFichier.h
 *  \brief gestion lecture de fichier et création des structures objets
 *  \author Razavet Maël & Klelifa Sarah
 *  \version 0.1
 *  \date 10/11/10
 *  
 */
//Inclusion des entêtes de librairie

#ifndef LECTUREFICHIER
#define LECTUREFICHIER
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vecteur.h"
#include "transformation.h"
//les structures

/**
 * \struct camera
 * \brief structure définissant une caméra
 *
 */
typedef struct {
        vecteur location;/**< struct vecteur de position de la camera*/
        vecteur look_at;/**< struct vecteur indiquant ou la camera regarde */
}camera;

/**
 * \struct background
 * \brief structure définissant un arriere plan
 *
 */
typedef struct {
        vecteur color_rgb;/**< struct vecteur indiquant la couleur d'arriere plan */
}background;

/**
 * \struct materiel
 * \brief structure définissant un materiel
 *
 */
typedef struct {
        vecteur color_rgb;/**< struct vecteur indiquant la couleur du matériel */
        //non fini
}materiel;

/**
 * \struct light_source
 * \brief structure définissant une lumiere
 *
 */
typedef struct {
        vecteur location;/**< struct vecteur de position de la lumiere*/
        vecteur color_rgb;/**< struct vecteur indiquant la couleur de la lumiere */
}light_source;

/**
 * \struct listeLight
 * \brief structure définissant une liste de lumiere
 *
 */
typedef struct listeLight{
        light_source lumiere;/**< struct lumiere courante*/
        struct listeLight* suivant;/**< struct pointeur sur la lumiere suivante*/
}listeLight;



/**
 * \struct plane
 * \brief structure définissant un plan
 *
 */
typedef struct{
        vecteur pigment;/**< struct vecteur indiquant la couleur du plan */
        vecteur location;/**< struct vecteur de position du plan*/
        float distance;/**< struct distance entre le plan et le sol*/
        double** matriceTransfo;/**< struct matrice de transformation*/
        double** matriceTransfoInverse;/**< struct matrice de transformation inverse*/
        int booleenCSG;/**<int booleenCSG pour définir si il y a une csg et laquelle c'est*/
        vecteur normale;/**< struct normale a la face intersecter*/
}plane;

/**
 * \struct listePlane
 * \brief structure définissant une liste de plan
 *
 */
typedef struct listePlane{
        plane plan;/**< struct plan courant*/
        struct listePlane* suivant;/**< struct pointeur sur le plan suivant*/
}listePlane;

/**
 * \struct sphere
 * \brief structure définissant une sphere
 *
 */
typedef struct{
        vecteur location;/**< struct vecteur de position de la sphere*/
        float rayon;/**< struct rayon de la sphere*/
        vecteur pigment;/**< struct vecteur indiquant la couleur de la sphere */
        double** matriceTransfo;/**< struct matrice de transformation*/
        double** matriceTransfoInverse;/**< struct matrice de transformation inverse*/
        int booleenCSG;/**<int booleenCSG pour définir si il y a une csg et laquelle c'est*/
        vecteur normale;/**< struct normale a la face intersecter*/
}sphere;

/**
 * \struct listeSphere
 * \brief structure définissant une liste de sphere
 *
 */
typedef struct listeSphere{
        sphere boule;/**< struct sphere courante*/
        struct listeSphere* suivant;/**< struct pointeur sur la sphere suivante*/
}listeSphere;

/**
 * \struct box
 * \brief structure définissant un cube
 *
 */
typedef struct{
        vecteur coordonneePoint1;/**< struct vecteur d'indiquant la coordonnee du premier coin de la boite*/
        vecteur coordonneePoint2;/**< struct vecteur d'indiquant la coordonnee du deuxieme coin de la boite*/
        vecteur pigment;/**< struct vecteur indiquant la couleur d'une boite */
        double** matriceTransfo;/**< struct matrice de transformation*/
        double** matriceTransfoInverse;/**< struct matrice de transformation inverse*/
        vecteur normale;/**< struct normale a la face intersecter*/
        int booleenCSG;/**<int booleenCSG pour définir si il y a une csg et laquelle c'est*/
}box;

/**
 * \struct listeBox
 * \brief structure définissant une liste de cube
 *
 */
typedef struct listeBox{
        box boite;/**< struct cube courant*/
        struct listeBox* suivant;/**< struct pointeur sur le cube suivant*/
}listeBox;

/**
 * \struct cylinder
 * \brief structure définissant un cylindre
 *
 */
typedef struct{
        vecteur coordonneeExtremite1;/**< struct vecteur d'indiquant la coordonnee de la premiere extremité du cylindre*/
        vecteur coordonneeExtremite2;/**< struct vecteur d'indiquant la coordonnee de la deuxieme extremité du cylindre*/
        float rayon;/**< struct rayon de la cylindre*/
        vecteur pigment;/**< struct vecteur indiquant la couleur du cylindre */
        double** matriceTransfo;/**< struct matrice de transformation*/
        double** matriceTransfoInverse;/**< struct matrice de transformation inverse*/
        vecteur normale;/**< struct normale a la face intersecter*/
        int booleenCSG;/**<int booleenCSG pour définir si il y a une csg et laquelle c'est*/
}cylinder;

/**
 * \struct listeCylinder
 * \brief structure définissant une liste de cylindre
 *
 */
typedef struct listeCylinder{
        cylinder cylindre;/**< struct cylindre courant*/
        struct listeCylinder* suivant;/**< struct pointeur sur le cylindre suivant*/
}listeCylinder;

/**
 * \struct cone
 * \brief structure définissant un cone
 *
 */
typedef struct{
        vecteur coordonneeExtremite1;/**< struct vecteur d'indiquant la coordonnee de la premiere extremité du cone*/
        vecteur coordonneeExtremite2;/**< struct vecteur d'indiquant la coordonnee de la deuxieme extremité du cone*/
        vecteur pigment;/**< struct vecteur indiquant la couleur du cone */
        float rayon1;/**< struct premier rayon du cone*/
        float rayon2;/**< struct deuxieme rayon du cone*/
        double** matriceTransfo;/**< struct matrice de transformation*/
        double** matriceTransfoInverse;/**< struct matrice de transformation inverse*/
        int booleenCSG;/**<int booleenCSG pour définir si il y a une csg et laquelle c'est*/
        vecteur normale;/**< struct normale a la face intersecter*/
}cone;

/**
 * \struct listeCone
 * \brief structure définissant une liste de cone
 *
 */
typedef struct listeCone{
        cone cone1;/**< struct cone courant*/
        struct listeCone* suivant;/**< struct pointeur sur le cone suivant*/
}listeCone;

/**
 * \struct torus
 * \brief structure définissant un tore
 *
 */
typedef struct{
        float rayon1;/**< struct premier rayon du tore*/
        float rayon2;/**< struct deuxieme rayon du tore*/
        vecteur pigment;/**< struct vecteur indiquant la couleur du tore */
        double** matriceTransfo;/**< struct matrice de transformation*/
        double** matriceTransfoInverse;/**< struct matrice de transformation inverse*/
        vecteur normale;/**< struct normale a la face intersecter*/
        int booleenCSG;/**<int booleenCSG pour définir si il y a une csg et laquelle c'est*/
}torus;

/**
 * \struct listeTorus
 * \brief structure définissant une liste de tore
 *
 */
typedef struct listeTorus{
        torus tore;/**< struct tore courant*/
        struct listeTorus* suivant;/**< struct pointeur sur le tore suivant*/
}listeTorus;

/**
 * \struct triangle
 * \brief structure définissant un triangle
 *
 */
typedef struct{
	vecteur coin1;/**< struct vecteur d'indiquant la coordonnee de la premiere extremité du triangle*/
	vecteur coin2;/**< struct vecteur d'indiquant la coordonnee de la deuxième extremité du triangle*/
	vecteur coin3;/**< struct vecteur d'indiquant la coordonnee de la troisième extremité du triangle*/
	vecteur pigment;/**< struct vecteur indiquant la couleur du triangle */
	double** matriceTransfo;/**< struct matrice de transformation*/
	double** matriceTransfoInverse;/**< struct matrice de transformation inverse*/
	int booleenCSG;/**<int booleenCSG pour définir si il y a une csg et laquelle c'est*/
	vecteur normale;/**< struct normale a la face intersecter*/
}triangle;

/**
 * \struct listeTriangle
 * \brief structure définissant une liste de triangle
 *
 */
typedef struct listeTriangle{
	triangle tgle;/**< struct triangle courant*/
	struct listeTriangle* suivant;/**< struct pointeur sur le triangle suivant*/
}listeTriangle;

/**
 * \struct objet
 * \brief structure contenant toutes les listes d'objet
 *
 */
typedef struct{
        listeSphere* lsphere;/**< struct liste de sphere*/
        listeBox* lbox;/**< struct liste de cube*/
        listeCylinder* lcylindre;/**< struct liste de cylindre*/
        listeTorus* ltore;/**< struct liste de tore*/
        listeCone* lcone;/**< struct liste de cone*/
        listePlane* lplan;/**< struct liste de plan*/
        listeTriangle* ltriangle;/**< struct liste de triangle*/
        camera cam;/**< struct camera*/
        listeLight* llumiere;/**< struct liste de lumiere*/
        background arrierePlan;/**< struct liste d'arriere plan*/
}objet;

/**
 * \struct listeUnion
 * \brief structure contenant toutes les listes d'objet ainsi que les CSG
 *
 */
typedef struct{
        objet obj;/**<objet contenant toutes les primitives */
        struct listeUnion* suivant;/**< struct pointeur sur la liste suivante*/
}listeUnion;       

/**
 * \struct listeIntersection
 * \brief structure contenant toutes les listes d'objet ainsi que les CSG
 *
 */
typedef struct{
       objet obj;/**<objet contenant toutes les primitives */
       struct  listeIntersection* suivant;/**< struct pointeur sur la liste suivante*/
}listeIntersection; 
      
/**
 * \struct listeDifference
 * \brief structure contenant toutes les listes d'objet ainsi que les CSG
 *
 */
typedef struct{
        objet obj;/**<objet contenant toutes les primitives */
        struct listeDifference* suivant;/**< struct pointeur sur la liste suivante*/
}listeDifference;        

/**
 * \struct objetPlusProche
 * \brief structure contenant l'objet le plus proche du rayon
 *
 */
typedef struct{
        sphere spherePlusProche;/**< struct sphere la plus proche du rayon*/
	plane planPlusProche;/**< struct cube le plus proche du rayon*/
	cone conePlusProche;/**< struct cone le plus proche du rayon*/
	torus torePlusProche;/**< struct tore le plus proche du rayon*/
	cylinder cylindrePlusProche;/**< struct cylindre le plus proche du rayon*/
	box boitePlusProche;/**< struct cube le plus proche du rayon*/
	triangle trianglePlusProche;/**< struct triangle le plus proche du rayon*/
}objetPlusProche;

/**
 * \struct objetCSG
 * \brief structure contenant les objets definient avec une CSG et ayant intersection
 *
 */
typedef struct{
        listeSphere* lsphere;/**< struct liste de sphere*/
        listeBox* lbox;/**< struct liste de cube*/
        listeCylinder* lcylindre;/**< struct liste de cylindre*/
        listeTorus* ltore;/**< struct liste de tore*/
        listeCone* lcone;/**< struct liste de cone*/
        listeTriangle* ltriangle;/**< struct liste de triangle*/
        listePlane* lplan;/**< struct liste de plan*/
	int booleenCSG;/**<int booleenCSG qui indique si il y a eu une intersection, difference ou union de définie*/
	int ordreObjet;/**<char* ordreObjet pour stocker le premier objet lu*/
}objetCSG;

//les fonctions

/**
 * \fn void enleveEspace(char* tab)
 * \brief fonction permettant d'enlever les espaces d'une chaine de caractère
 * 
 * \param tab : chaine de caractère à traiter
 */
void enleveEspace(char* tab); 

/**
 * \fn void LectureFichier(objet* obj, char* fichier, int tailleFichier, objetCSG* objetcsg, listeIntersection* lIntersection)
 * \brief fonction permettant de lire le fichier .pov et de traiter les objets afin de les stocker dans des structures
 * 
 * \param obj : structure de liste d'objet
 * \param fichier : chaine de caractère à lire
 * \param tailleFichier : taille du fichier 
 * \param objetcsg : structure dobjet ayant une csg de définie
 * \param lIntersection : liste d'intersection 
 */
void LectureFichier(objet* obj, char* fichier, int tailleFichier, objetCSG* objetcsg, listeIntersection* lIntersection);

/**
 * \fn lireIntersection(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, listeIntersection* lIntersection, objetCSG* objetcsg)
 * \brief fonction permettant de lire une intersection
 * 
 * \param obj: structure de liste d'objets
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 ** \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire 
 * \param liste : ma liste de matrice transformation
 * \param matriceTranslate : la matrice translation 
 * \param matriceScale : la matrice Scale
 * \param matriceRotate : la matrice Rotation
 * \param lIntersection : liste d'intersection 
  * \param objetcsg : structure dobjet ayant une csg de définie
 */
void lireIntersection(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, listeIntersection* lIntersection, objetCSG* objetcsg);

/**
 * \fn lireUnion(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, listeUnion* lUnion, objetCSG* objetcsg)
 * \brief fonction permettant de lire une union
 * 
 * \param obj: structure de liste d'objets
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire 
 * \param liste : ma liste de matrice transformation
 * \param matriceTranslate : la matrice translation 
 * \param matriceScale : la matrice Scale
 * \param matriceRotate : la matrice Rotation
 * \param lUnion : liste d'union
  * \param objetcsg : structure dobjet ayant une csg de définie
 */
void lireUnion(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, listeUnion* lUnion, objetCSG* objetcsg);

/**
 * \fn lireDifference(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, listeDifference* lDifference, objetCSG* objetcsg)
 * \brief fonction permettant de lire une difference
 * 
 * \param obj: structure de liste d'objets
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire 
 * \param liste : ma liste de matrice transformation
 * \param matriceTranslate : la matrice translation 
 * \param matriceScale : la matrice Scale
 * \param matriceRotate : la matrice Rotation
 * \param lDifference : liste dde difference
  * \param objetcsg : structure dobjet ayant une csg de définie
 */
void lireDifference(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, listeDifference* lDifference, objetCSG* objetcsg);

/**
 * \fn lireCamera(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier)
 * \brief fonction permettant de lire une caméra
 * 
 * \param obj: structure de liste d'objets
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire
 */
void lireCamera(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier);

/**
 * \fn lireLightSource(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier)
 * \brief fonction permettant de lire les lights sources
 * 
* \param obj: structure de liste d'objets
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire
 */
void lireLightSource(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier);

/**
 * \fn lireBackground(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier)
 * \brief fonction permettant de lire background
 * 
 * \param obj: structure de liste d'objets
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire
 */
void lireBackground(objet* obj, char* tabObj, int tailleFichier, int* i, char* fichier);

/**
 * \fn lirePlan(listePlane* nvPlan, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg)
 * \brief fonction permettant de lire un plan
 * 
 * \param nvPlan: liste de plan
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire 
 * \param liste : ma liste de matrice transformation
 * \param matriceTranslate : la matrice translation 
 * \param matriceScale : la matrice Scale
 * \param matriceRotate : la matrice Rotation
  * \param objetcsg : structure dobjet ayant une csg de définie
 */
void lirePlan(listePlane* nvPlan, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg);

/**
 * \fn lireSphere(listeSphere* nvSphere, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg)
 * \brief fonction permettant de lire une sphere
 * 
 * \param nvSphere: liste de sphere
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire 
 * \param liste : ma liste de matrice transformation
 * \param matriceTranslate : la matrice translation 
 * \param matriceScale : la matrice Scale
 * \param matriceRotate : la matrice Rotation
  * \param objetcsg : structure dobjet ayant une csg de définie
 */
void lireSphere(listeSphere* nvSphere, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg);

/**
 * \fn lireTriangle(listeTriangle* nvTriangle, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg)
 * \brief fonction permettant de lire un triangle
 * 
 * \param nvTriangle: liste de triangle
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire
 * \param liste : ma liste de matrice transformation
 * \param matriceTranslate : la matrice translation 
 * \param matriceScale : la matrice Scale
 * \param matriceRotate : la matrice Rotation
  * \param objetcsg : structure dobjet ayant une csg de définie
 */
void lireTriangle(listeTriangle* nvTriangle, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg);

/**
 * \fn lireCube(listeBox* nvBoite, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg)
 * \brief fonction permettant de lire un cube
 * 
 * \param nvBoite: liste de cube
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire
 * \param liste : ma liste de matrice transformation
 * \param matriceTranslate : la matrice translation 
 * \param matriceScale : la matrice Scale
 * \param matriceRotate : la matrice Rotation
  * \param objetcsg : structure dobjet ayant une csg de définie
 */
void lireCube(listeBox* nvBoite, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate,  objetCSG* objetcsg);

/**
 * \fn lireCylindre(listeCylinder* nvCylindre, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg)
 * \brief fonction permettant de lire un cylindre
 * 
 * \param nvCylindre: liste de cylindre
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire
 * \param liste : ma liste de matrice transformation
 * \param matriceTranslate : la matrice translation 
 * \param matriceScale : la matrice Scale
 * \param matriceRotate : la matrice Rotation
  * \param objetcsg : structure dobjet ayant une csg de définie
 */
void lireCylindre(listeCylinder* nvCylindre, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg);

/**
 * \fn lireCone(listeCone* nvCone, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg)
 * \brief fonction permettant de lire un cone
 * 
 * \param nvCone: liste de cone
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire
 * \param liste : ma liste de matrice transformation
 * \param matriceTranslate : la matrice translation 
 * \param matriceScale : la matrice Scale
 * \param matriceRotate : la matrice Rotation
  * \param objetcsg : structure dobjet ayant une csg de définie
 */
void lireCone(listeCone* nvCone, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg);

/**
 * \fn lireTore(listeTorus* nvTore, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg)
 * \brief fonction permettant de lire un tore
 * 
 * \param nvTore: liste de tore
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param tailleFichier : taille du fichier 
 * \param i : indique la position de lecture du fichier
 * \param fichier : chaine de caractère à lire
 * \param liste : ma liste de matrice transformation
 * \param matriceTranslate : la matrice translation 
 * \param matriceScale : la matrice Scale
 * \param matriceRotate : la matrice Rotation
   * \param objetcsg : structure dobjet ayant une csg de définie
  * \param objetcsg : structure dobjet ayant une csg de définie
 */
void lireTore(listeTorus* nvTore, char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate, objetCSG* objetcsg);

/**
 * \fn double** initialiseMatrice(listeMatrice* liste)
 * \brief fonction permettant d'initialiser la matrice transformation d'un objet
 * 
 * \param liste : ma liste de matrice transformation
 */
double** initialiseMatrice(listeMatrice* liste);

/**
 * \fn listeMatrice* getTransformation(char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate )
 * \brief fonction permettant de lire le fichier .pov et de traiter les objets afin de les stocker dans des structures
 * 
 * \param i : indique la position de lecture du fichier
 * \param tabObj : chaine de caractere servant à stocker les caractères du ficher
 * \param fichier : chaine de caractère à lire
 * \param tailleFichier : taille du fichier 
 * \param liste : ma liste de matrice transformation
 * \param matriceTranslate : la matrice translation 
 * \param matriceScale : la matrice Scale
 * \param matriceRotate : la matrice Rotation
 */
listeMatrice* getTransformation(char* tabObj, int tailleFichier, int* i, char* fichier, listeMatrice* liste, double** matriceTranslate, double** matriceScale, double** matriceRotate );

#endif
