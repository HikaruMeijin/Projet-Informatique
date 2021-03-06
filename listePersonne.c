#include <stdlib.h>
#include <stdio.h>
#include "listePersonne.h"


/*	@requires : nothing
	@assigns : nothing
	@ensures : retourne une personne */
personne creer_personne()
{
	personne per = (personne) malloc(sizeof(struct personne_base)); /* on alloue dynamiquement de la m�moire pour la personne 'per' que l'on cr�e */
	if (per == NULL) { exit(EXIT_FAILURE); } /* si notre allocation m�moire a �chou�, on arr�te l'ex�cution du programme */

	int i;
	for (i = 0; i < 6; i++)
	{
		per->tabChxOrg1[i] = NULL;
		per->tabChxOrg2[i] = NULL;
		per->tabChxLib[i] = NULL;
		per->assigned[i] = 0;
	}
	per->chxFin = 0;

	return per; /* l'allocation a r�ussi, on retourne per */
}

/*	@requires : nothing
	@assigns : nothing
	@ensures : retourne une liste de personne vide */
liste_personne creer_liste_personne()
{
	return NULL;
}

/*	@requires : une liste de personne valide
	@assigns : nothing
	@ensures : retourne 1 si la liste est vide et 0 sinon */
int liste_personne_vide(liste_personne listPer)
{
	return listPer == NULL;
}

/*	@requires : pointeur sur liste de personne valide et une personne valide, non pr�sente dans la liste
	@assigns : la liste de personne
	@ensures : la personne a ete inseree en tete de liste */
void inserer_liste_personne(liste_personne* listPer, personne per)
{
	if (listPer == NULL) { exit(EXIT_FAILURE); }

	liste_personne newLink = (liste_personne) malloc(sizeof(struct liste_personne_base)); /* allocation dynamique pour le nouveau maillon que l'on va ins�rer dans *listPer */
	if (newLink == NULL) { exit(EXIT_FAILURE); } /* si notre allocation m�moire a �chou�, on arr�te l'ex�cution du programme */

	newLink->val = per; /* le nouveau maillon prend la valeur per */
	newLink->next = *listPer;

	*listPer = newLink; /* newLink devient la nouvelle t�te de notre liste */
}

/*	@requires : personne toRemove non NULL et pointeur sur liste_personne valides
	@assigns : la liste de personnes *listPer
	@ensures : si per est pr�sente dans *listPer, retire per de *listPer et retourne 0;
			   sinon, retourne -1; */
int retirer_liste_personne(liste_personne* listPer, personne toRemove)
{
	if (listPer == NULL) { exit(EXIT_FAILURE); } /* listPer == NULL ==> listPer invalide, donc on arr�te l'�x�cution du programme */

	if (liste_personne_vide(*listPer)) { return -1; } /* si *listPer est vide, alors on retourne �videmment -1 */

	liste_personne prevLink = *listPer;
	liste_personne curLink = prevLink->next;
	
	if (prevLink->val == toRemove) /* si la personne qu'on veut retirer (toRemove) est en t�te de *listPer */
	{
		*listPer = curLink; /* on r�affecte *listPer au maillon suivant */
		free(prevLink); /* puis on lib�re l'espace qu'occupait l'ancienne t�te de *listPer */
		return 0;
	}

	while (curLink != NULL) /* sinon, on parcourt *listPer tant que curLink est non NULL */
	{
		if (curLink->val == toRemove) /* si la valeur du maillon courant curLink est toRemove */
		{
			prevLink->next = curLink->next; /* le maillon suivant du maillon pr�c�dent devient le maillon suivant du maillon courant */
			free(curLink); /* on lib�re l'espace qu'occupait le maillon courant (celui de valeur toRemove) */
			return 0;
		}

		/* sinon, on continue d'avancer dans la liste : */
		prevLink = curLink; /* prevLink avance de 1 dans *listPer; */
		curLink = prevLink->next; /* curLink aussi. */
	}
	/* soit on trouve toRemove dans *ListPer et l'on retourne 0,
	   soit on continue d'avancer jusqu'� arriver en fin de *listPer et obtenir curLink == NULL,
	   donc, terminaison de la boucle while, OK */

	/* si curLink vaut NULL, fin de la boucle : toRemove n'�tait pas pr�sent dans *listPer */
	return -1; /* on retourne donc -1 */
}
