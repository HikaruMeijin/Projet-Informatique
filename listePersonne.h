#ifndef LISTPER_H
#define LISTPER_H

typedef struct personne_base {

	int priorite;

	char* nom;

	char* prenom;

	int id1; // identifiant choix 1

	int id2; // identifiant choix 2

	char* tabChxOrg1[6];

	char* tabChxOrg2[6];

	char* tabChxLib[6];

	int chxFin; // entier qui indique le choix attribué à la fin à l'individu (0 : chxLib; 1 : chxOrg1 ; 2 : chxOrg2)
} * personne;

typedef struct liste_personne_base {
	personne val;

	struct liste_personne_base * next;
}  * liste_personne;

/*	@requires : nothing
	@assigns : nothing
	@ensures : retourne une liste de personne vide */
liste_personne creer_liste_personne();

/*	@requires : une liste de personne valide
	@assigns : nothing
	@ensures : retourne 1 si la liste est vide et 0 sinon */
int liste_personne_vide(liste_personne);

/*	@requires : pointeur sur liste de personne et une personne valides
	@assigns : la liste de personne
	@ensures : la personne a ete inseree en tete de liste */
void inserer_liste_personne(liste_personne*, personne);

/*	@requires : pointeur sur liste de personne et personne valides
	@assigns : la liste de personne *listPer
	@ensures : si per est présente dans *listPer, retire per de *listPer et retourne 0;
			   	 sinon, retourne  -1 */
int retirer_liste_personne(liste_personne*, personne);

void affiche(liste_personne) ;

#endif /* LISTPER_H */
