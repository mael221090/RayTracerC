/* \file transformation.c
 * \brief Fonction permettant de gerer une transformation
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date 10/11/10
 * 
 *
 *
 */


//Inclusion des entêtes de librairie
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "transformation.h"

//fonction qui ajoute une matrice en tête de la liste de matrice
listeMatrice* ajouterEnTete(listeMatrice* l, double*** valeur){

    // On crée un nouvel élément 
    listeMatrice* nouvelElement = malloc(sizeof(listeMatrice));
 
    // On assigne la valeur au nouvel élément 
    nouvelElement->matrice = valeur;
 
    // On assigne l'adresse de l'élément suivant au nouvel élément 
    nouvelElement->suivant = l;
 
    // On retourne la nouvelle liste, i.e. le pointeur sur le premier élément 
    return (nouvelElement);
}

//fonction permettant de creer une matrice et de lui alloquer de la mémoire
double ** creerMatrice(int n){
	double** matriceTransfo;
	int i;

	//on alloue la mémoire à la matrice
	matriceTransfo = malloc(n * sizeof(double*));
	if(matriceTransfo == NULL){
		printf("L'allocation de la mémoire pour la matrice à échoué 1");
		exit(EXIT_FAILURE);
	}
	for(i=0 ; i < n ; i++){
		matriceTransfo[i] = malloc(n*(sizeof(double)));       
		if(matriceTransfo[i] == NULL){                              
			printf("L'allocation de la mémoire pour la matrice à échoué 2");
			exit(EXIT_FAILURE);
		}
	}
	return (matriceTransfo);
}

//calcul de la transposer d'une matrice
double** transposer(double** matrice){
	double** Mtranspose;
	
	Mtranspose = creerMatrice(4);
	int i, j;
	for(i=0; i<4; i++){
		for(j=0;j<4;j++){
			Mtranspose[i][j] = matrice[j][i];
		}
	}
	return Mtranspose;
}

//fonction permettant de libèrer la matrice en mémoire
void libereMatrice(double** matrice, int n){
	int i;
	for (i=0;i<n; i++){
		free(matrice[i]);
	}
	free(matrice);
}

//fonction permettant de remplir une matrice de zéro
double** remplitMatrice(double** matrice, int n){
	int i;
	int j;
	//on rempli la matrice pour que ce soit une matrice identité
	for(i=0; i<n; i++){
		for(j=0;j<n;j++){
			matrice[i][j]=0;
		}
	}
	return (matrice);
}

//fonction qui compare deux matrices entre elles
int compareMatrice(double** matrice1, double** matrice2){
	int i;
	int j;
	int bool;
	bool=1;
	//on regarde pour chaque case des deux matrices si elles sont égales
	for(i=0; i<4; i++){
		for(j=0;j<4;j++){
			bool = matrice1[i][j]==matrice2[i][j] && bool;
		}
	}
	return (bool);
}

//fonction qui remplit une matrice de telle façon que ce soit la matrice identité
double** matriceIdentite(double** matriceTransfo, int n){
	int i;
	int j;
	//on rempli la matrice pour que ce soit une matrice identité
	for(i=0; i<n; i++){
		for(j=0;j<n;j++){
			if(i==j){
				matriceTransfo[i][j]=1;
			}else{
				matriceTransfo[i][j]=0;
			}
		}
	}
	return (matriceTransfo);
}

//fonction qui remplit les matrices transformations suivant le type de transformation et le vecteur associé
double ** transformation(int typeTransfo, vecteur vecteurTransfo){
	double** matriceTransfo;
	double** matriceTmp;
	double** matriceTransfoX;
	double** matriceTransfoY;
	double** matriceTransfoZ;
	int boolx =0;
	int booly =0;
	int boolz =0; 

	matriceTransfo = creerMatrice(4);
	matriceTransfo = matriceIdentite(matriceTransfo, 4);
	
	if(typeTransfo==3){
		matriceTmp = creerMatrice(4);
		matriceTransfoX = creerMatrice(4);
		matriceTransfoY = creerMatrice(4);
		matriceTransfoZ = creerMatrice(4);
		
		matriceTmp =  matriceIdentite(matriceTmp, 4);
		matriceTransfoX =  matriceIdentite(matriceTransfoX, 4);
		matriceTransfoY =  matriceIdentite(matriceTransfoY, 4);
		matriceTransfoZ =  matriceIdentite(matriceTransfoZ, 4);
	}
	
	switch(typeTransfo){

	case 1://si c'est une translation
		/*for(i=0;i<3;i++){
			matriceTransfo[i][3]=vecteurTransfo[i];
		}*/
		matriceTransfo[0][3]=vecteurTransfo.x;
		matriceTransfo[1][3]=vecteurTransfo.y;
		matriceTransfo[2][3]=vecteurTransfo.z;
		
		break;
	case 2://si c'est un scale
		matriceTransfo[0][0] = vecteurTransfo.x;
		matriceTransfo[1][1] = vecteurTransfo.y;
		matriceTransfo[2][2] = vecteurTransfo.z;
		break;
	case 3://si c'est une rotation
		
		if(vecteurTransfo.x!=0){//selon l'axe des x
			boolx = 1;
			vecteurTransfo.x = vecteurTransfo.x*(M_PI/180);
			matriceTransfo[1][1]= cos(vecteurTransfo.x);
			matriceTransfo[1][2]=-sin(vecteurTransfo.x);
			matriceTransfo[2][1]= sin(vecteurTransfo.x);
			matriceTransfo[2][2]= cos(vecteurTransfo.x);
		}
		if(vecteurTransfo.y!=0){//selon l'axe des y
				
				
			booly = 1;
			vecteurTransfo.y = vecteurTransfo.y*(M_PI/180);
			matriceTransfo[0][0]= cos(vecteurTransfo.y);
			matriceTransfo[0][2]= sin(vecteurTransfo.y);
			matriceTransfo[2][0]=-sin(vecteurTransfo.y);
			matriceTransfo[2][2]= cos(vecteurTransfo.y);
	
		}
		if(vecteurTransfo.z!=0){//selon l'axe des z
				
			boolz = 1;
			vecteurTransfo.z = vecteurTransfo.z*(M_PI/180);
			matriceTransfo[0][0]= cos(vecteurTransfo.z);
			matriceTransfo[0][1]= -sin(vecteurTransfo.z);
			matriceTransfo[1][0]= sin(vecteurTransfo.z);
			matriceTransfo[1][1]= cos(vecteurTransfo.z);
		}
		
		//si plusieur menbre du vecteur rotation sont remplit, on multiplie les matrices entre elles
		if(boolx && booly){
			if(boolz){
				matriceTmp = produitMatricielle(matriceTransfoZ, matriceTransfoY,4);
				matriceTransfo = produitMatricielle(matriceTmp, matriceTransfoX,4);
			}else{
				matriceTransfo = produitMatricielle(matriceTransfoY, matriceTransfoX,4);
			}
		}else if(booly && boolz){
			matriceTransfo = produitMatricielle(matriceTransfoZ, matriceTransfoY,4);
		}else if(boolx && boolz){
			matriceTransfo = produitMatricielle(matriceTransfoZ, matriceTransfoX,4);
		}
		libereMatrice(matriceTmp,4);
		libereMatrice(matriceTransfoX,4);
		libereMatrice(matriceTransfoY,4);
		libereMatrice(matriceTransfoZ,4);
		break;

	default:
		printf("probleme transfo");	
	}
	return (matriceTransfo);
}

