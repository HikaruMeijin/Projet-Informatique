#ifndef TAS_H
#define TAS_H

#include "listePersonne.h"
#include "listePlanete.h"

typedef struct tas_base {
  personne* tableau;
  int prochain_vide;
} * tas;

/*@requires nothing
  @ensigns nothing
  @ensures retourne un tas vide */
tas creer_tas();

/*@requires tas valide
  @ensigns nothing
  @ensures retourne 1 si tas vide, O sinon */
int tas_vide(tas);

/*@requires pointeur sur tas valide et persone valide, non présente dans le tas
  @ensigns tas
  @ensures personne insérée à la bonne place dans le tas*/
void inserer_tas(tas*, personne);

/*@requires pointeur sur tas valide
  @ensigns tas
  ensures retirer personne en conservant nature de tas */
personne retirer_tas(tas*);

/*@requires pointeur sur tas valide et indice valide
  @ensigns nothing
  ensures renvoi de la priorité de la personne concernée */
int personne_priorite(tas* , int );

/*@requires pointeur sur tas valide
  @ensigns nothing
  ensures échange la racine avec le fils droit */
void echanger_racine_fd(tas*, int);

/*@requires pointeur sur tas valide
  @ensigns nothing
  ensures échange la racine avec le fils gauche */
void echanger_racine_fg(tas*, int);

/*@requires pointeur sur tas valide
  @ensigns tas
  ensures rééquilibrer le tas et conserver sa structure */
void reorganiser_tas(tas*);

/*@requires pointeur sur tas valide
  @ensigns tas
  ensures libérer la zone mémoire associée au tas */
void liberer_tas(tas*);

#endif // TAS_H