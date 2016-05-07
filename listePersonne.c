#include <stdlib.h>
#include <stdio.h>
#include "listePersonne.h"


liste_personne creer_liste_personne()
{
  return NULL ;
}

liste_personne cons(liste_personne d, personne v)
{
  liste_personne r = (liste_personne) malloc(sizeof(struct liste_personne_base)) ;
  r->val = v ;
  r->next = d ;
  return r ;
}

int liste_personne_vide(liste_personne l)
{
	return l == NULL ;
}


void inserer_liste_personne(liste_personne * d, personne v)
{
  *d = cons(*d,v) ;
}

personne supprimer_liste_personne(liste_personne * d, personne v)
{
  if(*d)
    return NULL;
  if((*d)->val == v)
    {
      personne r =(*d)->val ;
      (*d) = (*d)->next ;
      return r;
    }
  liste_personne old = (*d) ;
  liste_personne curr = (*d) ;
  curr = curr->next ;
  while(curr)
    {
      if(curr->val == v)
	{
	  old->next = curr->next ;
	  personne r = curr->val ;
	  return r ;
	}
      else
	{
	  old=curr ;
	  curr = curr->next ;
	}
    }
  return NULL ;
}

void affiche(liste_personne d)
{
	while(d)
		{
			printf("%s %s : %s -> %s -> %s -> %s -> %s -> %s \n %s -> %s -> %s -> %s -> %s -> %s\n %s -> %s -> %s -> %s -> %s -> %s\n", d->val->nom, d->val->prenom, d->val->tabChxOrg1[0],d->val->tabChxOrg1[1],d->val->tabChxOrg1[2],d->val->tabChxOrg1[3],d->val->tabChxOrg1[4],d->val->tabChxOrg1[5],d->val->tabChxOrg2[0],d->val->tabChxOrg2[1],d->val->tabChxOrg2[2],d->val->tabChxOrg2[3],d->val->tabChxOrg2[4],d->val->tabChxOrg2[5],d->val->tabChxLib[0],d->val->tabChxLib[1],d->val->tabChxLib[2],d->val->tabChxLib[3],d->val->tabChxLib[4],d->val->tabChxLib[5]) ;
			d = d->next ;
		}
}

