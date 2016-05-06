#include <stdlib.h>
#include <stdio.h>
#include "listePersonne.h"

struct personne_base {
	int priorite;
	char* nom;
	char* prenom;
	int id1; // identifiant choix 1
	int id2; // identifiant choix 2
	char* tabChxOrg1[6];
	char* tabChxOrg2[6];
	char* tabChxLib[6];
	int chxFin; // entier qui indique le choix attribu� � la fin � l'individu (0 : chxLib; 1 : chxOrg1 ; 2 : chxOrg2)
};

struct liste_personne_base {
	personne val;
	liste_personne next;
};

liste_personne creer_liste_personne()
{
	return NULL;
}

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
	@ensures : si per est pr�sente dans *listPer, retire per de *listPer et retourne 0;
			   sinon, retourne -1; */
int retirer_liste_personne(liste_personne* listPer, personne toRemove)
{
	if (listPer == NULL) { exit(EXIT_FAILURE); }

	if (!(*listPer == NULL)) /* si *listPer est non vide */
	{
		liste_personne curLink = *listPer;
		
		if (curLink->val == toRemove) /* si toRemove se trouve en t�te de *listPer */
		{ 
			*listPer = curLink->next; /* alors r�affecter la t�te de *listPer au cha�non suivant */
			free(curLink); /* et lib�rer l'espace occup� par la t�te pr�c�dente de la liste */
			
			if (*listPer == NULL) { free(listPer); } /* si la liste se retrouve vide, lib�rer l'espace qu'elle occupe */

			return 0;
		}
		else /* si toRemove ne se trouve pas en t�te de *listPer */
		{
			while (curLink->next != NULL) /* parcours de *listPer */
			{
				if (curLink->next->val == toRemove) /* si toRemove est la valeur du cha�non suivant */
				{
					liste_personne toDisappear = curLink->next;
					curLink->next = toDisappear->next; /* alors r�affecter le cha�non suivant � celui qui suit */
					free(toDisappear); /* et lib�rer l'espace occup� par le cha�non de valeur toRemove */
					
					return 0;
				}
				else { curLink = curLink->next; }
			} /* boucle n�cessairement car curLink->next devient forc�ment NULL si toRemove n'a pas �t� trouv� */
			return -1;
		}
	}
	else /* if (*listPer == NULL) [en principe, ce cas n'arrive jamais si seule cette fonction de retrait est utilis�e] */ 
	{
		free(listPer);
		return -1;
	}
}
