#ifndef LISTPLA_H
#define LISTPLA_H

typedef struct planete_base {
	char* nom;
	int nbPlaces; /* nombre de places restantes */
} * planete;

typedef struct liste_planete_base {
	planete val;
	struct liste_planete_base * next;
} * liste_planete;

/*	@requires : nothing
	@assigns : nothing
	@ensures : retourne une liste de planete vide */
liste_planete creer_liste_planete();

/*	@requires : une liste de planete valide
	@assigns : nothing
	@ensures : retourne 1 si la liste est vide et 0 sinon */
int liste_planete_vide(liste_planete);

/*	@requires : un pointeur sur liste de planete et une planete valides
	@assigns : la liste de planete
	@ensures : la planete a ete inseree en tete de liste */
void inserer_liste_planete(liste_planete*, planete);

# endif /* LISTPLA_H */
