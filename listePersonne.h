#ifndef LISTPER_H
#define LISTPER_H

typedef struct personne_base {
	int priorite;
	char* nom;
	char* prenom;
	int id1; /* identifiant choix 1 */
	int id2; /* identifiant choix 2 */
	char* tabChxOrg1[6]; /* tableau correspondant au 1er choix de voyage pre-orgarnise de la personne */
	char* tabChxOrg2[6]; /* tableau correspondant � son 2nd voeu de voyage de type pre-organise */
	char* tabChxLib[6]; /* tableau contenant les choix de la personne dans le cas d'un parcours libre */
	int assigned[6];  /* tableau qui indique les zones assign�es de mani�re d�finitive au voyageur */
	int chxFin; /* entier qui indique le choix attribu� � la fin � l'individu (1 : chxOrg1 ; 2 : chxOrg2 ; 3 : chxLib) */
} * personne;

typedef struct liste_personne_base {
	personne val;
	struct liste_personne_base * next;
} * liste_personne;

/*	@requires : nothing
	@assigns : nothing
	@ensures : retourne une personne */
personne creer_personne();

/*	@requires : nothing
	@assigns : nothing
	@ensures : retourne une liste de personne vide */
liste_personne creer_liste_personne();

/*	@requires : une liste de personne valide
	@assigns : nothing
	@ensures : retourne 1 si la liste est vide et 0 sinon */
int liste_personne_vide(liste_personne);

/*	@requires : pointeur sur liste de personne valide et une personne valide, non pr�sente dans la liste
	@assigns : la liste de personne
	@ensures : la personne a ete inseree en tete de liste */
void inserer_liste_personne(liste_personne*, personne);

/*	@requires : pointeur sur liste de personne et personne valides
	@assigns : la liste de personne *listPer
	@ensures : si per est pr�sente dans *listPer, retire per de *listPer et retourne 0;
			   sinon, retourne -1; */
int retirer_liste_personne(liste_personne*, personne);

#endif /* LISTPER_H */