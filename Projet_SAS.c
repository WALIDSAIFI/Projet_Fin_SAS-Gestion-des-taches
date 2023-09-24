#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>
#define Max 500
int N = 0;
int id=1;

typedef struct {
    int jour;
    int mois;
    int anne;
} date;

typedef struct {
    int   identifiant;
    date dateC;
    char  titre[50];
    char  Description[950];
    date  deadline;
    char  status[50];
} taches;
date date_actuelle(){
    date Date;
	
    time_t secondes = time(NULL);
    struct tm Date_actuel = *localtime(&secondes);
    Date.anne = Date_actuel.tm_year + 1900;
    Date.mois = Date_actuel.tm_mon + 1;
    Date.jour = Date_actuel.tm_mday; 
    return Date;
}

void ajouter_tach(taches Tab[]) {
    Tab[N].dateC = date_actuelle(); 
    Tab[N].identifiant=id++;
    printf("%d\n", Tab[N].identifiant);
    printf("Entrez le titre de la tache: ");
    scanf(" %[^\n]s", Tab[N].titre);
    printf("Description de la tache: ");
    scanf(" %[^\n]s", Tab[N].Description);
    printf("Entrez la deadline JJ/MM/AAAA: ");
    scanf("%d/%d/%d", &Tab[N].deadline.jour, &Tab[N].deadline.mois, &Tab[N].deadline.anne);
    while((Tab[N].deadline.jour>=31 ||Tab[N].deadline.jour<0) || (Tab[N].deadline.mois>=12 ||Tab[N].deadline.mois<0)){
    	printf("**Entre un date valide SVP!! JJ/MM/AAAA :");
    	scanf("%d/%d/%d", &Tab[N].deadline.jour, &Tab[N].deadline.mois, &Tab[N].deadline.anne);
	}
    int choix_statut;
    do {
        printf("Choisissez le statut de la tache:\n");
        printf("1.a realiser\n");
        printf("2.En cours de realisation\n");
        printf("3.Finalisee\n");
        printf("Choix: ");
        scanf("%d", &choix_statut);

        switch (choix_statut) {
            case 1:
                strcpy(Tab[N].status, "arealiser");
                break;
            case 2:
                strcpy(Tab[N].status, "En cours de realisation");
                break;
            case 3:
                strcpy(Tab[N].status, "Finalise");
                break;
            default:
                printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
        }
    } while (choix_statut < 1 || choix_statut > 3); 

    N++;
}

void ajouter_plusieurs_taches(taches Tab[]) {
    int i, nbr;
    printf("Donnez le nombre de taches a ajouter: ");
    scanf("%d", &nbr);
    for (i = 0; i < nbr; i++) {
        ajouter_tach(Tab);
    }
}
/*-----------------------------------les fonction de Affichage------------------------------------- */
void Afficher_plusieurs(taches Tab[]){
    int i;
    for(i=0;i<N;i++){
        printf("\n--------------------------------------------------\n");
        printf("\tIdentifiant : %d.\n",Tab[i].identifiant);
        printf("\tla date de creation JJ/MM/AAAA:%d/%d/%d\n",Tab[i].dateC.jour,Tab[i].dateC.mois,Tab[i].dateC.anne);
        printf("\tTitre : %s .\n",Tab[i].titre);
        printf("\tDescription:%s\n",Tab[i].Description);
        printf("\t Dealine  : %d/%d/%d\n",Tab[i].deadline.jour,Tab[i].deadline.mois,Tab[i].deadline.anne);
        printf("\tStatut:%s\n",Tab[i].status);
    }
}
/*--------------------------------fonction de trier est affiche+-------------------------------------*/


