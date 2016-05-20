#include "listePlanete.h"
#include "listePersonne.h"
#include "tas.h"
#include "conversion.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

/*@requires nomPlanete existe dans toutePlanete && toutePlanete contient toutes les planetes
  @assigns nothing
  @ensures renvoit l'objet planète depuis toutePlanete correspondant à nomPlanete*/
planete convertToPlanete(char* nomPlanete,liste_planete* toutePlanete){
  int i;
  liste_planete currentZone=creer_liste_planete();
  planete planeteCurr;
  for(i=0;i<6;i=i+1){
    currentZone=toutePlanete[i];
    while(liste_planete_vide(currentZone)==0){
      planeteCurr=currentZone->val;
      if(strcmp(planeteCurr->nom,nomPlanete)==0){
	return planeteCurr;
      }
      currentZone=currentZone->next;
    }
  }
  printf("Erreur on convertToPlanete : Planete '%s' introuvable",nomPlanete);
  exit(1);
}

/*@requires nomPlanete existe dans toutePlanete && toutePlanete contient toutes les planetes
  @assigns nothing
  @ensures renvoit la zone où se situe nomPlanete depuis toutePlanete*/
int quelZone(char* nomPlanete,liste_planete* toutePlanete){
  int i;
  liste_planete currentZone=creer_liste_planete();
  planete planeteCurr;
  for(i=0;i<6;i=i+1){
    currentZone=toutePlanete[i];
    while(liste_planete_vide(currentZone)==0){
      planeteCurr=currentZone->val;
      if(strcmp(planeteCurr->nom,nomPlanete)==0){
	return i;
      }
      currentZone=currentZone->next;
    }
  }
  return -1;
}

/*@requires nomPlanete existe, contrainte valide, partie == {0;1}, size >= 0 & size < 6
  @assigns nothing
  @ensures renvoie la position de nomPlanete dans contrainte si nomPlanete existe dans contrainte, -1 sinon*/
int dansContrainte(char* nomPlanete,char*** contrainte,int partie,int size){
  int i;
  int indice=-1;
  for(i=0;i<size;i=i+1){
    if(strcmp(nomPlanete,contrainte[partie][i])==0){
      indice=i;
      break;
    }
  }
  return indice;
}

/*@requires choix[] valide, nomPlanete existe
  @assigns nothing
  @ensures renvoi 1 si nomPlanete est dans choix[], 0 sinon*/
int dansLesChoix(char* choix[],char* nomPlanete){
  int present=0;
  int i;
  for(i=0;i<6;i=i+1){
    if(strcmp(choix[i],nomPlanete)){
      present=1;
      break;
    }
  }
  return present;
}

/*@requires choix est un choix libre
  @assign rien
  @ensure renvoi 1 si les contraintes sont respectees 0 sinon*/
int respectContrainte(char* choix[],char*** contrainte,int size){
  int respect=1;
  int i;
  int j;
  int k;
  for(i=0;i<size;i=i+1){
    for(j=0;j<6;j=j+1){
      if(strcmp(choix[j],contrainte[0][i])==0){
	respect=0;
	for(k=0;k<6;k=k+1){
	  if(strcmp(choix[k],contrainte[1][i])==0){
	    respect=1;
	    break;
	  }
	}
	if(respect==0){return 0;}
      }
    }
  }
  return respect;
}

/*@requires croisière valide
  @assign rien
  @ensure retourne le nombre de places max dans chaque croisière*/
int nbPlaceCroisiere(liste_planete* croisiere){
  int nbPlace = 15000;
  int sommePlace=0;
  int i;
  liste_planete current=creer_liste_planete();
  planete planeteCurr;
  for(i=0;i<6;i=i+1){/* pour chaque zone*/
    current=croisiere[i];
    while(liste_planete_vide(current)==0){/*tant qu'il reste des planetes dans la zone*/
      planeteCurr = current->val;
      sommePlace = sommePlace + planeteCurr->nbPlaces;/*on somme les places de chaque planete*/
      current=current->next;
    }
    if (sommePlace < nbPlace){/*on prend le minimum de chaque zone*/
      nbPlace=sommePlace;
    }
    sommePlace=0;
  }
  return nbPlace;
}

/*@requires choixCroisière valide, zone entre 0 et 5, choix valide
  @ensure renvoit 0 si plus de place dans la planete choix de la zone zone. 1 sinon, et reduit le nombre de places de la planete choix
  @assign change le nombre de places eventuellement*/
