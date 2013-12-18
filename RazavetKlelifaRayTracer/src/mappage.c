/* \file LectureFichier.c
 * \author Razavet Mael, Klelifa Sarah
 * \version 0.1
 * \date mond oct 11
 * 
 * \brief Permet de mapper un fichier en mémoire
 *
 *
 */

//Inclusion des entêtes de librairie
#include "mappage.h"

//fonction qui permet de mapper un fichier en mémoire
int ouvre(char* chemin_fichier, int x, int y,objet* obj, objetCSG* objetcsg, listeIntersection* lIntersection){
	//déclaration des varibles
        int fd; // Notre File Descriptor
        struct stat buf;//nouvelle structure
        char* buffer;

	if (-1 == (fd = open(chemin_fichier, O_RDWR))) // Ouverture en lecture et écriture
   	{
      		perror("open() "); // perror affichera un message indiquant la cause de l'erreur
      		exit(EXIT_FAILURE); // sortir du programme
  	}


        if (-1 == stat(chemin_fichier, &buf)) // Obtention de la taille, on passe l'adresse de buf car la fonction attend un pointeur!
        {
                perror("stat() ");
                close(fd); // Fermeture du fichier
                exit(EXIT_FAILURE); // Si erreur on sort
        }
         
	//initialisation du buffer pour mapper le fichier
        buffer = (char*)mmap(0, (int)buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
 
 
	if ((char*)-1 == buffer)
        {
                perror("mmap() ");
                close(fd); // Fermeture du fichier
                exit(EXIT_FAILURE);
        }
 	close(fd); // Fermeture du fichier

 	//On lit puis stockes les données du fichier
	LectureFichier(obj, buffer,(int)buf.st_size, objetcsg, lIntersection);


	return (EXIT_SUCCESS);
}
