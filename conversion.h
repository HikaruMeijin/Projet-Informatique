#ifndef CONVERSION_H_INCLUDED
#define CONVERSION_H_INCLUDED

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "tas.h"
#include "listePlanete.h"
#include "listePersonne.h"

/*  @requires : f1 et f2 deux flux sur les fichiers des personnes (f1 = flux sur le tableau de priorite et f2 = flux sur le tableau de souhait)
    @assigns : nothing
    @ensures : retourne le tas où sont rangées toutes les personnes*/
tas convertir_t_personne ( FILE * , FILE * ) ; 

/*  @requires : fd un flux sur le fichier des zones
    @assigns : nothing
    @ensures : retourne le tableau de listes de planete */
liste_planete * convertir_t_planete( FILE * ) ;

/*  @requires : f un flux sur le fichier des contraintes, sizetab le nombre de ligne du fichier
    @assigns : nothing
    @ensures : retourne le tableau des contraintes */
char*** convertir_contrainte(FILE * f, int sizetab) ;

 /* @requires : une personne et un flux sur un fichier
    @assigns : rajoute une ligne au fichier
    @ensures : la ligne a été ajoutée */
void ajout_ligne ( personne , FILE * ) ;

/* @requires : un flux de fichier
   @assigns : nothing
   @ensures : retourne le nombre de lignes du fichier
*/
int nombreligne(FILE * f) ;

#endif // CONVERSION_H_INCLUDED
