#ifndef TAS_H
#define TAS_H

#include "listePersonne.h"
#include "listePlanete.h"

struct tas_base {
  personne* tableau;
  int prochain_vide;
};

typedef struct tas_base* tas;

/*@requires nothing
  @ensigns nothing
  @ensures retourne un tas vide */
tas creer_tas();

/*@requires tas valide
  @ensigns nothing
  @ensures retourne 1 si tas vide, O sinon */
int tas_vide(tas);

/*@requires pointeur sur tas et persone valide
  @ensigns tas
  @ensures personne insérée à la bonne place dans le tas*/
void inserer_tas(tas*, personne);

/*@requires pointeur sur tas valide
  @ensigns tas
  ensures retirer personne en conservant nature de tas */
personne retirer_tas(tas*);

/*@requires pointeur sur tas valide
  @ensigns nothing
  ensures compare la racine au fils droit et agit en consequence */
void comparaison_priorite_fd(tas*, int);

/*@requires pointeur sur tas valide
  @ensigns nothing
  ensures compare la racine au fils gauche et agit en consequence */
void comparaison_priorite_fg(tas*, int);

/*@requires pointeur sur tas valide
  @ensigns tas
  ensures rééquilibrer tas et conserver structure */
void reorganiser_tas(tas*);

/*@requires pointeur sur tas valide
  @ensigns tas
  ensures libérer la zone mémoire qssociée au tas */
void liberer_tas(tas*);

#endif // TAS_H