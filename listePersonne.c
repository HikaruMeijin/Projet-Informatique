#include <stdlib.h>
#include <stdio.h>
#include "listePersonne.h"

/*	@requires : une liste de personne valide
	@assigns : nothing
	@ensures : retourne 1 si la liste est vide et 0 sinon */
int liste_personne_vide(liste_personne listPer)
{
	if (listPer == NULL) { return 1; }
	else /* if (listPer != NULL) */ { return 0; }
}

/*	@requires : pointeur sur liste de personne et une personne valides
	@assigns : la liste de personne
	@ensures : la personne a ete inseree en tete de liste */
void inserer_liste_personne(liste_personne* listPer, personne per)
{
	if (listPer == NULL) { exit(EXIT_FAILURE); }

	liste_personne newLink = malloc(sizeof(*newLink));
	if (newLink == NULL) { exit(EXIT_FAILURE); }

	newLink->val = per;
	newLink->next = *listPer;

	*listPer = newLink;
}

/*	@requires : personne toRemove non NULL et pointeur sur liste_personne valides
	@assigns : la liste de personnes *listPer
	@ensures : si per est présente dans *listPer, retire per de *listPer et retourne 0;
			   sinon, retourne -1; */
int retirer_liste_personne(liste_personne* listPer, personne toRemove)
{
	if (listPer == NULL) { exit(EXIT_FAILURE); }

	liste_personne* toModify = listPer;
	liste_personne curLink = *toModify;

	while (curLink != NULL && curLink->val != toRemove)
	{
		toModify = &curLink->next;
		curLink = *toModify;
	}

	if (curLink == NULL) { return -1; }

	*toModify = curLink->next;
	free(curLink);

	return 0;
}
