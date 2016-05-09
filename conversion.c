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


void inserecara(char * chaine, char caractere)
{
    int i = strlen(chaine) ;
    chaine[i] = caractere ;
    chaine[i+1] ='\0' ;
}

tas convertir_t_personne(FILE * f1,FILE * f2) //a modifier si ça marche liste-> tas
{
    tas tasP = creer_tas() ;
    char tampon1[BUFSIZE] ;
    char tmp[300] ; //tampon pour contenir la chaine de caractere de chaque case de la ligne
    tmp[0] = '\0' ;
    while(fgets(tampon1,BUFSIZE,f1)) //tant qu'on peut lire une ligne du tableau de souhait
    {
	personne personneTraite = creer_personne()  ; //on cree une variable ou vont etre stockees les infos des personnes
	int nonfinligne = 1 ;
        int i = 0 ; //variable pour le parcours de la ligne
	int j = 1 ; //variable pour savoir quelle information on a traitee
        int k = 1 ; //variable pour savoir quelle zone est traitee
        while (nonfinligne) //tant que la ligne n'est pas finie
        {
            if(tampon1[i]==',' || tampon1[i] =='\n') //on est tombé sur le délimitateur de case ou sur la fin de la ligne
            {
                switch (j)
                {
                    case 1 :
                    {
                            personneTraite->nom = malloc(20*sizeof(char)) ;
			    sprintf(personneTraite->nom,"%s",tmp) ;
                       	    j=j+1 ;
                            tmp[0] = '\0' ;
                            break ;
                    }
                    case 2 :
                    {
                            personneTraite->prenom = malloc(20*sizeof(char)) ;
			    sprintf(personneTraite->prenom,"%s",tmp) ;
		            j=j+1 ;
                            tmp[0] = '\0' ;
			    break ;
                           
                    }
                    case 3 :
                    {
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
                            else //cas où le type de croisière n'est pas reconnu
                            {
                                fprintf(stderr,"Conversion : Type de croisière non reconnue\n") ;
                                exit(1) ;
                            }
			    j=j+1 ;
                            tmp[0] = '\0' ;
			    break ;
                           
                    }
                    case 4 :
                    {
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
                            else //cas où le type de croisière n'est pas reconnu
                            {
                                fprintf(stderr,"Conversion : Type de croisière non reconnue\n") ;
                                exit(1) ;
                            }
			    j=j+1 ;
			    tmp[0] = '\0' ;
			    break ;
                    }
                    case 5 : //on traite le premier souhait 
                    {
                        if(personneTraite->id1 == 1)
                        {
                            switch (k)
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
                                  j=j+1 ;
                                  k= 1 ;
                                  break ;
                              }
                             
                            }
                        }
                        else if(personneTraite->id2 == 1)
                        {
                            switch (k)
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
                                  j=j+1 ;
                                  k= 1 ;
                                  break ;
                              }
			      
                            }
                        }
                        else
                        {
                            if (k==6)
                            {
                                k = 1 ;
                                j=j+1 ;
                            }
                            else
                            {
                                k=k+1 ;
                            }
			    
                        }
			tmp[0]='\0' ;
			break ;
                    }
                    case 6 : //on traite le deuxieme souhait
                    {
                        if(personneTraite->id1 == 2)
                        {
                            switch (k)
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
                                  j=j+1 ;
                                  k= 1 ;
                                  break ;
                              }
			      
                            }
                        }
                        else if(personneTraite->id2 == 2)
                        {
                            switch (k)
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
                                  j=j+1 ;
                                  k= 1 ;
                                  break ;
                              }
			      
                            }
                        }
                        else
                        {
                            if (k==6)
                            {
                                k = 1 ;
                                j=j+1 ;
                            }
                            else
                            {
                                k=k+1 ;
                            }
			    
                        }
			tmp[0]='\0' ;
			break ;
                    }
                    case 7 : //on traite le troisieme souhait
                    {
                        if(personneTraite->id1 == 3)
                        {
                            switch (k)
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
                                  j=j+1 ;
                                  k= 1 ;
                                  break ;
                              }
			      
                            }
                        }
                        else if(personneTraite->id2 == 3)
                        {
                            switch (k) 
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
                                  j=j+1 ;
                                  k= 1 ;
                                  break ;
                              }
                            }
                        }
                        else
                        {
                            if (k==6)
                            {
                                k = 1 ;
                                j=j+1 ;
                            }
                            else
                            {
                                k=k+1 ;
                            }
                        }
                        tmp[0]='\0' ;
			break ;
                    }
                    case 8 :
                    {
                        switch (k)
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
                                  j=j+1 ;
                                  k= 1  ;
				  nonfinligne = 0 ;
                                  break ;
                              }
                            }
			tmp[0]='\0' ;
			break ;
                    }
                }
            }
            else
            {
                inserecara(tmp,tampon1[i]) ;
            }
	    i=i+1 ;
        }
        i=0 ;
	tampon1[0] = '\0' ;
	fgets(tampon1,BUFSIZE,f2) ; //on lit le fichier de priorité ligne par ligne
        tmp[0] = '\0' ;
	j = 1 ;
	nonfinligne = 1 ;
        while (nonfinligne) //tant que la ligne n'est pas finie
            {
                if(tampon1[i] == ',' || tampon1[i] == '\n') //on est tombé sur le délimitateur de case
                {
                    if(j==3)
                    {
                        personneTraite->priorite = atoi(tmp) ;
                        if(personneTraite->id1 != 4)
                        {
                            personneTraite->priorite = personneTraite->priorite + 1000 ;
                        }
			nonfinligne = 0 ;
                    }
                    j=j+1 ;
                    tmp[0] = '\0' ;
                }
                else
                {
                    inserecara(tmp,tampon1[i]) ;
                }
                i=i+1 ;

            } 
	inserer_tas(&tasP,personneTraite) ; 
	tampon1[0] = '\0' ;
    }
    return tasP ; 
}


