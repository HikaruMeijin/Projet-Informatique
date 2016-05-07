#include <stdlib.h>
#include <stdio.h>
#include "listePlanete.h"

liste_planete creer_liste_planete()
{
	return NULL;
}

/*	@requires : une liste de planete valide
	@assigns : nothing
	@ensures : retourne 1 si la liste est vide et 0 sinon */
int liste_planete_vide(liste_planete listPla)
{
	return listPla == NULL ;
}

/*	@requires : pointeur sur liste de planete et une planete valides
	@assigns : la liste de planete
	@ensures : la planete a ete inseree en tete de liste */

liste_planete consPla(liste_planete d, planete v)
{
  liste_planete r = (liste_planete) malloc(sizeof(struct liste_planete_base)) ;
  r->val = v ;
  r->next = d ;
  return r ;
}

void inserer_liste_planete(liste_planete * d, planete v)
{
  *d = consPla(*d,v) ;
}