int choixPlanetePossible(liste_planete* choixCroisiere,int zone,char* choix){
  liste_planete tmp=choixCroisiere[zone];
  while(liste_planete_vide(tmp)==0){/*on parcours les planetes de la zone*/
    if(strcmp(choix,(tmp->val)->nom)==0){/*On recherche la planete correspondant au choix*/
      if((tmp->val)->nbPlaces > 0){/*s'il y a de la place*/
	(tmp->val)->nbPlaces--;/*on reduit le nombre de places dispo*/
	return 1;/*on renvoit que c'est possible*/
      }
      else{
	return 0;/*sinon c'est pas possible : pas de suppression de place*/
      }
    }
    else{
      tmp=tmp->next;
    }
  }
  return 0;
}

/*@requires toutePlanete valide, planete valide zone entre 0 et 5
  @assign retire une place a planete
  @ensure retire une place a planete*/
void supprimerPlace(liste_planete* toutePlanete,int zone,char* planete){
  choixPlanetePossible(toutePlanete,zone,planete);/*va retirer une place à planete car c'est forcément possible*/
}

/*@require choixCroisière valide et zone entre 0 et 5
  @assign rien
  @ensure retourne le nom de la planete dispo. 'impossible' sinon */
char* premiereDestPossible(liste_planete* choixCroisiere,int zone){
  liste_planete tmp=choixCroisiere[zone];
  while(liste_planete_vide(tmp)==0){
    if((tmp->val)->nbPlaces > 0){
      (tmp->val)->nbPlaces--;
      return (tmp->val)->nom;
    }
    else{
      tmp=tmp->next;
    }
  }
  printf("impossible");
  exit(1);
}

