#include <stdlib.h>
#include <stdio.h>
#include "listePersonne.h"
#include "listePlanete.h"

int main()
{
    personne per1 = NULL, per2 = NULL;
    per1 = malloc(sizeof(struct personne_base));
    per2 = malloc(sizeof(struct personne_base));
    
    per1->nom = "Nono";
    
    per2->nom = "Nana";
    
    liste_personne listPer = creer_liste_personne();
    inserer_liste_personne(&listPer, per1);
    inserer_liste_personne(&listPer, per2);
    
    personne per[2] = {per1, per2};
    int i = 0;
    
    while(!liste_personne_vide(listPer))
    {
        printf("%s", listPer->val->nom);
        retirer_liste_personne(&listPer, per[i]);
        i++;
    }
}