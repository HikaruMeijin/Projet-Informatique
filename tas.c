#include "stdio.h"
#include "stdlib.h"
#include "tas.h"

#define Nbpersonnes 200

tas creer_tas() {
	tas tmp;
	tmp->tableau = malloc(Nbpersonnes*sizeof(personne)); // Création du tableau de personnes
	tmp->prochain_vide = 0; // Indice du dernier élément
	return tmp;
}

int tas_vide(tas t){
	return (*t)->prochain_vide==0;
}

void inserer_tas(tas* t, personne p){
	int n = (*t)->prochain_vide;
	(*t)->tableau[n]=p;
	(*t)->prochain_vide=(*t)->prochain_vide+1;
	reorganiser_tas(t); // S'assure que la propriété du tas est conservé
}

personne retirer_tas(tas* t){
	int n = (*t)->prochain_vide;
	personne prio = (*t)->tableau[0]; // Ces lignes inversent les valeurs en n et 0
	(*t)->tableau[0] = (*t)->tableau[n];
	(*t)->tableau[n] = NULL;
	(*t)->prochain_vide=(*t)->prochain_vide-1;
	reorganiser_tas(t);
	return prio;
}

void comparaison_priorite_fd(tas* t, int i){
	personne tmp = (*t)->tableau[i]; // Compare dans le cas où on devrait inverser avec le fils droit
	(*t)->tableau[i] = (*t)->tableau[2*i+2];
	(*t)->tableau[2*i+2] = tmp;
	i=2*i+2;
}

void comparaison_priorite_fg(tas* t, int i){
	personne tmp = (*t)->tableau[i]; // Compare dans le cas où on devrait inverser avec le fils gauche
	(*t)->tableau[i] = (*t)->tableau[2*i+1];
	(*t)->tableau[2*i+1] = tmp;
	i=2*i+1;
}

int personne_priorite(tas* t, int ind){
	return ((*t)->tableau[ind])->priorite;
}

void reorganiser_tas(tas* t){
	int i=0;
	while(i < Nbpersonnes/2){ // S'assurer que l'on ne dépasse pas les 200 éléments 
		if((*t)->tableau[2*i+1]==NULL){ //Si pas de fils gauche
			if((*t)->tableau[2*i+2]==NULL) break; 
			else{ // Si le fils droit existe
				if (personne_priorite(t, i) < personne_priorite(t, 2*i+2)) comparaison_priorite_fd(t,i);
				else break;
			}
		}
		else if((*t)->tableau[2*i+2]==NULL){ // Si pas de fils droit
			if((*t)->tableau[2*i+1]==NULL) break;
			else{ // Si le fils gauche existe
				if (personne_priorite(t, i) < personne_priorite(t, 2*i+1)) comparaison_priorite_fg(t,i);
				else break;
			}
		}
		else {
			if(personne_priorite(t, 2*i+1) >= personne_priorite(t, 2*i+2)){ 
				if (personne_priorite(t, i) < personne_priorite(t, 2*i+1)) comparaison_priorite_fg(t,i);
				else break; // Si le fils gauche est plus petit que la racine
			}
			else {
				if (personne_priorite(t, i) < personne_priorite(t, 2*i+2)) comparaison_priorite_fd(t,i);
				else break; // Si le fils droit est plus petit que la racine
			}
		}
	}
}

void liberer_tas(tas* t){
	if(tas_vide(*t)) free((*t)->tableau); // Ne libère le tas que s'il n'y a aucuns éléments dans le tableau
}