int main(int argc , char* argv[]){/*Ordre des tableau entrée : toutes planetes, croisière 1 (croisiere planetes), croisière 2 (croisiere satellites) , croisière 3 (croisiere vie), personnes, priorités, contraintes*/
  if(argc!=8){
    fprintf(stderr,"nombre incorrect d'arguments. Attendu : 7");
    exit(1);
  }
  int i,j;
  mkdir("resultat", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) ; /*crée un dossier résultat (n'y touche pas si existant)*/
  remove("resultat/affectation.csv"); /*supprime le fichier affectation.csv si existant*/
  FILE* fFinal=fopen("resultat/affectation.csv","a"); /*ouvre le fichier et le crée si n'existe pas (ici il le crée à chaque fois)*/
  FILE* fplanete=fopen(argv[1],"r");
  FILE* fcroisiere1=fopen(argv[2],"r");
  FILE* fcroisiere2=fopen(argv[3],"r");
  FILE* fcroisiere3=fopen(argv[4],"r");
  FILE* fpersonnes=fopen(argv[5],"r");
  FILE* fpriorite=fopen(argv[6],"r");
  FILE* fcontrainte=fopen(argv[7],"r");
  if((fFinal == NULL) || (fplanete == NULL) || (fcroisiere1 == NULL) || (fcroisiere2 == NULL) || (fcroisiere3 == NULL) || (fpersonnes == NULL) || (fpriorite == NULL) | (fcontrainte == NULL))
  {
  	fprintf(stderr,"%s : erreur d'ouverture des fichiers (vérifiez le nom)\n",argv[0]) ;
	exit(1) ;
  }
  tas tPersonne = creer_tas();/*Tas stockant l'ensemble des voyageurs*/
  tas* tasCroisiere=(tas*)malloc(4*sizeof(tas));;
  for (i=0;i<4;i=i+1){
    tasCroisiere[i] = creer_tas();/*tas regroupant les voyageurs d'une même croisière*/
  }
  tPersonne = convertir_t_personne(fpersonnes,fpriorite);
  liste_planete* Croisiere[4];/*Une case par croisière. Chaque croisière est une liste de planète*/
  Croisiere[0] = convertir_t_planete(fcroisiere1);/* CROISIERE PLANETE*/
  Croisiere[1] = convertir_t_planete(fcroisiere2);/* CROISIERE SATTELITE*/
  Croisiere[2] = convertir_t_planete(fcroisiere3);/*CROISIERE VIE*/
  Croisiere[3] = convertir_t_planete(fplanete);/*CROISIERE LIBRE*/
	
  int placeCroisiere[4];/*Nombre de places pour chaque croisière*/
  for(i=0;i<4;i=i+1){
    placeCroisiere[i]=nbPlaceCroisiere(Croisiere[i]);
  }
  int nbLigne=nombreligne(fcontrainte);
  char*** tContrainte = convertir_contrainte(fcontrainte,nbLigne);

  personne current;
  while(tas_vide(tPersonne)==0){
    current=retirer_tas(&tPersonne);/*on prend la personne avec la plus grande priorité*/
    if(placeCroisiere[current->id1 - 1]>0){/*Si il reste de la place dans la croisière choisie en 1er Choix*/
      placeCroisiere[current->id1-1]--;
      if(current->id1==4){
	placeCroisiere[3]--;
        current->chxFin=3;
      }
      else{
        current->chxFin=1;/*On indique que le premier choix est son choix*/
      }
      inserer_tas(&tasCroisiere[current->id1 - 1],current);/*ajout dans le tas de la croisière en question*/
    }
    else if(placeCroisiere[current->id2 - 1]>0){/*Si il reste de la place dans son choix deux*/
      placeCroisiere[current->id2-1]--;
      if(current->id2 == 4){
	placeCroisiere[3]--;
        current->chxFin=3;
      }
      else{
        current->chxFin=2;/*on indique que le deuxième choix est son choix*/
      }
      inserer_tas(&tasCroisiere[current->id2 - 1],current);/*ajout dans le tas de la croisière*/
    }
    else{
      placeCroisiere[3]--;
      current->chxFin=3;/*on indique que c'est ni son 1er ni son 2eme choix*/
      inserer_tas(&tasCroisiere[3],current);/*Sinon on assigne au choix libre*/
    }
  }
  /*--TRAITEMENT DES PLANETES DANS CROISIERE--*/
  char* imposition;
  planete Pimposition;
  for(i=0;i<3;i=i+1){/*Pour chaque croisière organisée*/;
    for(j=0;j<6;j=j+1){/*Pour chaque zone*/
      tas tasTampon=creer_tas();
      liste_personne tamponPersonne = creer_liste_personne();
      while(tas_vide(tasCroisiere[i])==0){/*tant qu'il y a des voyageurs dans le tas*/
	current=retirer_tas(&tasCroisiere[i]);/*on prend la personne a plus forte priorité*/
        if(i==current->id1-1){/*Si il s'agit de son premier choix*/
	  if(choixPlanetePossible(Croisiere[i],j,current->tabChxOrg1[j])==0){/*si son choix de zone j est pas possible*/
	    inserer_liste_personne(&tamponPersonne,current);/*on insere dans le tampon (voir apres)*/
	  }
	  else{
	    supprimerPlace(Croisiere[3],j,current->tabChxOrg1[j]); /*Si c'est possible on retire une place a la planete concernée. On a rien a faire pour enregistrer son choix : il est déja enregistré dans ses choix, on garde donc ça intact*/
	    inserer_tas(&tasTampon,current);
	  }
	}
	else{/*Si c'est son deuxième choix*/
	  if(choixPlanetePossible(Croisiere[i],j,current->tabChxOrg2[j])==0){/*si c'est pas possible*/
	    inserer_liste_personne(&tamponPersonne,current);/*tampon*/
	  }
	  else{
	    supprimerPlace(Croisiere[3],j,current->tabChxOrg2[j]);/*on supprime la place*/
	    inserer_tas(&tasTampon,current);
	  }
	}
      }
      while(liste_personne_vide(tamponPersonne)==0){/*on parcours les personnes dont le choix est impossible*/
	current=tamponPersonne->val;
	imposition = premiereDestPossible(Croisiere[i],j);/*on stocke dans imposition la première planete ou il y a de la place*/
	supprimerPlace(Croisiere[3],j,imposition);/*on supprime la place*/
	current->tabChxOrg1[j]=imposition;/*on change leurs choix qui sont maintenant leurs choix finaux*/
	current->tabChxOrg2[j]=imposition;
	inserer_tas(&tasTampon,current);
	tamponPersonne=tamponPersonne->next;
      }
      tasCroisiere[i]=tasTampon;
    }
    while(tas_vide(tasCroisiere[i])==0){
      ajout_ligne(retirer_tas(&tasCroisiere[i]),fFinal);
    }
  }
  /*TRAITEMENT DES CHOIX LIBRE*/
  liste_personne nonRespect = creer_liste_personne();/*on stocke ici les personnes ne respectant pas les contraintes*/
  liste_personne nonPlace = creer_liste_personne();/*Et ici les personnes sans destinations, faute de place*/
  liste_planete parcoursPlanete;
  char* implique;
  char* impliquant;
  char* choix;
  planete Pimplique;
  planete Pimpliquant;
  planete Pchoix;
  int alreadyInsert;
  int indice;
  int indice2;
  int zone;
  while(tas_vide(tasCroisiere[3])==0){
    current=retirer_tas(&tasCroisiere[3]);/*on retire les clients par ordre de priorité*/
    current->chxFin=3;/*on traite les choix libres, on rerègle leurs choix*/
    if(respectContrainte(current->tabChxLib,tContrainte,nbLigne)==0){
      inserer_liste_personne(&nonRespect,current);/*on isole ceux qui ne respectent pas les contraintes*/
    }
    else{
      alreadyInsert=0;/*on initialise à 0: il n'a pas été inseré dans les autres listes (il respecte les contraintes, et il y a de la place*/
      for(i=0;i<nbLigne;i=i+1){/*parcours du tableau des contraintes*/
	implique=tContrainte[1][i];/*planete impliquée par une autre*/
	impliquant=tContrainte[0][i];/*Planete qui implique une autre*/
	Pimplique = convertToPlanete(implique,Croisiere[3]);/*on récupere les objets pout tester les nb de places*/
	Pimpliquant = convertToPlanete(impliquant,Croisiere[3]);
	if((dansLesChoix(current->tabChxLib,implique)==1) && (dansLesChoix(current->tabChxLib,impliquant)==0) && (Pimpliquant->nbPlaces > Pimplique->nbPlaces - 1)){/*on vérifie qu'il reste des places dans les planetes contraintes*/
	  inserer_liste_personne(&nonPlace,current);/*pas de place => on insère*/
	  alreadyInsert=1;
	  break;
	}
      }
      if(alreadyInsert == 0){/*traitement uniquement si current n'a pas bougé vers les autres listes*/
	for(i=0;i<6;i=i+1){/*pour toutes les zones*/
	  if(current->assigned[i]==0){/*si la zone n'est pas déja assignée*/
	    choix=current->tabChxLib[i];/*on retient son choix*/
	    Pchoix=convertToPlanete(choix,Croisiere[3]);/*on récupère l'objet planete*/
	    indice=dansContrainte(choix,tContrainte,0,nbLigne);/*on vérifie si elle fait partie des contraintes*/
	    indice2=dansContrainte(choix,tContrainte,1,nbLigne);
	    if(indice>-1){/*si son choix implique une autre planete*/
	      implique=tContrainte[1][indice];/*on récupère ladite planète*/
	      Pimplique = convertToPlanete(implique,Croisiere[3]);
	      if((Pchoix->nbPlaces <= 0) || (Pimplique->nbPlaces <= 0)){/*si ya plus de place*/
		inserer_liste_personne(&nonPlace,current);/*on ajoute la personne dans la liste de ceux qui n'ont pas trouvé de place*/
		alreadyInsert=1;/*on indique qu'il a été inséré dans une liste*/
		break;
	      }
	      else{/*sinon pas de soucis on ajoute les 2 planetes a leurs destinations*/
		zone=quelZone(implique,Croisiere[3]);
		current->tabChxLib[i]=choix;
		current->tabChxLib[zone]=implique;
		supprimerPlace(Croisiere[3],i,choix);/*on supprime une place*/
		supprimerPlace(Croisiere[3],zone,implique);
		current->assigned[i]=1;/*et on met à jour les assignations*/
		current->assigned[zone]=1;
		
	      }
	    }
	    else if(indice2>-1){/*sinon si la planete est impliquée par un autre*/
	      impliquant=tContrainte[0][indice2];/*on récupère la planète nécéssaire*/
	      Pimpliquant=convertToPlanete(impliquant,Croisiere[3]);
	      if(dansLesChoix(current->tabChxLib,impliquant)){/*si cette planete est dans les choix*/
		zone=quelZone(impliquant,Croisiere[3]);/*alors on ajoute les deux*/
		current->tabChxLib[i]=choix;
		current->tabChxLib[zone]=impliquant;
		supprimerPlace(Croisiere[3],i,choix);
		supprimerPlace(Croisiere[3],zone,impliquant);
		current->assigned[i]=1;
		current->assigned[zone]=1;
	      }
	      else if((Pchoix->nbPlaces) - 1 < (Pimpliquant->nbPlaces)){/*sinon si le nombre de places de la planete impliquant le choix passerait au dessus apres affectation, on arrête les affectations*/
		inserer_liste_personne(&nonPlace,current);
		alreadyInsert=1;/*on indique que current a été ajouté dans la liste pour arrêter les affectations*/
		break;
	      }
	      else{
		current->assigned[i]=1;/*pas besoin d'assigner le choix, c'est déjà fait par definition*/
		supprimerPlace(Croisiere[3],i,choix);
	      }
	    }
	    else{/*choix n'apparait dans aucune contrainte*/
	      if(choixPlanetePossible(Croisiere[3],i,choix)==1){/*et si il y a de la place*/
		current->assigned[i]=1; /*le nombre de place est mis à jour dans la fonction dans le test*/
		current->tabChxLib[i]=choix; /*ainsi que son choix*/
	      }
	      else{/*il n'y a plus de place*/
		inserer_liste_personne(&nonPlace,current);/*on l'ajoute dans la liste de ceux qui ont un probleme de place*/
	        alreadyInsert=1;
		break;
	      }
	    }
	  }
	}
	if (alreadyInsert==0){/*si current n'a pas été inséré i.e. si tous ses choix ont fonctionné : on ajoute la personne au document final*/
	  ajout_ligne(current,fFinal);
	}
      }
    }
  }
  while(liste_personne_vide(nonPlace)==0 || liste_personne_vide(nonRespect)==0){/*tant qu'il reste des gens a traiter dans les 2 listes*/
    if(liste_personne_vide(nonPlace)==0){/*on retire et traite en priorité ceux qui n'ont pas eu de place*/
      current=nonPlace->val;
      nonPlace=nonPlace->next;
    }
    else{/*puis quand tout ceux la ont été traités, on traite ceux qui n'ont pas respecté les contraintes*/
      current=nonRespect->val;
      nonRespect=nonRespect->next;
    }
    
    for(i=0;i<6;i=i+1){/*pour chaque zone*/
      if (current->assigned[i] == 0){/*on applique l'algorithme a la zone i uniquement si elle a pas déja été traitée avant*/
	choix=current->tabChxLib[i];/*on retient son choix*/
	Pchoix=convertToPlanete(choix,Croisiere[3]);
	if(Pchoix->nbPlaces > 0){/*si son choix a encore des places libres*/
	  if(dansContrainte(choix,tContrainte,0,nbLigne)==-1 && dansContrainte(choix,tContrainte,1,nbLigne)==-1){/*si son choix n'apparait dans aucune contrainte*/
	    current->assigned[i]=1;/*alors il n'y a aucun soucis*/
	    supprimerPlace(Croisiere[3],i,choix);
	  }
	  else{/*sinon on regarde quelle contrainte est concernée*/
	    indice=dansContrainte(choix,tContrainte,0,nbLigne);/*choix implique une autre planete?*/
	    if(indice>-1){/*si oui*/
	      implique=tContrainte[1][indice];/*on recupere la planete impliquée*/
	      Pimplique=convertToPlanete(implique,Croisiere[3]);
	      if(Pimplique->nbPlaces > 0 ){/*si la planete impliquée est libre*/
		zone=quelZone(implique,Croisiere[3]);
		if(current->assigned[zone]==0 || dansLesChoix(current->tabChxLib,implique)==1){/*on vérifie que la zone ou se situe la planete impliquée n'a pas déjà été traitée ou si cette planete est dans les choix*/
		  current->tabChxLib[zone]=implique;/*si une de ces conditions est vraie, on assigne les deux*/
		  supprimerPlace(Croisiere[3],i,choix);
		  supprimerPlace(Croisiere[3],zone,implique);
		  current->assigned[i]=1;
		  current->assigned[zone]=1;
		}
	      }
	    }
	    else{/*choix n'implique rien, donc choix est impliqué (car choix est dans les contrainte)*/
	      indice=dansContrainte(choix,tContrainte,1,nbLigne);
	      impliquant=tContrainte[0][indice];/*on récupere la planete qui implique choix*/
	      Pimpliquant=convertToPlanete(impliquant,Croisiere[3]);
	      if(Pchoix->nbPlaces - 1 >= Pimpliquant->nbPlaces){/*si les contraintes de place sont respectées, on assigne*/
		supprimerPlace(Croisiere[3],i,choix);
		current->assigned[i]=1;
	      }
	    }
	  }
	}
	if(current->assigned[i]==0){/*Si il n'y a pas eu d'affectation précédement dans la zone i*/
	  parcoursPlanete=Croisiere[3][i];/*il faut regarder les autres planetes de ladite zone*/
	  while(liste_planete_vide(parcoursPlanete)==0){/*parcours...*/
	    imposition=(parcoursPlanete->val)->nom;
	    if(strcmp(imposition,choix)!=0){/*le parcours risque de passer par le choix. On vérifie qu'on ne traite pas ce cas là*/
	      Pimposition=convertToPlanete(imposition,Croisiere[3]);
	      indice=dansContrainte(imposition,tContrainte,0,nbLigne);/*on récupère les contraintes concernées par imposition, si elles existent*/
	      indice2=dansContrainte(imposition,tContrainte,1,nbLigne);
	      if(Pimposition->nbPlaces > 0 && indice==-1){/*si la planete parcourue est libre et n'implique aucune planete*/
		if(indice2>-1){/*si imposition est impliquée*/
		  impliquant=tContrainte[0][indice2];
		  Pimpliquant=convertToPlanete(impliquant,Croisiere[3]);
		  if(Pimposition->nbPlaces - 1 >= Pimpliquant->nbPlaces){/*on vérifie les conditions de place liées aux contraintes*/
		    current->tabChxLib[i]=imposition;/*assignation si respect*/
		    current->assigned[i]=1;
		    supprimerPlace(Croisiere[3],i,imposition);
		    break;/*zone assignée, on stop*/
		  }
		  if(dansLesChoix(current->tabChxLib,impliquant)==1){/*sinon on regarde si la planete impliquant la planete imposée est dans les choix, ce qui reglerait ce problème de place*/
		    zone=quelZone(impliquant,Croisiere[3]);/*si oui on affecte les deux*/
		    current->tabChxLib[i]=imposition;
		    current->tabChxLib[zone]=impliquant;
		    supprimerPlace(Croisiere[3],i,imposition);
		    supprimerPlace(Croisiere[3],zone,impliquant);
		    current->assigned[i]=1;
		    current->assigned[zone]=1;
		    break;/*zone assignée, stop*/
		  }
		}
		else{/*sinon imposition n'est dans aucune contrainte, et est libre : affectation*/
		  current->tabChxLib[i]=imposition;
		  current->assigned[i]=1;
		  supprimerPlace(Croisiere[3],i,imposition);
		  break;
		}
	      }
	      else if(Pimposition->nbPlaces > 0 && indice>-1){/*si la planete est libre et en implique une autre*/
		implique=tContrainte[1][indice];
		Pimplique=convertToPlanete(implique,Croisiere[3]);
		zone=quelZone(implique,Croisiere[3]);
		if(Pimplique->nbPlaces > 0 && current->assigned[zone]==0){/*on vérifie que la planete impliquée par la planete impose soit libre et que la zone ne soit pas déja assignée*/
		  current->tabChxLib[i]=imposition;/*si c'est respecté, aucune problème : on affecte les 2*/
		  current->tabChxLib[zone]=implique;
	          supprimerPlace(Croisiere[3],i,imposition);
		  supprimerPlace(Croisiere[3],zone,implique);
		  current->assigned[i]=1;
		  current->assigned[zone]=1;
		  break;
		}
	      }
	    }
	    parcoursPlanete=parcoursPlanete->next;/*la planete imposée n'est pas libre, ou inaffectable : on passe a la suivante*/
	  }
	}
      }
    }
    for(i=0;i<nbLigne;i=i+1){/*ce bout de code permet de regler le cas ou il n'y a plus assez de place autre part que dans une planete qui en implique une autre qui n'a pas été choisie par C*/
      impliquant=tContrainte[0][i];
      implique=tContrainte[1][i];
      zone=quelZone(implique,Croisiere[3]);
      if(current->assigned[zone]==0){
	current->tabChxLib[zone]=premiereDestPossible(Croisiere[3],zone);
	current->assigned[zone]=1;
      }
    }
    for(i=0;i<6;i=i+1){/*on vérifie que tout a été assigné*/
      if(current->assigned[i]==0){
	printf("Erreur : planete non assigné");
	exit(1);
	}
    }
    ajout_ligne(current,fFinal);
  }
  return 0;
}
