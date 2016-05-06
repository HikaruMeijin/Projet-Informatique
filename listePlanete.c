#include <stdlib.h>
#include <stdio.h>
#include "listePlanete.h"

struct planete_base {
	char* nom;
	int nbPlaces; /* nombre de places restantes */
};

struct liste_planete_base {
	planete val;
	liste_planete next;
};

liste_planete creer_liste_planete()
{
	return NULL;
}

/*	@requires : une liste de planete valide
	@assigns : nothing
	@ensures : retourne 1 si la liste est vide et 0 sinon */
int liste_planete_vide(liste_planete listPla)
{
	if (listPla == NULL) { return 1; }
	else /* if (listPla != NULL) */ { return 0; }
}

/*	@requires : pointeur sur liste de planete et une planete valides
	@assigns : la liste de planete
	@ensures : la planete a ete inseree en tete de liste */
void inserer_liste_planete(liste_planete* listPla, planete pla)
{
	if (listPla == NULL) { exit(EXIT_FAILURE); }

	liste_planete newLink = malloc(sizeof(*newLink));
	if (newLink == NULL) { exit(EXIT_FAILURE); }

	newLink->val = pla;
	newLink->next = *listPla;

	*listPla = newLink;
}