void trier_titre(taches Tab[]){
      int i,j;
      taches temp;
       for(i=0;i<N-1;i++){
        for  (j = 0; j <N-i-1; j++)
        {
             if(tolower(Tab[j].titre[0])>tolower(Tab[j+1].titre[0])){
                         temp=Tab[j];
                         Tab[j]=Tab[j+1];
                         Tab[j+1]=temp;
             }
        }
    }
         Afficher_plusieurs(Tab);
}
int  comp_date(date d1, date d2){
   if(d1.anne!=d2.anne){
    return d1.anne - d2.anne;
   }
    if(d1.mois!=d2.mois){
    return d1.mois - d2.mois;
    }
    if(d1.jour!=d2.jour){
    return d1.jour - d2.jour;
   }
}
void tri_date(taches tab[]){
     int i;
     int j;
     taches tmp;
     for(i=0;i<=N-2;i++){
        for(j=0;j<N-i-1;j++){
            if(comp_date(tab[j].deadline,tab[j+1].deadline)>0){
               tmp=tab[j];
               tab[j]=tab[j+1];
               tab[j+1]=tmp;
            }
        }
     }
     Afficher_plusieurs(tab);
}
void date_limite(taches Tab[]) {
    int i;
    int delai_jour[N];
    int jours;
     date d_actuel;
     d_actuel = date_actuelle();
    for (i = 0; i < N; i++) {
        jours = (Tab[i].deadline.anne - d_actuel .anne) * 365 + (Tab[i].deadline.mois - d_actuel.mois) * 30 + (Tab[i].deadline.jour - d_actuel.jour);
        delai_jour[i] = jours;  
    }
  
    for (i = 0; i < N; i++) {
    	if(delai_jour[i] == 0){
            printf("-----------------------------------------------------------\n");
            printf("| ID : %d    |  Titre : %s  | Date limite : Aujourd'hui\n", Tab[i].identifiant, Tab[i].titre);
               }else if(delai_jour[i]<=3 && delai_jour[i] > 0){
            	printf("-----------------------------------------------------------\n");
                 printf("| ID : %d    |  Titre : %s  | Date limite : dans %d jours\n", Tab[i].identifiant, Tab[i].titre, delai_jour[i]);
		 }
     }
}
void trie_menu(taches tab[]){
     int choix;
     printf("--------------Menu : Afficher la liste de toutes les taches --------------------------\n");
     printf("1-Trier les taches par ordre alphabetique.\n");
     printf("2-Trier les taches par deadline.\n");
     printf("3-Afficher les taches dont le deadline est dans 3 jours ou moins.\n");
     printf("Entre votre Choix: ");
     scanf("%d",&choix);
            switch (choix)
            {
            case 1:trier_titre(tab);
                break;
            case 2:tri_date(tab);
                 break;
            case 3: date_limite(tab);
                break;
            default: printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
                break;
            }

}

/*les fonction de modification*/
void modifier_Taches(taches Tab[]){
    int nbr,i,choix,choix_statut;
    printf("Donner le identifient de tache a modifier:");
    scanf("%d",&nbr);
    for(i=0;i<N;i++){
          if(Tab[i].identifiant == nbr){
           
                printf("0-Modifier la description de teche:\n");
                printf("1-Modifier le statut de tache.\n");
                printf("2-Modifier le deadline de tache.\n");
                printf("Saisir le Choix  a modifier :\n");
                scanf("%d",&choix);
                switch (choix)
                {
                case 0:printf("Entre le nouveau description:");
                       scanf("%s",&Tab[i].Description);
                    break;

                case 1:   
                            printf("Choisissez le statut de la tache:\n");
                            printf("1.a realiser\n");
                            printf("2.En cours de realisation\n");
                            printf("3.Finalisee\n");
                            printf("Choix: ");
                            scanf("%d", &choix_statut);
                              switch (choix_statut) {
                              case 1:
                                     strcpy(Tab[N].status, "arealiser");
                                        break;
                               case 2:
                                      strcpy(Tab[N].status, "En cours de realisation");
                                          break;
                                case 3:
                                      strcpy(Tab[N].status, "Finalise");
                                           break;
                                default:
                                      printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
                              }
                       break;
                case 2:printf("Entre le nouveau deadline de tache.");
                       scanf("%d/%d/%d",&Tab[i].deadline.jour,&Tab[i].deadline.mois,&Tab[i].deadline.anne);
                       break; 

                default:
                       printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
                    break;
                }
          }
    }
}
/*-----------------------------------------------les fonction de recherche----------------------------------*/
void Rechercher_taches_id(taches Tab[]){
    int i,id,test=0;
    printf("Donner identification a chercher:");
    scanf("%d",&id);
        for(i=0 ; i<N ;i++){
            if(Tab[i].identifiant == id){
               printf("la tache identifient %d il est existe.\n",id);
               test++;
            }
        }
        if(test == 0)
             printf("la tache de  identifient  %d il n'est pas existe.\n",id);
}
void Rechercher_taches_titre(taches tab[]){
    char titre;
    int i,t=0;
        printf("Donner le titre de tache a chercher:");
        scanf("%s",&titre);
        for(i = 0; i<N ;i++){
            if(strcmp(tab[i].titre,&titre) == 0){
                printf("la tache de titre %s il est existe.\n",tab[i].titre);
                  t++;
            }
            if(t == 0)
            printf("la tache de titre %s il n'est pas existe.\n",titre);
                
        }

}
void Rechercher_menu_taches(taches Tab[]){
    int choix;
            printf("1-Rechercher une tache par son Identifiant.\n");
            printf("2-Rechercher une tache par son Titre.\n");
            printf("3-Quiter:\n");
            printf("Donner votre choix:");
            scanf("%d",&choix);
            switch (choix)
            {
            case 1:Rechercher_taches_id(Tab);
                break;
            case 2:Rechercher_taches_titre(Tab);
                break;
            case 3: printf("Au revoir !");
                break;
            
            default:
                       printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
                    break;
            }
        
}