liste_planete * convertir_t_planete ( FILE * f )
{

    liste_planete * Tabplanete = malloc(6*sizeof(liste_planete)) ;
    int k=0 ;
    for(k=0;k<6;k=k+1)
    {
	Tabplanete[k] = creer_liste_planete() ;
    }
    char tampon1[BUFSIZE] ;
    char tmp[30]; //variable pour contenir le nom de la planete
    char tmp2[30] ; //variable pour contenir le nombre de place dispo
    tmp[0]='\0' ; tmp2[0]='\0' ;
    while(fgets(tampon1,BUFSIZE,f)) //tant qu'on peut lire une ligne du tableau de plenete
    {
	int nonFinligne = 1 ;
        int i = 0 ; //variable pour le parcours de la ligne
	int j = 0 ; //variable pour le parcour de chaque zone
        while (nonFinligne) //tant que la ligne n'est pas finie
        {
            if(tampon1[i] == ',')
            {
		printf("%i\n",j) ;
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
			nonFinligne = 0 ;
		    }
                }
	    j=j+1 ;
            tmp[0] = '\0' ;
            tmp2[0] ='\0' ;
      
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
    while( fgets(tampon,BUFSIZE,f) ) //tant qu'on peut lire une ligne du tableau
	i=i+1 ;
    return i ;
}

char*** convertir_contrainte (FILE * f)
{
    char*** TabContrainte = malloc( 2*sizeof(char**)) ;
    char tampon1[BUFSIZE] ;
    char tmp[30] ; //variable pour contenir le nom de la premiere planete
    char tmp2[30] ; //variable pour contenir le nom de la 2eme
    int i = nombreligne(f) ;
    int j = 0 ;
    for(j=0 ; j<1 ; j=j+1)
    {
        TabContrainte[j] = malloc(i*sizeof(char*)) ;
    }
    j = 0 ; //la j-eme ligne de contrainte
    while(fgets(tampon1,BUFSIZE,f)) //tant qu'on peut lire une ligne du tableau de contrainte
    {
       i = 0 ; //variable pour le parcours de la ligne
       while (tampon1[i] != '\0') //tant que la ligne n'est pas finie
       {
           if(tampon1[i] == ',')
           {
               while(tampon1[i] != '\0')
               {
                   inserecara(tmp2,tampon1[i]) ;
                   i=i+1 ;
               }
               sprintf(TabContrainte[0][j],"%s",tmp) ; //la premiere contrainte
               sprintf(TabContrainte[1][j],"%s",tmp2) ; //la seconde contrainte
               i=i-1 ;
           }
           else
           {
               inserecara(tmp,tampon1[i]) ;
           }
           i=i+1 ;
       }
       j=j+1 ;
    }
    return TabContrainte ;
}

void ajout_ligne ( personne Personne , FILE * file)
{
    char ligne[300] ;
    if(Personne->chxFin == 1)
    {
        sscanf(ligne,"%s,%s,%s,%s,%s,%s,%s,%s\n",Personne->nom,Personne->prenom,Personne->tabChxOrg1[0],Personne->tabChxOrg1[1],Personne->tabChxOrg1[2],Personne->tabChxOrg1[3],Personne->tabChxOrg1[4],Personne->tabChxOrg1[5]) ;
    }
    else if (Personne->chxFin == 2)
    {
        sscanf(ligne,"%s,%s,%s,%s,%s,%s,%s,%s\n",Personne->nom,Personne->prenom,Personne->tabChxOrg2[0],Personne->tabChxOrg2[1],Personne->tabChxOrg2[2],Personne->tabChxOrg2[3],Personne->tabChxOrg2[4],Personne->tabChxOrg2[5]) ;
    }
    else if ((Personne->chxFin) == 3)
    {
        sscanf(ligne,"%s,%s,%s,%s,%s,%s,%s,%s\n",Personne->nom,Personne->prenom,Personne->tabChxLib[0],Personne->tabChxLib[1],Personne->tabChxLib[2],Personne->tabChxLib[3],Personne->tabChxLib[4],Personne->tabChxLib[5]) ;
    }
    fseek(file,0,SEEK_END) ; //on se place a la fin du fichier
    fwrite(ligne,sizeof(ligne),1,file) ; // on ecrit la ligne
}
