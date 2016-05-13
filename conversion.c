#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "listePlanete.h"
#include "listePersonne.h"
#include "tas.h"

#define BUFSIZE 400

/*@requires chaine une chaine de caractere et caractere un char
  @assigns chaine
  @ensures rajoute le caractère à la fin de la chaines
*/
void inserecara(char * chaine, char caractere)
{
    int i = strlen(chaine) ; //on calcule la taille de la chaine
    chaine[i] = caractere ; //on ajoute le caractère a la fin
    chaine[i+1] ='\0' ; //on finit la chaine par '\0' 
}

/*  @requires : f1 et f2 deux flux sur les fichiers des personnes (f1 = flux sur le tableau de priorite et f2 = flux sur le tableau desouhait)
    @assigns : nothing
    @ensures : retourne le tas où sont rangés toutes les personnes*/
tas convertir_t_personne(FILE * f1,FILE * f2)
{
    tas tasP = creer_tas() ; //création du tas où on va rentrer les personnes
    char tampon1[BUFSIZE] ; //tampon qui contiendra la ligne a traiter
    char tmp[300] ; //tampon pour contenir la chaine de caractere de chaque case de la ligne
    tmp[0] = '\0' ; //on initialise les tampons
    tampon1[0]='\0';
    while(fgets(tampon1,BUFSIZE,f1)) //tant qu'on peut lire une ligne du tableau de souhait : le fichier est pas infini, la boucle est finie
    {
	personne personneTraite = creer_personne()  ; //on cree la personne où on va rentrer toutes ses informations
	int nonfinligne = 1 ; //variable dont la valeur est 1 quand la ligne est pas finie et 0 quand elle est finie
        int i = 0 ; //variable pour le parcours de la ligne
	int j = 1 ; //variable pour savoir quelle information on a traitee
        int k = 1 ; //variable pour savoir quelle zone est traitee
        while (nonfinligne) //tant que la ligne n'est pas finie : la ligne est pas infini donc tampon[i] == '\n' -> nonfinligne = 0 ;
        {
            if(tampon1[i]==',' || tampon1[i] =='\n') //on est tombé sur le délimitateur de case ou sur la fin de la ligne
            {
                switch (j)
                {
                    case 1 : //la premiere case est le nom de la personne
                    {
                            personneTraite->nom = malloc(20*sizeof(char)) ; //on alloue la mémoire pour ranger l'info
			    sprintf(personneTraite->nom,"%s",tmp) ;
                       	    j=j+1 ; //on passe a la seconde case
                            tmp[0] = '\0' ; //la variable tampon est réinitialisée
                            break ;
                    }
                    case 2 : //la seconde case est le prenom de la personne
                    {
                            personneTraite->prenom = malloc(20*sizeof(char)) ; //on alloue la mémoire pour ranger l'info
			    sprintf(personneTraite->prenom,"%s",tmp) ;
		            j=j+1 ; //on passe a la 3eme case 
                            tmp[0] = '\0' ; //la variable tampon est réinitialisée
			    break ;
                           
                    }
                    case 3 : //la 3eme case est le premier souhait de la personne
                    {
			    //selon le souhait de la personne, on donne une valeur entiere propre à la croisière choisie
			    // 1 : croisière planetes
                            // 2 : croisiere satellites
			    // 3 : croisière vie
			    // 4 : croisière libre
			    // Si de nouvelles croisieres sont ajoutées dans le futur il faudra rajouter une conditionnelle avec un nouvel entier 
                            if(strcmp(tmp,"satellites")==0)
                            {
                                personneTraite->id1 = 2 ; //le premier choix est fixe sur la croisiere satellite
                            }
                            else if(strcmp(tmp,"vie")==0)
                            {
                                personneTraite->id1 = 3 ; //le premier choix est fixe sur la croisiere vie
                            }
                            else if(strcmp(tmp,"planetes")==0)
                            {
                                personneTraite->id1 = 1 ; //le premier choix est fixe sur la croisiere planetes
                            }
                            else if(strcmp(tmp,"libre")==0)
                            {
                                personneTraite->id1 = 4 ; //le premier choix est fixe sur la croisiere libre
                            }
                            else //cas où le type de croisière n'est pas reconnu (normalement cas n'existant pas hors erreur humaine)
                            {
                                fprintf(stderr,"Conversion : Type de croisière non reconnue\n") ;
                                exit(1) ;
                            }
			    j=j+1 ; //on passe a la 4eme case
                            tmp[0] = '\0' ; //la variable tampon est réinitialisée
			    break ;
                           
                    }
                    case 4 : //la 4eme case est le second choix de la personne
                    {
			    //selon le souhait de la personne, on donne une valeur entiere propre à la croisière choisie
			    // 1 : croisière planetes
                            // 2 : croisiere satellites
			    // 3 : croisière vie
			    // 4 : croisière libre
			    // Si de nouvelles croisieres sont ajoutées dans le futur il faudra rajouter une conditionnelle avec un nouvel entier 
                            if(strcmp(tmp,"satellites")==0)
                            {
                                personneTraite->id2 = 2 ; //le premier choix est fixe sur la croisiere satellite
                            }
                            else if(strcmp(tmp,"vie")==0)
                            {
                                personneTraite->id2 = 3 ; //le premier choix est fixe sur la croisiere vie
                            }
                            else if(strcmp(tmp,"planetes")==0)
                            {
                                personneTraite->id2 = 1 ; //le premier choix est fixe sur la croisiere planetes
                            }
                            else if(strcmp(tmp,"libre")==0)
                            {
                                personneTraite->id2 = 4 ; //le premier choix est fixe sur la croisiere libre
                            }
                            else //cas où le type de croisière n'est pas reconnu(cas impossible normalement hors faute humaine dans la prise de note)
                            {
                                fprintf(stderr,"Conversion : Type de croisière non reconnue\n") ;
                                exit(1) ;
                            }
			    j=j+1 ;
			    tmp[0] = '\0' ;
			    break ;
                    }
                    case 5 : //on traite la première selection de planetes (croisiere planetes = 6 zones) 
                    {
			//Ici, trois cas se présentent : -le premier choix est planetes
			//				 -le deuxieme choix est planetes
			//				 -Aucun des deux choix est planetes
                        if(personneTraite->id1 == 1) //Le premier choix est planetes, on va rentrer toutes les planetes dans le tableau de choix1
                        {
                            switch (k) //On traite chaque zone une par une
                            {
                              case 1 :
                              {
				  personneTraite->tabChxOrg1[0] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[0],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 2 :
                              {
                                  personneTraite->tabChxOrg1[1] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[1],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 3 :
                              {
                                  personneTraite->tabChxOrg1[2] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[2],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 4 :
                              {
                                  personneTraite->tabChxOrg1[3] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[3],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 5 :
                              {
                                  personneTraite->tabChxOrg1[4] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[4],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 6 :
                              {
                                  personneTraite->tabChxOrg1[5] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[5],"%s",tmp) ;
                                  j=j+1 ; //toutes les zones ont été traitées pour la croisière, on peut passer a la prochaine
                                  k= 1 ; //on réinitialise la variable des zones
                                  break ;
                              }
                             
                            }
                        }
                        else if(personneTraite->id2 == 1) //Le 2eme choix est planetes, on va rentrer toutes les planetes dans le tableau de choix1
                        {
                            switch (k) //on traite zone par zone
                            {
                              case 1 :
                              {
                                  personneTraite->tabChxOrg2[0] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[0],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 2 :
                              {
                                  personneTraite->tabChxOrg2[1] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[1],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 3 :
                              {
                                  personneTraite->tabChxOrg2[2] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[2],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 4 :
                              {
                                  personneTraite->tabChxOrg2[3] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[3],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 5 :
                              {
                                  personneTraite->tabChxOrg2[4] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[4],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 6 :
                              {
                                  personneTraite->tabChxOrg2[5] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[5],"%s",tmp) ;
                                  j=j+1 ; //toutes les zones ont été traitées pour la croisiere, on peut passer a la prochaine
                                  k= 1 ; //on réinitialise la variable des zones
                                  break ;
                              }
			      
                            }
                        }
                        else //aucun souhait pour cette croisière, on traite aucune information
                        {
                            if (k==6) //si on a passé toutes les zones de cette croisière
                            {
                                k = 1 ; //on réinitialise la variable des zones
                                j=j+1 ; //toutes les zones ont été traitées pour la crosière, on peut passer à la prochaine
                            }
                            else
                            {
                                k=k+1 ; 
                            }
			    
                        }
			tmp[0]='\0' ; //on réinitialise le tampon 
			break ;
                    }
                    case 6 : //on traite la deuxieme sélection de palanetes (croisière satllites = 6planetes)
		    //Ici, trois cas se présentent : -le premier choix est satellites
		    //				     -le deuxieme choix est satellites
		    //   		             -Aucun des deux choix est satellites
                    {
                        if(personneTraite->id1 == 2) //le premier choix est satellites
                        {
                            switch (k) //on traite chaque zones
                            {
                              case 1 :
                              {
                                  personneTraite->tabChxOrg1[0] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[0],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 2 :
                              {
                                  personneTraite->tabChxOrg1[1] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[1],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 3 :
                              {
                                  personneTraite->tabChxOrg1[2] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[2],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 4 :
                              {
                                  personneTraite->tabChxOrg1[3] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[3],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 5 :
                              {
                                  personneTraite->tabChxOrg1[4] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[4],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 6 :
                              {
                                  personneTraite->tabChxOrg1[5] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[5],"%s",tmp) ;
                                  j=j+1 ; //on passe a la prochaine selection de planetes
                                  k= 1 ; //on reinitialise la variable des zones
                                  break ;
                              }
			      
                            }
                        }
                        else if(personneTraite->id2 == 2) //le deuxieme choix est satellites
                        {
                            switch (k) // on parcourt les zones
                            {
                              case 1 :
                              {
                                  personneTraite->tabChxOrg2[0] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[0],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 2 :
                              {
                                  personneTraite->tabChxOrg2[1] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[1],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 3 :
                              {
                                  personneTraite->tabChxOrg2[2] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[2],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 4 :
                              {
                                  personneTraite->tabChxOrg2[3] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[3],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 5 :
                              {
                                  personneTraite->tabChxOrg2[4] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[4],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 6 :
                              {
                                  personneTraite->tabChxOrg2[5] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[5],"%s",tmp) ;
                                  j=j+1 ; //toutes les zones ont ete traitees, on peut passer a la prochaine selection de planete
                                  k= 1 ; //on reinitialise la variable des zones
                                  break ;
                              }
			      
                            }
                        }
                        else //aucun des choix est la croisière satellites
                        {
                            if (k==6) //on a parcouru toutes les zones
                            {
                                k = 1 ; //on reinitialise la variable des zones
                                j=j+1 ; //toutes les zones ont ete parcourues, on peut passer a la prochaine selection de planete
                            }
                            else
                            {
                                k=k+1 ;
                            }
			    
                        }
			tmp[0]='\0' ; //on reinitialise le tampon chaine de caractere
			break ;
                    }
                    case 7 : //on traite la troisieme selection de planete (croisiere vie = 6 planetes
                    {
		    //Ici, trois cas se présentent : -le premier choix est vie
		    //				     -le deuxieme choix est vie
		    //   		             -Aucun des deux choix est vie
                        if(personneTraite->id1 == 3) //le premier choix est la croisiere vie
                        {
                            switch (k) //on parcours toutes les zones
                            {
                              case 1 :
                              {
                                  personneTraite->tabChxOrg1[0] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[0],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 2 :
                              {
                                  personneTraite->tabChxOrg1[1] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[1],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 3 :
                              {
                                  personneTraite->tabChxOrg1[2] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[2],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 4 :
                              {
                                  personneTraite->tabChxOrg1[3] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[3],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 5 :
                              {
                                  personneTraite->tabChxOrg1[4] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[4],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 6 :
                              {
                                  personneTraite->tabChxOrg1[5] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg1[5],"%s",tmp) ;
                                  j=j+1 ; //on a parcouru toutes les zones, on peut passer a la prochaine selection de planetes
                                  k= 1 ; //on reinitialise la variable des zones
                                  break ;
                              }
			      
                            }
                        }
                        else if(personneTraite->id2 == 3) //le second choix est la croisiere vie
                        {
                            switch (k) //on parcourt toutes les zones
                            {
                              case 1 :
                              {
                                  personneTraite->tabChxOrg2[0] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[0],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 2 :
                              {
                                  personneTraite->tabChxOrg2[1] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[1],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 3 :
                              {
                                  personneTraite->tabChxOrg2[2] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[2],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 4 :
                              {
                                  personneTraite->tabChxOrg2[3] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[3],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 5 :
                              {
                                  personneTraite->tabChxOrg2[4] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[4],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 6 :
                              {
                                  personneTraite->tabChxOrg2[5] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxOrg2[5],"%s",tmp) ;
                                  j=j+1 ; //toutes les zones ont ete parcourues, on peut passer a la prochaine selection de planetes
                                  k= 1 ; //on reinitialise la variable des zones
                                  break ;
                              }
                            }
                        }
                        else //aucun des choix est la crosiere vie
                        {
                            if (k==6) //on a parcouru toutes les zones
                            {
                                k = 1 ; //on reinitialise la variable du parcourt des zones
                                j=j+1 ; //toutes les zones ont ete parcourues, on peut passer a la prochaine selection de planetes
                            }
                            else
                            {
                                k=k+1 ;
                            }
                        }
                        tmp[0]='\0' ; //on reinitialise la chaine tampon
			break ;
                    }
                    case 8 : //La derniere selection est la selection libre, quoiqu'il arrive, il faut la traiter
                    {
                        switch (k) //on parcours toutes les zones et on rentre les infos dans tabChxLib
                            {
                              case 1 :
                              {
                                  personneTraite->tabChxLib[0] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxLib[0],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 2 :
                              {
                                  personneTraite->tabChxLib[1] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxLib[1],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 3 :
                              {
                                  personneTraite->tabChxLib[2] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxLib[2],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 4 :
                              {
                                  personneTraite->tabChxLib[3] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxLib[3],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 5 :
                              {
                                  personneTraite->tabChxLib[4] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxLib[4],"%s",tmp) ;
                                  k=k+1 ;
                                  break ;
                              }
                              case 6 :
                              {
                                  personneTraite->tabChxLib[5] = malloc(20*sizeof(char)) ;
                                  sprintf(personneTraite->tabChxLib[5],"%s",tmp) ;
                                  j=j+1 ; //on a tout parcouru toute la ligne
                                  k= 1  ; //on reinitialise la variable e parcort des zones
				  nonfinligne = 0 ; //la ligne est finie, on peut sortir de la boucle
                                  break ;
                              }
                            }
			tmp[0]='\0' ; //on reinitialise le tampon chaine
			break ;
                    }
                }
            }
            else
            {
                inserecara(tmp,tampon1[i]) ; //on rajoute le prochain caractere du tampon ligne au tampon chaine (hors caracteres separateurs , et \n
            }
	    i=i+1 ; //on parcourt le tampon ligne
        }
	//il manque la priorite de la personne a aller chercher dans priorite.csv
	//on suppose qu'il y a le meme nombre de personne dans chaque fichier et que celles ci sont dans le meme ordre
        i=0 ; 
	tampon1[0] = '\0' ; //on reinitialise le tampon ligne
	fgets(tampon1,BUFSIZE,f2) ; //on lit le fichier de priorité ligne par ligne
        tmp[0] = '\0' ; //on reinitialise le tampon chaine
	j = 1 ; //on initialise le marqueur des cases
	nonfinligne = 1 ; //on initialise la variable pour la fin de ligne
        while (nonfinligne) //tant que la ligne n'est pas finie
            {
                if(tampon1[i] == ',' || tampon1[i] == '\n') //on est tombé sur le délimitateur de case
                {
                    if(j==3) //on est sur la case des priorités
                    {
                        personneTraite->priorite = atoi(tmp) ;
                        if(personneTraite->id1 != 4) //si la personne a un premier choix non libre, il passe en priorité devant les personne avec choix libre
                        {
                            personneTraite->priorite = personneTraite->priorite + 1000 ; //on rajoute 1000 car il n'y a que 200 personnes, la prio max est 200 donc en rajoutant 1000, elle passe devant
                        }
			nonfinligne = 0 ; //on est arrivé à la fin de la ligne
                    }
                    j=j+1 ;
                    tmp[0] = '\0' ; //on reinitialise le tampon chaine
                }
                else
                {
                    inserecara(tmp,tampon1[i]) ;
                }
                i=i+1 ;

            } 
	inserer_tas(&tasP,personneTraite) ; //on insere la personne totalement traitée au tas
	tampon1[0] = '\0' ; //on reinitialise le tampon ligne
    }
    return tasP ; //la fonction retourne le tas complet
}


liste_planete * convertir_t_planete ( FILE * f )
{

    liste_planete * Tabplanete = malloc(6*sizeof(liste_planete)) ; //on alloue la memoire pour le tableau de liste de planete
    int k=0 ; //on vas creer la liste de planete pour chaque zone
    for(k=0;k<6;k=k+1)
    {
	Tabplanete[k] = creer_liste_planete() ;
    }
    char tampon1[BUFSIZE] ; //on cree le tampon ligne
    char tmp[30]; //variable pour contenir le nom de la planete
    char tmp2[30] ; //variable pour contenir le nombre de place dispo
    tmp[0]='\0' ; tmp2[0]='\0' ; //on initialise les 2 tampons chaines
    while(fgets(tampon1,BUFSIZE,f)) //tant qu'on peut lire une ligne du tableau de plenete
    {
	int nonFinligne = 1 ; //variable pour la fin de la ligne
        int i = 0 ; //variable pour le parcours de la ligne
	int j = 0 ; //variable pour le parcour de chaque zone
        while (nonFinligne) //tant que la ligne n'est pas finie
        {
            if(tampon1[i] == ',') //on tombe sur le delimitateur d'une case
            {
		i=i+1 ;
                while(tampon1[i] != '\n' && tampon1[i] != ',')
                {
                    inserecara(tmp2,tampon1[i]) ;
                    i=i+1 ;
                }
                if (tmp[0] != '\0') //il existe des cas ou dans le tableau pour des planete d'une meme zone, il n'y a que des virgules avant ou apres
                {
		    planete planeteTraitee = creer_planete() ; //tampon planete
		    planeteTraitee->nom = malloc(20*sizeof(char)) ;
                    sprintf(planeteTraitee->nom,"%s",tmp) ;
                    planeteTraitee->nbPlaces = atoi(tmp2) ;
                    inserer_liste_planete(&Tabplanete[j] , planeteTraitee) ;
		    if(tampon1[i] == '\n')
		    {
			nonFinligne = 0 ; //la ligne est finie on sort de la boucle
		    }
                }
	    j=j+1 ;
            tmp[0] = '\0' ; //on reinitialise le tampon chaine
            tmp2[0] ='\0' ; //on reinitialise le tampon chaine
      
            }
            else
            {
                inserecara(tmp,tampon1[i]) ;
            }
            i=i+1 ;
        }
	


    }
    return Tabplanete ;
}

int nombreligne(FILE * f)
{
    int i=0 ;
    char tampon[BUFSIZE] ;
    tampon[0]='\0' ;
    while(fgets(tampon,BUFSIZE,f)) //tant qu'on peut lire une ligne du tableau
    {
	i=i+1 ;
	tampon[0]='\0' ;
    }
    fseek(f,0,SEEK_SET) ; //on se remet au début du fichier
    return i ;
}

char*** convertir_contrainte(FILE * f,int sizetab)
{
    char*** TabContrainte = malloc(2*sizeof(char**)) ; ;
    char tampon1[BUFSIZE] ;
    char tmp[30] ; //variable pour contenir le nom de la premiere planete
    char tmp2[30] ; //variable pour contenir le nom de la 2eme
    int j = 0 ;
    tmp[0]='\0' ;
    tmp2[0]='\0' ;
    tampon1[0]='\0' ;
    for(j=0 ; j<2 ; j=j+1)
    {
        TabContrainte[j] = malloc(sizetab*sizeof(char*)) ;
	int k = 0 ;
	for(k=0;k<sizetab;k=k+1)
	{
		TabContrainte[j][k] = malloc(30*sizeof(char)) ;
	}
    }
    j=0 ; //la j-eme ligne de contrainte
    while(fgets(tampon1,BUFSIZE,f)) //tant qu'on peut lire une ligne du tableau de contrainte
    {
       int nonFinligne = 1 ;
       int i = 0 ; //variable pour le parcours de la ligne
       while (nonFinligne) //tant que la ligne n'est pas finie
       {
           if(tampon1[i] == ',')
           {
	       i=i+1 ;
               while(tampon1[i] != '\n')
               {
                   inserecara(tmp2,tampon1[i]) ;
                   i=i+1 ;
               }
               sprintf(TabContrainte[0][j],"%s",tmp) ; //la premiere contrainte
               sprintf(TabContrainte[1][j],"%s",tmp2) ; //la seconde contrainte
               nonFinligne = 0 ;
	       
           }
           else
           {
               inserecara(tmp,tampon1[i]) ;
           }
           i=i+1 ;
       }
       tmp[0]='\0' ;
       tmp2[0]='\0' ;
       tampon1[0]='\0' ;
       j=j+1 ;
    }
    return TabContrainte ;
}

void ajout_ligne ( personne Personne , FILE * file)
{
    char ligne[300] ;
    if(Personne->chxFin == 1) //si la croisiere finale est contenue dans le premier choix
    {
        sscanf(ligne,"%s,%s,%s,%s,%s,%s,%s,%s\n",Personne->nom,Personne->prenom,Personne->tabChxOrg1[0],Personne->tabChxOrg1[1],Personne->tabChxOrg1[2],Personne->tabChxOrg1[3],Personne->tabChxOrg1[4],Personne->tabChxOrg1[5]) ;
    }
    else if (Personne->chxFin == 2) //si la croisiere finale est contenue dans le second choix
    {
        sscanf(ligne,"%s,%s,%s,%s,%s,%s,%s,%s\n",Personne->nom,Personne->prenom,Personne->tabChxOrg2[0],Personne->tabChxOrg2[1],Personne->tabChxOrg2[2],Personne->tabChxOrg2[3],Personne->tabChxOrg2[4],Personne->tabChxOrg2[5]) ;
    }
    else if ((Personne->chxFin) == 3) //si la croisiere finale est contenue dans le choix libre
    {
        sscanf(ligne,"%s,%s,%s,%s,%s,%s,%s,%s\n",Personne->nom,Personne->prenom,Personne->tabChxLib[0],Personne->tabChxLib[1],Personne->tabChxLib[2],Personne->tabChxLib[3],Personne->tabChxLib[4],Personne->tabChxLib[5]) ;
    }
    fseek(file,0,SEEK_END) ; //on se place a la fin du fichier
    fwrite(ligne,sizeof(ligne),1,file) ; // on ecrit la ligne
}