//fonction permettant de calculer le produit matricielle entre deux matrices
double** produitMatricielle(double** pmatrice, double** dmatrice,int n){
	double** resultProduit;
	resultProduit = creerMatrice(n);
	int i,j,k;
	double res;
	//on fait le produit matricielle des deux matrices
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			res=0;
			for(k=0; k<n;k++){//on multiple la ligne de la premier matrice par la colonne de l'autre
				res=pmatrice[i][k]*dmatrice[k][j]+res;
			}
			resultProduit[i][j]=res;
		}
	}
	return (resultProduit);
}

//fonction permettant de calculer le produit d'une matrice et d'un vecteur de taille 4 
vecteur4 produitMatriceNonCarree(double** pmatrice, vecteur4 vecteur,int n){
	vecteur4 resultProduit;
	//on multiplie chaque composante du vecteur de taille 4 par la matrice
	resultProduit.x = pmatrice[0][0]*vecteur.x + pmatrice[0][1]*vecteur.y + pmatrice[0][2]*vecteur.z + pmatrice[0][3]*vecteur.w ;
	resultProduit.y = pmatrice[1][0]*vecteur.x + pmatrice[1][1]*vecteur.y + pmatrice[1][2]*vecteur.z + pmatrice[1][3]*vecteur.w ;
	resultProduit.z = pmatrice[2][0]*vecteur.x + pmatrice[2][1]*vecteur.y + pmatrice[2][2]*vecteur.z + pmatrice[2][3]*vecteur.w ;
	resultProduit.w = pmatrice[3][0]*vecteur.x + pmatrice[3][1]*vecteur.y + pmatrice[3][2]*vecteur.z + pmatrice[3][3]*vecteur.w ;
	
	return (resultProduit);
}

//fonction qui permet d'afficher une matrice 
void afficheMatrice(double** matrice,int n){
	int i;
	int j;
	
	for(i=0; i<n; i++){
		for(j=0;j<n;j++){
			printf(" %lf", matrice[i][j]);
		}
		printf("\n");
	}
}

//fonction qui calcul la sous matrice d'une matrice
double** sousMatrice(double** matrice, int k, int l, int n){
	double** ssMatrice;
	int s;
	int r;
	int i;
	int j;
	int bool;
	bool=0;
	s=0;
	ssMatrice = creerMatrice(n-1);

	for(i=0; i<n; i++){
		r=0;
		for(j=0; j<n; j++){
			if(i!=k && j!=l){
				ssMatrice[s][r] = matrice[i][j];
				bool=1;
				r++;
			}
		}
		if(i!=k){
			s++;
		}
	}
	return (ssMatrice);
}

//fonction permettant de calculer le determinant d'une matrice
double determinant(double** matrice, int n){
	double res;
	double** ssMatrice;
	int i;
	i=0;
	res =0;
	if(n==1){
		res = matrice[0][0];
	}else{
		for(i=0; i<n; i++){
			ssMatrice = sousMatrice(matrice,0,i,n);
			res = matrice[0][i]*determinant(ssMatrice,n-1)*pow(-1,i) +res;
			libereMatrice(ssMatrice, n-1);
		}
	}
	return (res);
}

//fonction permettant de calculer l'inverse d'une matrice
double** matriceInverse(double** matrice, int n){
	double** matriceInv;
	double** ssmatrice;
	int i, j;
	double det;
	matriceInv = creerMatrice(n);

	det = determinant(matrice, n);
	for(i=0; i<n; i++){
		for(j=0;j<n;j++){
			ssmatrice = sousMatrice(matrice,j,i,n);
			matriceInv[i][j] = (1/det)*determinant(ssmatrice,n-1)*pow(-1,i+j);
			libereMatrice (ssmatrice, n-1);
		}
	}
	return (matriceInv);
}