void Supprimer_tache(taches Tab[]){
    int i,j,id;
    printf("Donner identifiant a supprimer : ");
    scanf("%d",&id);
         for(i=0;i<N;i++){
            if(Tab[i].identifiant == id){
                for(j=i;j<N-1;j++)
                  Tab[j] = Tab[j+1];
            }
         }
         N--;
}
/*------------------------------------------les fonction de Statistique--------------------------------:*/
void Afficher_nombre_taches(){
    int cpt = N;
    printf("-----------------------------------------------------\n");
    printf("le nombre des Tache est %d.\n",cpt);
    printf("-----------------------------------------------------\n");
}
void Affiche_nombre_completes_incompletes(taches tab[]){
	
    int i,nbr_com=0,nbr_incomp=0; 
    for(i=0;i<N;i++){
        if(strcmp(tab[i].status,"Finalise") == 0)
             nbr_com++;
      else if(strcmp(tab[i].status,"En cours de realisation") == 0 || strcmp(tab[i].status,"arealiser"))
               nbr_incomp++;
    }  
     printf("-----------------------------------------------------\n");
     printf("le nombre des tache completes est :%d \n",nbr_com);
     printf("le nombre des tache incompletes est :%d \n",nbr_incomp);
     printf("-----------------------------------------------------\n");
    

}

void Afficher_nombre_restants(taches Tab[]) {
    int i;
    date dateActuelle = date_actuelle();

    for (i = 0; i < N; i++) {
        int jours = (Tab[i].deadline.anne - dateActuelle.anne) * 365 +  (Tab[i].deadline.mois - dateActuelle.mois) * 30 + (Tab[i].deadline.jour - dateActuelle.jour);

        printf("ID : %d | Titre : %s |", Tab[i].identifiant, Tab[i].titre);

        if (jours < 0) {
            printf(" Deadline : en retard de %d jours\n", -jours);
        } else if (jours == 0) {
            printf(" Deadline : Aujourd'hui\n");
        } else {
            printf(" il reste  :  %d jours\n", jours);
        }
    }
}
void Statistiques_menu(taches tab[]){
    int choix;
            printf("1-Afficher le nombre total des taches.\n");
            printf("2-Afficher le nombre de taches completes et incompletes.\n");
            printf("3-Afficher le nombre de jours restants jusqu'au delai de chaque tache.\n");
            printf("4-Quitter:\n");
            printf("Donner votre choix:");
            scanf("%d",&choix);
            switch (choix)
            {
            case 1:Afficher_nombre_taches(tab);
                break;
            case 2:Affiche_nombre_completes_incompletes(tab);
                break;
            case 3: Afficher_nombre_restants(tab);
                 break;
            
            default:
                       printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
                    break;
            }
}



int main() {
    taches tab[Max];
    int choix;
    do{
        printf("----------------------Menu : Gestion de Taches ToDo------------------------------------\n");
        printf("\t|1-Ajouter une nouvelle tache.\n");
        printf("\t|2-Ajouter plusieurs nouvelles taches.\n");
        printf("\t|3-Afficher la liste de toutes les taches (Identifiant, Titre, Description, Deadline, Statut).\n");
        printf("\t|4-Modifier une tache.\n");
        printf("\t|5-Supprimer une tache par identifiant.\n");
        printf("\t|6-Rechercher les Taches.\n");
        printf("\t|7-Statistiques.\n");
        printf("\t|8-Quitter.\n");
        printf("\t|Entre votre choix:");
        scanf("%d",&choix);

        switch (choix){
        case 1: ajouter_tach(tab);
            break;
        case 2:ajouter_plusieurs_taches(tab);
               break;
            
        case 3:trie_menu(tab);
                break;
        case 4:modifier_Taches(tab);
               break;
         case 5:Supprimer_tache(tab);
              break;
        case 6 : Rechercher_menu_taches(tab);
               break;
        case 7:Statistiques_menu(tab);
              break;
        case 8:printf("\tAu revoir !");
              break;
        default:
                       printf("Choix invalide. Veuillez choisir parmi les options disponibles!.\n");
                    break;
        }

    }while(choix!=8);

return 0;

}



