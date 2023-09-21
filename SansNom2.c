#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <ctype.h>
int N = 0;

typedef struct {
    int jour;
    int mois;
    int anne;
} date;

typedef struct {
    int   identifiant;
    char  titre[50];
    char  Description[400];
    date  deadline;
    char  status[50];
} taches;


void ajouter_tach(taches Tab[]) {
   Tab[N].identifiant = N + 1;
    printf("%d\n", Tab[N].identifiant);
    printf("Entrez le titre de la tache: ");
    scanf("%s", Tab[N].titre);
    printf("Description de la tache: ");
    scanf(" %s", Tab[N].Description);  
    printf("Entrez la deadline JJ/MM/AAAA: ");
    scanf("%d/%d/%d", &Tab[N].deadline.jour, &Tab[N].deadline.mois, &Tab[N].deadline.anne);
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
/*les fonction de Affichage */
void Afficher_plusieurs(taches Tab[]){
    int i;
    for(i=0;i<N;i++){
        printf("\n--------------------------------------------------\n");
        printf("\tIdentifiant : %d.\n",Tab[i].identifiant);
        printf("\tTitre : %s .\n",Tab[i].titre);
        printf("\tDescription:%s\n",Tab[i].Description);
        printf("\t Dealine  : %d/%d/%d\n",Tab[i].deadline.jour,Tab[i].deadline.mois,Tab[i].deadline.anne);
    }
}
/*fonction de trier*/


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
}
void Trier_deadline(taches tab){
    
}
/*les fonction de modification*/
void modifier_Taches(taches Tab[]){
    int nbr,i,choix;
    printf("Donner le identifient de tache a modifier:");
    scanf("%d",&nbr);
    for(i=0;i<N;i++){
          if(Tab[i].identifiant == nbr){
            do{
                printf("0-Modifier la description de teche:\n");
                printf("1-Modifier le statut de tache.\n");
                printf("2-Modifier le deadline de tâche.\n");
                printf("3-Quetter:\n");
                printf("Saisir le Choix de Affichage :\n");
                scanf("%d",&choix);
                switch (choix)
                {
                case 0:printf("Entre le nouveau description:");
                       scanf("%s",&Tab[i].Description);
                    break;
                case 1:printf("Entre le nouveau satut de tache:");
                       scanf("%s",&Tab[i].status);
                       break;
                case 2:printf("Entre le nouveau deadline de tache.");
                       scanf("%d/%d/%d",&Tab[i].deadline.jour,&Tab[i].deadline.mois,&Tab[i].deadline.anne);
                       break;
                case 3:printf("Au revoir!");
                
                default:
                       printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
                    break;
                }

            }while( choix!=3); 
          }
    }
}
/*les fonction de recherche*/
void Rechercher_taches_id(taches Tab[]){
    int i,id,test=0;
    printf("Donner identification a chercher:");
    scanf("%d",&id);
        for(i=0 ; i<N ;i++){
            if(Tab[i].identifiant == id){
               printf("la tache identifient %d il est existe.\n");
               test++;
            }
        }
        if(test == 0)
             printf("la tache identifient %d il n'est pas existe.\n",id);
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
         do{
            printf("1-Rechercher une tâche par son Identifiant.\n");
            printf("2-Rechercher une tâche par son Titre.\n");
            printf("3-Quiter:");
            printf("Donner votre choix:");
            scanf("%d",&choix);
            switch (choix)
            {
            case 1:Rechercher_taches_id(Tab);
                break;
            case 2:Rechercher_taches_titre(Tab);
                break;
            case 3: printf("Au revoir !");
            
            default:
                       printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
                    break;
            }
         }while(choix!=3); 
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
/*les fonction de Statistique:*/
void Afficher_nombre_taches(){
    int cpt = N;
    printf("le nombre des Tache est %d.\n",cpt);
}
void Affiche_nombre_completes_incompletes(taches tab[]){
    int i,nbr_com=0,nbr_incomp=0; 
    for(i=0;i<N;i++){
        if(strcmp(tab[i].status,"Finalise") == 0)
             nbr_com++;
      else if(strcmp(tab[i].status,"En cours de realisation") == 0 || strcmp(tab[i].status,"arealiser"))
               nbr_incomp++;
    }  
     printf("le nombre des tache completes est :%d \n",nbr_com);
     printf("le nombre des tache incompletes est :%d \n",nbr_incomp);
    

}
void Afficher_jours_restants(taches tab[]){

}


int main() {
    taches tab[150];
    int choix;
    do{
        printf("----------------------Menu-----------------------\n");
        printf("1-Ajouter une nouvelle tache.\n");
        printf("2-Ajouter plusieurs nouvelles taches.\n");
        printf("3-Afficher la liste de toutes les taches (Identifiant, Titre, Description, Deadline, Statut).\n");
        printf("4-Modifier une tâche.\n");
        printf("5-Supprimer une tache par identifiant.\n");
        printf("6-Rechercher les Taches.\n");
        printf("7-Statistiques.\n");
        printf("8-Quitter.\n");
        printf("Entre votre choix:");
        scanf("%d",&choix);

        switch (choix){
        case 1: ajouter_tach(tab);
            break;
        case 2:ajouter_plusieurs_taches(tab);
               break;
            
        case 3:Afficher_plusieurs(tab);
                break;
        case 4:modifier_Taches(tab);
               break;
         case 5:Supprimer_tache(tab);
              break;
        default:
                       printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
                    break;
       
        }
    }while(choix!=8);

  
   

    return 0;
}

