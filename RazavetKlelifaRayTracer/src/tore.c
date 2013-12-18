/* \file tore.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date 11/12/10
 * 
 * \brief Fonction de calculer lintersection avec un tore
 *
 *
 */

//Inclusion des entetes de librairie
#include "tore.h"


//calcule l'intersection entre un rayon et un cylindre
int intersectTore(rayon ray, torus tore, float* t, vecteur* intersection, vecteur* normale){
	//déclaration des variables
	int booleen;
	double a;//une inconnue de l'équation de degree 4
	double b;//une inconnue de l'équation de degree 4
	double c;//une inconnue de l'équation de degree 4
	double d;//une inconnue de l'équation de degree 4
	double e;//une inconnue de l'équation de degree 4
	double double_alpha;//variables qui stocke une partie des inconnues
	double double_beta;//variables qui stocke une partie des inconnues
	double double_teta;//variables qui stocke une partie des inconnues
	
	double p;//des inconnues intermediaires pour resolution equation de degrees 4
	double q;//des inconnues intermediaires pour resolution equation de degrees 4
	double r;//des inconnues intermediaires pour resolution equation de degrees 4
	double u;//des inconnues intermediaires pour resolution equation de degrees 4
	double v;//des inconnues intermediaires pour resolution equation de degrees 4
	double p2;//des inconnues intermediaires pour resolution equation de degrees 4
	double q2;//des inconnues intermediaires pour resolution equation de degrees 4
	
	double deltaprime;//des deltas intermediaires pour trouver les racines et donc les t possibles
	double delta1;//un delta dune equation de degree 2
	double delta2;//un delta dune equation de degree 2
	double z1;//racine intermédiaire
	
	double z2;//racine intermédiaire
	double z3;//racine intermédiaire
	double z4;//racine intermédiaire
	double y0;//racine intermédiaire
	
	double double_solution[4];//tableau de solutions possibles
	int int_i;//un compteur
	
	float float_var;//variable temporaire pr la normale
	vecteur4 rayTransfoOrigine;//declare un vecteur pour les transformations
	vecteur4 rayTransfoDirecteur;//declare un vecteur pour les transformations
	vecteur4 normalTransfo;	//vecteur permettant le produit matricielle entre le vecteur normale et la matrice transformation
	vecteur4 intersectTore4;//vecteur permettant le produit matricielle entre le vecteur intersection et la matrice transformation
	
	//initialisation des variables
	booleen =0;
	
	//opérations sur les transformations
	//on creer des vecteurs de dimension 4 avec les coordonnees des vecteurs du rayon
	rayTransfoOrigine = vector4(ray.origine.x,ray.origine.y,ray.origine.z,1);
	rayTransfoDirecteur = vector4(ray.vectDir.x,ray.vectDir.y,ray.vectDir.z,0);
	//on le multiplie a la matrice pour le transformer
	rayTransfoOrigine = produitMatriceNonCarree(tore.matriceTransfoInverse,rayTransfoOrigine,4);
	rayTransfoDirecteur = produitMatriceNonCarree(tore.matriceTransfoInverse,rayTransfoDirecteur,4);
	//on initialise les coordonnees du rayon avec le nouveau rayon transformer
	ray.origine = vector(rayTransfoOrigine.x,rayTransfoOrigine.y,rayTransfoOrigine.z);
	ray.vectDir = vector(rayTransfoDirecteur.x,rayTransfoDirecteur.y,rayTransfoDirecteur.z);
		
	//on initialise le tableau de solution
	for(int_i=0;int_i<4;int_i++){
		double_solution[int_i]=0;
	}	
	
	//initialisation des variables
	booleen=0;
	z1=0;
	z2=0;
	z3=0;
	z4=0;
	deltaprime=-1;
	delta1=-1;
	delta2=-1;
	u=0;
	v=0;
	p=0;
	q=0;
	r=0;
	p2=0;
	q2=0;
	int_i=0;
	//initialisation des variables permettant davoir les coefficients de lequation
	double_alpha=dot(ray.vectDir, ray.vectDir);
	double_beta=2*dot(ray.origine, ray.vectDir);
	double_teta=dot(ray.origine, ray.origine)-tore.rayon1*tore.rayon1-tore.rayon2*tore.rayon2;
	//nos coefficients
	a=double_alpha*double_alpha;
	b=2*double_alpha*double_beta;
	c=double_beta*double_beta+2*double_alpha*double_teta+4*tore.rayon1*tore.rayon1*ray.vectDir.z*ray.vectDir.z;
	d=2*double_beta*double_teta+8*tore.rayon1*tore.rayon1*ray.vectDir.z*ray.origine.z;
	e=double_teta*double_teta+4*tore.rayon1*tore.rayon1*ray.origine.z*ray.origine.z-4*tore.rayon2*tore.rayon2*tore.rayon1*tore.rayon1;
	
	//valeur maximale 
	*t=MAXFLOAT;

	//initialisation de variables intermediaires
	p=-(3*b*b/(8*a*a))+c/a;
	q=((b/2)*(b/2)*(b/2))/(a*a*a)-(0.5*b*c)/(a*a)+d/a;
	r=-3*((b/4)/a)*((b/4)/a)*((b/4)/a)*((b/4)/a)+c*(((b/4)*(b/4))/(a*a*a))-(0.25*b*d)/(a*a)+e/a;
	p2=-p*p/12-r;
	q2=-(p*p*p)/108+p*r/3-(q*q)/8;
	deltaprime=q2*q2+0.148148148*p2*p2*p2;
	
	//on ne prend que les racines réelles
	if(deltaprime>0 || deltaprime==0){
		//on stocke deux racines de lequation de degree 3
		u=cbrt((-q2+sqrt(deltaprime))/2);
		v=cbrt((-q2-sqrt(deltaprime))/2);
		//variables intermediaire pour equation de degree 2
		y0=u+v+(p/6);
		//si cette condition est verifiee alors il y a intersection et on stocke les valeurs des racines
		if((2*y0-p)==0){
			z1=sqrt(-y0);
			z2=-sqrt(-y0);
			//on initialise les variables restantes a une valeur tres petite pour ne pas quelles puissent etre le t minimale
			z3=-100;
			z4=-100;
			booleen=1;
		}
		//sinon il y a egalement intersection mais il y a plusieurs cas possibles
		else{
			booleen=1;
			//on calcule les deux deltas des equation de degree  resultantes de la methode de ferrari
			delta1=-2*y0-p-(2*q)/(sqrt(2*y0-p));
			delta2=-2*y0-p+(2*q)/(sqrt(2*y0-p));
			//si le rayon traverse le tore en 4 points
			if(delta1>0 && delta2>0){
				z1=(sqrt(2*y0-p)-sqrt(delta1))/2;
				z2=(sqrt(2*y0-p)+sqrt(delta1))/2;
				z3=(-sqrt(2*y0-p)-sqrt(delta2))/2;
				z4=(-sqrt(2*y0-p)+sqrt(delta2))/2;
			}
			//si le rayon traverse le tore en trois points et il est tangent au bord interne pour l’un des points
			else if(delta1>0 && delta2==0){
				z1=(sqrt(2*y0-p)-sqrt(delta1))/2;
				z2=(sqrt(2*y0-p)+sqrt(delta1))/2;
				z3=-sqrt(2*y0-p)/2;
				z4=-100;
			}
			else if(delta1==0 && delta2>0){
				z1=sqrt(2*y0-p)/2;
				z2=-100;
				z3=(-sqrt(2*y0-p)-sqrt(delta2))/2;
				z4=(-sqrt(2*y0-p)+sqrt(delta2))/2;
			}
			//si le rayon traverse le tore en deux points 
			else if(delta1>0 && delta2<0){
				z1=(sqrt(2*y0-p)-sqrt(delta1))/2;
				z2=(sqrt(2*y0-p)+sqrt(delta1))/2;
				z3=-100;
				z4=-100;
			}
			else if(delta1==0 && delta2==0){
				z1=sqrt(2*y0-p)/2;
				z2=-100;
				z3=-sqrt(2*y0-p)/2;
				z4=-100;
			}
			else if(delta1<0 && delta2>0){
				z1=-100;
				z2=-100;	
				z3=(-sqrt(2*y0-p)-sqrt(delta2))/2;
				z4=(-sqrt(2*y0-p)+sqrt(delta2))/2;	
			}
			//si le rayon est tangent à l’extèrieur du tore au point
			else if(delta1==0 && delta2<0){
				z1=sqrt(2*y0-p)/2;
				z2=-100;
				z3=-100;
				z4=-100;
			}
			else if(delta1<0 && delta2==0){
				z1=-100;
				z2=-100;
				z3=-sqrt(2*y0-p)/2;
				z4=-100;
			}
			//si le rayon ne traverse pas le tore
			else if(delta1<0 && delta2<0){
				z1=-100;
				z2=-100;
				z3=-100;
				z4=-100;
				booleen=0;
			}
		}
	}
	//sinon il n'y a pas intersection
	else{
		booleen=0;
	}
	
	//si il y a intersection
	if(booleen){
		//on stocke les solutions finales (apres chgt de variables)
		double_solution[0]=z1-b/(4*a);
		double_solution[1]=z2-b/(4*a);
		double_solution[2]=z3-b/(4*a);
		double_solution[3]=z4-b/(4*a);
		//boucle for pour parcourir le tableau
		for(int_i=0;int_i<4;int_i++){
			//si la racine en question est strictement superieur a epsilon et inferieur aux autres raicines
			if(double_solution[int_i]>0.0000001 && double_solution[int_i]<*t){
				//on stocke la racine 
				*t=double_solution[int_i];
			}
		}
	
		//on calcule lintersection grace a la racine t calculee	
		(*intersection) = opPlus(ray.origine, opProduitScalaire(ray.vectDir, *t));
		}
		
		//initialisation dune variable temporaire
		float_var=pow((*intersection).x,2)+pow((*intersection).y,2)+pow((*intersection).z,2)-pow(tore.rayon1,2)-pow(tore.rayon2,2);
		//calcul de la normal du tore au point dintersection
		(*normale).x=4*(*intersection).x*float_var;
		(*normale).y=4*(*intersection).y*float_var;
		(*normale).z=4*(*intersection).z*float_var+8*pow(tore.rayon1,2)*(*intersection).z;
		
	//on change la valeur de l'intersection	et de la normale
	
	//on calcule l'intersection transformé
	intersectTore4 = opPlus4(rayTransfoOrigine, opProduitScalaire4(rayTransfoDirecteur, *t));
	intersectTore4 = produitMatriceNonCarree(tore.matriceTransfo, intersectTore4,4);
	*intersection = vector(intersectTore4.x, intersectTore4.y, intersectTore4.z);
	//on calcul la normale transformé
	normalTransfo = vector4((*normale).x, (*normale).y, (*normale).z,0);
	normalTransfo = produitMatriceNonCarree(tore.matriceTransfo, normalTransfo,4);
	(*normale)=vector(normalTransfo.x, normalTransfo.y, normalTransfo.z);
	(*normale) = normaliser(*normale);
	
	
	//on retourne le booleen
	return (booleen);
	
}
