#ifndef TAS_H
#define TAS_H

#include "listePersonne.h"

typedef struct tas_base {
  personne* tableau;
  int prochain_vide;
} * tas;

/*@requires nothing
  @assigns nothing
  @ensures retourne un tas vide */
tas creer_tas();

/*@requires tas valide
  @assigns nothing
  @ensures retourne 1 si tas vide, O sinon */
int tas_vide(tas);

/*@requires pointeur sur tas valide et persone valide, non présente dans le tas
  @assigns tas
  @ensures personne insérée à la bonne place dans le tas*/
void inserer_tas(tas*, personne);

/*@requires pointeur sur tas valide
  @assigns tas
  @ensures retirer personne en conservant nature de tas */
personne retirer_tas(tas*);

/*@requires pointeur sur tas valide et indice valide
  @assigns nothing
  @ensures renvoi de la priorité de la personne concernée */
int personne_priorite(tas* , int );

/*@requires pointeur sur tas valide
  @assigns tas
  @ensures échange la racine avec le fils droit */
void echanger_racine_fd(tas*, int i);

/*@requires pointeur sur tas valide
  @assigns tas
  @ensures échange la racine avec le fils gauche */
void echanger_racine_fg(tas*, int i);

/*@requires pointeur sur tas valide
  @assigns tas
  @ensures rééquilibrer le tas après retrait d'un élément et conserver sa structure */
void reorganiser_tas_retirer(tas*);

/*@requires indice valide
  @assigns nothing
  @ensures la parité de l'indice ind (retourne 1 si pair, 0 sinon) */
int est_pair(int ind);

/*@requires pointeur sur tas valide
  @assigns tas
  @ensures rééquilibrer le tas après ajout d'un élément et conserver sa structure */
void reorganiser_tas_inserer(tas* t);

/*@requires pointeur sur tas valide
  @assigns tas
  @ensures libérer la zone mémoire associée au tas */
void liberer_tas(tas*);

#endif // TAS_H
