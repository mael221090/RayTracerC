/* \file cylindre.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date 11/12/10
 * 
 * \brief Fonction qui permet de calculer lintersection avec un cylindre
 *
 *
 */

//Inclusion des entetes de librairie
#include "cylindre.h"


//calcule l'intersection entre un rayon et un cylindre
int intersectCylindre(rayon ray, cylinder cylindre, float* t, vecteur* intersection, vecteur* normale){
	//déclaration de variables
	//3 variables de l'équation du second degré entre rayon et cylindre
	float a;//coefficient dune equation de degree 2 
	float b;//coefficient dune equation de degree 2 
	float c;//coefficient dune equation de degree 2 
	float delta;//le discrimant de l'équation du second degré
	float t1;//racine de lequation
	float t2;//racine de lequation
	int booleen;//booleen pour savoir si il y a intersection ou non
	vecteur4 rayTransfoOrigine;
	vecteur4 rayTransfoDirecteur;
	vecteur4 normalTransfo;	//vecteur permettant le produit matricielle entre le vecteur normale et la matrice transformation
	vecteur4 intersectCylindre4;//vecteur permettant le produit matricielle entre le vecteur intersection et la matrice transformation
	
	booleen =0;
	
	//opérations sur les transformations 
	//on creer des vecteurs de dimension 4 avec les coordonnees des vecteurs du rayon
	rayTransfoOrigine = vector4(ray.origine.x,ray.origine.y,ray.origine.z,1);
	rayTransfoDirecteur = vector4(ray.vectDir.x,ray.vectDir.y,ray.vectDir.z,0);
	//on le multiplie a la matrice pour le transformer
	rayTransfoOrigine = produitMatriceNonCarree(cylindre.matriceTransfoInverse,rayTransfoOrigine,4);
	rayTransfoDirecteur = produitMatriceNonCarree(cylindre.matriceTransfoInverse,rayTransfoDirecteur,4);
	//on initialise les coordonnees du rayon avec le nouveau rayon transformer
	ray.origine = vector(rayTransfoOrigine.x,rayTransfoOrigine.y,rayTransfoOrigine.z);
	ray.vectDir = vector(rayTransfoDirecteur.x,rayTransfoDirecteur.y,rayTransfoDirecteur.z);
	
	
	//calcules des variables avec le nouveau rayon
	a=ray.vectDir.y*ray.vectDir.y+ray.vectDir.z*ray.vectDir.z;
	b=2*(ray.vectDir.y*ray.origine.y+ray.vectDir.z*ray.origine.z);
	c=ray.origine.y*ray.origine.y+ray.origine.z*ray.origine.z-cylindre.rayon*cylindre.rayon;
	//calcul du delta
	delta=b*b-4*a*c;
	
	//si le delta est negatif aucune solution donc pas intersection
	if(delta<0){
		//si on est sur la face superieur
		if((ray.origine.y*ray.origine.y +ray.origine.z*ray.origine.z) < cylindre.rayon*cylindre.rayon ){
			//si le x vérifie ces conditions
			if(ray.origine.x > 0.5 || (ray.origine.x >=-0.5 && ray.origine.x < 0.5)){
				//intersection avec un plan
				if(ray.vectDir.x!=0){
					//on initialise le t
					*t = ( 0.5 - ray.origine.x) / ray.vectDir.x;
					//si le t est strictement positif
					if(*t>0.000001){
						//booleen est vrai car il y a intersection
						booleen=1;
						//on initialise lintersection
						*intersection=opPlus(ray.origine, opProduitScalaire(ray.vectDir, *t));
					}
				}	
			}
			//si on est sur la face inferieur
			else if(ray.origine.x <-0.5 || (ray.origine.x >-0.5 && ray.origine.x <= 0.5)){
				//intersection avec un plan
				if(ray.vectDir.x!=0){
					//on initialise le t
					*t = (-0.5 - ray.origine.x) / ray.vectDir.x;
					//si le t est strictement superieur
					if(*t>0.000001){
						//booleen est vrai car il y a intersection
						booleen =1;
						//on initialise lintersection
						*intersection=opPlus(ray.origine, opProduitScalaire(ray.vectDir, *t));
						
					}
				}	
			
			}
		}
		
	}
	//si delta=0 alors une solution le rayon est tangent au cylindre
	else if(delta==0){
		//calcul de la racine et de lintersection correspondante
		*t=-b/(2*a);
		//calcul du point dintersection
		*intersection=opPlus(ray.origine, opProduitScalaire(ray.vectDir, *t));
		//il y a intersection
		booleen=1;
	}
	//si le delta est positif
	else if(delta>0){
		//calcul des deux racines 
		t1=(-b+sqrt(delta))/(2*a);
		t2=(-b-sqrt(delta))/(2*a);
		//si lune de ces conditions sont vérifiés alors le t prend la valeur correspondante
		if((t1<=t2 && t1>0.000001) || (t2<t1 && t2<0.000001)){
			*t=t1;
		}
		else{
			*t=t2;
		}
		//on initialise lintersection
		*intersection=opPlus(ray.origine, opProduitScalaire(ray.vectDir, *t));
		//il y a intersection
		booleen=1;

		//si on est sur la face superieure du cylindre
		if ((*intersection).x < -0.5 || (ray.origine.x < -0.5 && (ray.origine.y*ray.origine.y +ray.origine.z*ray.origine.z) <= cylindre.rayon*cylindre.rayon )){
			//intersection avec un plan
		 	if(ray.vectDir.x!=0){
		 		//on initialise le t	
				*t = (-0.5-ray.origine.x) / ray.vectDir.x;
				//on initialise lintersection
				*intersection=opPlus(ray.origine, opProduitScalaire(ray.vectDir, *t));
				//si ces conditions sont vérifiées
				if(*t>0.000001 && (((*intersection).y*(*intersection).y +(*intersection).z*(*intersection).z) <= cylindre.rayon*cylindre.rayon)){
					//il y a intersection
					booleen =1;
				}
				else{
					//il n y a pas dintersection
					booleen = 0;
				}
			}
			else{
				//il n y a pas dintersection
				booleen =0;
			}	
		//si on est sur la face inferieure du cylindre	
		}else if ((*intersection).x >0.5 || (ray.origine.x > 0.5 && (ray.origine.y*ray.origine.y +ray.origine.z*ray.origine.z) <= cylindre.rayon*cylindre.rayon )){
		 	if(ray.vectDir.x!=0){
		 		//on initialise le t
				*t = ( 0.5 - ray.origine.x) / ray.vectDir.x;
				//on initialise lintersection
				*intersection=opPlus(ray.origine, opProduitScalaire(ray.vectDir, *t));
				if(*t>0.000001 && (((*intersection).y*(*intersection).y +(*intersection).z*(*intersection).z) <= cylindre.rayon*cylindre.rayon)){
					//il y a intersection
					booleen =1;
						
				}
				else{
					//il n y a pas dintersection
					booleen =0;
				}
			}
			else{
				//il n y a pas dintersection
				booleen =0;
			}	
		 }
	}
	
	//calcul de la normal			
	//on se trouve sur le coté du cylindre
      	if(((*intersection).x >=(-0.5+0.000001)) && ((*intersection).x <= (0.5-0.000001))){
      		*normale = vector(0,(*intersection).y/0.5,(*intersection).z/0.5);
      	}
      	//on se trouve sur la face inférieur du cylindre			
        else if ((*intersection).x <= -0.49999999 && ((*intersection).x >= -0.59999999)){
    		*normale = vector(-1,0,0);
    	}
    	//on se trouve sur la face supérieur du cylindre
    	else if ((*intersection).x <= (0.5 + 0.0000001) && (*intersection).x >= (0.5 - 0.0000001)){
      		*normale = vector(1,0,0);
    	}
    	//sinon
    	else{
    		*normale=vector(0,0,1);
    	}
	
	//on change la valeur de l'intersection	et de la normale
	
	//on calcule l'intersection transformé
	intersectCylindre4 = opPlus4(rayTransfoOrigine, opProduitScalaire4(rayTransfoDirecteur, *t));
	intersectCylindre4 = produitMatriceNonCarree(cylindre.matriceTransfo, intersectCylindre4,4);
	*intersection = vector(intersectCylindre4.x, intersectCylindre4.y, intersectCylindre4.z);
	//on calcul la normale transformé
	normalTransfo = vector4((*normale).x, (*normale).y, (*normale).z,0);
	normalTransfo = produitMatriceNonCarree(cylindre.matriceTransfo, normalTransfo,4);
	*normale=vector(normalTransfo.x, normalTransfo.y, normalTransfo.z);
	*normale = normaliser(*normale);
			
	//on retourne le booleen
	return booleen;
}
