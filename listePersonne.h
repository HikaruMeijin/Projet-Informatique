#ifndef LISTPER_H
#define LISTPER_H

typedef struct personne_base * personne;
typedef struct liste_personne_base * liste_personne;

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
	@assigns : la liste de personne
	@ensures : retire la personne de la liste */
personne retirer_liste_personne(liste_personne*, personne);

#endif /* LISTPER_H */