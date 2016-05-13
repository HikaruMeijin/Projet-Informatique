#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tas.h"

#define TailleTableau 256

tas creer_tas() {
	tas t = (tas) malloc(sizeof(struct tas_base));
	if(t == NULL) exit(EXIT_FAILURE);
	
	t->tableau = (personne*) malloc((TailleTableau+1)*sizeof(personne)); // Création du tableau de personnes
	if(t->tableau == NULL) exit(EXIT_FAILURE);

	int i;
	for(i=0 ; i < TailleTableau+1 ; i++ ) t->tableau[i] = NULL ; // Initialisation des personnes 
	t->prochain_vide = 0; // Indice du dernier élément
	return t;
}

int tas_vide(tas t){
	return t->prochain_vide==0; //Vérifie qu'il n'y ait aucunes personnes dans le tas (dans le cas contraire, prochain_vide > 0)
}

void inserer_tas(tas* t, personne p){
	int n = (*t)->prochain_vide;
	(*t)->tableau[n]=p;
	(*t)->prochain_vide=(*t)->prochain_vide+1; // Mise à jour pour le dernier élément
	reorganiser_tas_inserer(t); // S'assure que la propriété du tas est conservée
}

personne retirer_tas(tas* t){
	int n = (*t)->prochain_vide;
	personne prio = (*t)->tableau[0]; // Ces lignes inversent les personnes des indices n et 0
	(*t)->tableau[0] = (*t)->tableau[n-1];
	(*t)->tableau[n-1] = NULL;
	(*t)->prochain_vide=(*t)->prochain_vide-1; // Mise à jour pourr le dernier élément
	reorganiser_tas_retirer(t); // S'assure que la propriété du tas est conservée
	return prio;
}

void echanger_racine_fd(tas* t, int i){
	personne tmp = (*t)->tableau[i]; // Echange dans le cas où on devrait inverser avec le fils droit
	(*t)->tableau[i] = (*t)->tableau[2*i+2];
	(*t)->tableau[2*i+2] = tmp;
}

void echanger_racine_fg(tas* t, int i){
	personne tmp = (*t)->tableau[i]; // Echange dans le cas où on devrait inverser avec le fils gauche
	(*t)->tableau[i] = (*t)->tableau[2*i+1];
	(*t)->tableau[2*i+1] = tmp;
}

int personne_priorite(tas* t, int ind){
	return ((*t)->tableau[ind])->priorite;
}

void reorganiser_tas_retirer(tas* t){
	int i=0;
	while(i < 100){ // S'assurer que l'on ne dépasse pas les 200 éléments 
		if((*t)->tableau[i]!=NULL){
			if((*t)->tableau[2*i+2]==NULL){ // Si pas de fils droit
				if((*t)->tableau[2*i+1]==NULL) break;
				else{ // Si le fils gauche existe
					if (personne_priorite(t, i) < personne_priorite(t, 2*i+1)){
						echanger_racine_fg(t,i); // Si le fils gauche a une plus grande priorité que la racine
						i=2*i+1;
					}
					else break; // Si la personne se trouvant à la racine a une plus grande priorité, on quitte la boucle
				}
			}
			else {
				if(personne_priorite(t, 2*i+1) >= personne_priorite(t, 2*i+2)){ 
					if (personne_priorite(t, i) < personne_priorite(t, 2*i+1)) {
						echanger_racine_fg(t,i); // Si le fils gauche a une plus grande priorité que la racine
						i=2*i+1;
					}
					else break; // Si la personne se trouvant à la racine a une plus grande priorité, on quitte la boucle
				}
				else {
					if (personne_priorite(t, i) < personne_priorite(t, 2*i+2)) {
						echanger_racine_fd(t,i); // Si le fils droit a une plus grande priorité que la racine
						i=2*i+2;
					}
					else break; // Si la personne se trouvant à la racine a une plus grande priorité, on quitte la boucle
				}
			}
		}
		else break;
	}
}

int est_pair(int ind){
	if(ind % 2 == 0) return 1;
	else return 0;
}

void reorganiser_tas_inserer(tas* t){
	int i=(*t)->prochain_vide-1;
	int j=0;
	double k = 0.0;
	while(i != 0){ // S'assurer que l'on atteigne bien l'élément 0
		k = (double) i/2 ;
		if(est_pair(i) == 0){ // Si l'indice considéré est impair (il n'y a donc pas de fils droit)
			j = (int) floor(k); // Permet d'obtenir l'indice auquel se trouve la racine associée
			if (personne_priorite(t, j) < personne_priorite(t, i)){
				echanger_racine_fg(t,j); // Si le fils gauche a une plus grande priorité que la racine
				i=j;
			}
			else break; // Si la personne se trouvant à la racine a une plus grande priorité, on quitte la boucle
		}
		else { // Si l'indice est pair (il y a alors deux fils)
			if(personne_priorite(t, i-1) >= personne_priorite(t, i)) break; // Si le fils gauche a une priorité plus petite que le fils droit, aucuns changements à apporter
			else {
				j=(int) floor(k);
				j--; // Permet d'obtenir l'indice auquel se trouve la racine associée
				if (personne_priorite(t, j) < personne_priorite(t, i)) {
					echanger_racine_fd(t,j); // Si le fils droit a une plus grande priorité que la racine
					i=j;
				}
				else break; // Si la personne se trouvant à l'élément rajouté a une plus petite priorité, on quitte la boucle
			}
		}
	}
}

void liberer_tas(tas* t){
	if(tas_vide(*t)) free((*t)->tableau); // Ne libère le tas que s'il n'y a aucuns éléments dans le tas
}
