#ifndef CONVERSION_H_INCLUDED
#define CONVERSION_H_INCLUDED

#include "tas.h"
#include "liste_planete.h"
#include "liste_personne.h"

/*  @requires : f1 et f2 deux flux sur les fichiers des personnes (f1 = flux sur le tableau de priorite et f2 = flux sur le tableau desouhait)
    @assigns : nothing
    @ensures : retourne un tableau de personne avec les priorites et souhaits */
tas convertir_t_personne ( FILE * , FILE * ) ;

/*  @requires : fd un flux sur le fichier des zones
    @assigns : nothing
    @ensures : retourne le tableau de listes de planete */
liste_planete * convertir_t_planete ( FILE * ) ;

/*  @requires : fd un flux sur le fichier des contraintes
    @assigns : nothing
    @ensures : retourne le tableau des contraintes */
planete * convertir_contrainte (FILE * f)

 /* @requires : une personne et un flux sur un fichier
    @assigns : rajoute une ligne à file FILE
    @ensures : retourne 0 si la ligne a été ajoutée */
int ajout_ligne ( personne , FILE * ) ;

#endif // CONVERSION_H_INCLUDED
