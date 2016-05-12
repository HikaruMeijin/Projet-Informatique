#include <stdlib.h>
#include <stdio.h>
#include "listePlanete.h"

/*	@requires : nothing
	@assigns : nothing
	@ensures : retourne une planete */
planete creer_planete()
{
	planete pla = (planete) malloc(sizeof(struct planete_base)); /* on alloue dynamiquement la m�moire n�cessaire pour la planete 'pla' que l'on cr�e */
	if (pla == NULL) { exit(EXIT_FAILURE); } /* si notre allocation m�moire a �chou�, on arr�te l'ex�cution du programme */

	return pla; /* l'allocation a r�ussi, on retourne pla */
}

/*	@requires : nothing
	@assigns : nothing
	@ensures : retourne une liste de planete vide */
liste_planete creer_liste_planete()
{
	return NULL;
}

/*	@requires : une liste de planete valide
	@assigns : nothing
	@ensures : retourne 1 si la liste est vide et 0 sinon */
int liste_planete_vide(liste_planete listPla)
{
	return listPla == NULL;
}

/*	@requires : pointeur sur liste de planete et une planete valides
	@assigns : la liste de planete
	@ensures : la planete a ete inseree en tete de liste */
void inserer_liste_planete(liste_planete* listPla, planete pla)
{
	if (listPla == NULL) { exit(EXIT_FAILURE); }

	liste_planete newLink = (liste_planete) malloc(sizeof(struct liste_planete_base)); /* allocation dynamique pour le nouveau maillon que l'on va ins�rer dans *listPla */
	if (newLink == NULL) { exit(EXIT_FAILURE); } /* si notre allocation m�moire a �chou�, on arr�te l'ex�cution du programme */

	newLink->val = pla; /* le nouveau maillon prend la valeur pla */
	newLink->next = *listPla;

	*listPla = newLink; /* newLink devient la nouvelle t�te de notre liste */
}
