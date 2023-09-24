#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 200
int sizeTable;
int numTaches;
typedef struct {
    int id;
    char Title[200];
    char Description[500];
    int Deadline[3];
    char Status[20];
} Task;

void getCurrentDate(int actualDate[]) {

    time_t t = time(NULL);
    struct tm* timeinfo = localtime(&t);
    actualDate[0] = timeinfo->tm_mday;
    actualDate[1] = timeinfo->tm_mon + 1;
    actualDate[2] = timeinfo->tm_year + 1900;
}

void ajoutTache(Task tacheTable[]) {
    getchar();
    printf("Combien de taches voulez-vous ajouter ? : ");
    scanf("%d", &numTaches);

    for (int i = 0; i < numTaches; i++) {
        tacheTable[i].id = i + 1;
        printf("Titre : ");
        getchar();
        fgets(tacheTable[i].Title, 200, stdin);
        printf("Description : ");
        fgets(tacheTable[i].Description, 500, stdin);
        printf("Deadline (format j/m/annee) : ");
        scanf("%d/%d/%d", &tacheTable[i].Deadline[0], &tacheTable[i].Deadline[1], &tacheTable[i].Deadline[2]);
        sizeTable++;
        printf("id = %d\n",sizeTable);
    }


}

void afficherTaches(Task tacheTable[], int size) {
    if (sizeTable == 0) {
        printf("La liste des taches est vide.\n");
        return;
    }

    int actualDate[3];
    getCurrentDate(actualDate);

    printf("Liste des taches:\n");
    for (int i = 0; i < sizeTable; i++) {
        printf("Titre: %s", tacheTable[i].Title);
        printf("id: %d\n", tacheTable[i].id);
        printf("Description: %s", tacheTable[i].Description);
        printf("Deadline: %d/%d/%d\n", tacheTable[i].Deadline[0], tacheTable[i].Deadline[1], tacheTable[i].Deadline[2]);

        if (tacheTable[i].Deadline[2] < actualDate[2] ||
            (tacheTable[i].Deadline[2] == actualDate[2] && tacheTable[i].Deadline[1] < actualDate[1]) ||
            (tacheTable[i].Deadline[2] == actualDate[2] && tacheTable[i].Deadline[1] == actualDate[1] && tacheTable[i].Deadline[0] < actualDate[0])) {
            printf("Status: Finalisee\n");
        } else if (tacheTable[i].Deadline[2] == actualDate[2] && tacheTable[i].Deadline[1] == actualDate[1] && tacheTable[i].Deadline[0] == actualDate[0]) {
            printf("Status: en cours de realisation\n");
        } else {
            printf("Status: a realiser\n");
        }
        printf("\n");
    }
}

void trierTachesAlphabetiquement(Task tacheTable[], int size) {
    for (int i = 0; i < sizeTable - 1; i++) {
        for (int j = i + 1; j < sizeTable; j++) {
            if (strcmp(tacheTable[i].Title, tacheTable[j].Title) > 0) {
                Task temp = tacheTable[i];
                tacheTable[i] = tacheTable[j];
                tacheTable[j] = temp;
            }
        }
    }
}

void trierTachesParDeadline(Task tacheTable[], int size) {
    for (int i = 0; i < sizeTable; i++) {
        for (int j = i + 1; j < sizeTable; j++) {
            if (tacheTable[i].Deadline[2] > tacheTable[j].Deadline[2] ||
                (tacheTable[i].Deadline[2] == tacheTable[j].Deadline[2] && tacheTable[i].Deadline[1] > tacheTable[j].Deadline[1]) ||
                (tacheTable[i].Deadline[2] == tacheTable[j].Deadline[2] && tacheTable[i].Deadline[1] == tacheTable[j].Deadline[1] && tacheTable[i].Deadline[0] > tacheTable[j].Deadline[0])) {
                Task temp = tacheTable[i];
                tacheTable[i] = tacheTable[j];
                tacheTable[j] = temp;
            }
        }
    }
}

void rechercherTacheParId(Task tacheTable[], int size, int id) {
    for (int i = 0; i < sizeTable; i++) {
        if (tacheTable[i].id == id) {
            printf("Tache trouvee par ID:\n");
            afficherTaches(&tacheTable[i], 1);
            return;
        }
    }
    printf("Aucune tache trouvee avec cet ID.\n");
}
void rechercherTacheParTitre(Task tacheTable[], int size, const char* titre) {
    int found = 0;
    for (int i = 0; i < sizeTable; i++) {
        if (strcmp(tacheTable[i].Title, titre) == 0) {
            found = 1;
            printf("Taches trouvees par titre:\n");
            afficherTaches(&tacheTable[i], 1);
        }
    }
    if (found == 0) {
        printf("Aucune tache trouvee avec ce titre.\n");
    }
}
void supprimerTacheParId(Task tacheTable[], int id) {
    int found = 0;
    for (int i = 0; i < sizeTable; i++)
        {
            if (tacheTable[i].id == id)
            {
            found = 1;
            }
        }

    if(found==1)
    {
        for(int i=id;i<sizeTable;i++)
        {
            tacheTable[i]=tacheTable[i+1];

        }
    }

    if (!found) {
        printf("Aucune tache trouvee avec cet ID.\n");
    }
        sizeTable--;

}
void modifierDescriptionTache(Task tacheTable[], int id) {
    for (int i = 0; i < sizeTable; i++) {
        if (tacheTable[i].id == id) {
            printf("Nouvelle description : ");
            getchar();
            fgets(tacheTable[i].Description, 500, stdin);
            printf("La description de la tache a ete modifiee avec succes.\n");
            return;
        }
    }
    printf("Aucune tache avec cet ID n'a ete trouvee.\n");
}

void modifierStatutTache(Task tacheTable[], int id) {
    for (int i = 0; i < sizeTable; i++) {
        if (tacheTable[i].id == id) {
            printf("Nouveau statut : ");
            getchar();
            fgets(tacheTable[i].Status, sizeof(tacheTable[i].Status), stdin);
            printf("Le statut de la tache a ete modifie avec succes.\n");
            return;
        }
    }
    printf("Aucune tache avec cet ID n'a ete trouvee.\n");
}

void modifierDeadlineTache(Task tacheTable[], int id) {
    for (int i = 0; i < sizeTable; i++) {
        if (tacheTable[i].id == id) {
            printf("Nouveau deadline (format j/m/annee) : ");
            scanf("%d/%d/%d", &tacheTable[i].Deadline[0], &tacheTable[i].Deadline[1], &tacheTable[i].Deadline[2]);
            printf("Le deadline de la tache a ete modifie avec succes.\n");
            return;
        }
    }
    printf("Aucune tache avec cet ID n'a ete trouvee.\n");
}
void afficherStatistiques(Task tacheTable[], int size) {
    if (sizeTable == 0) {
        printf("La liste des taches est vide.\n");
        return;
    }

    int totalTaches = sizeTable;
    int tachesCompletes = 0;
    int tachesIncompletes = 0;

    int actualDate[3];
    getCurrentDate(actualDate);

    printf("Nombre total de taches : %d\n", totalTaches);

    for (int i = 0; i < sizeTable; i++) {
        if (tacheTable[i].Deadline[2] < actualDate[2] ||
            (tacheTable[i].Deadline[2] == actualDate[2] && tacheTable[i].Deadline[1] < actualDate[1]) ||
            (tacheTable[i].Deadline[2] == actualDate[2] && tacheTable[i].Deadline[1] == actualDate[1] && tacheTable[i].Deadline[0] < actualDate[0])) {
            tachesCompletes++;
        } else {
            tachesIncompletes++;
        }

        int joursRestants = 0;
        if (tacheTable[i].Deadline[2] > actualDate[2] ||
            (tacheTable[i].Deadline[2] == actualDate[2] && tacheTable[i].Deadline[1] > actualDate[1]) ||
            (tacheTable[i].Deadline[2] == actualDate[2] && tacheTable[i].Deadline[1] == actualDate[1] && tacheTable[i].Deadline[0] > actualDate[0])) {
            joursRestants = (tacheTable[i].Deadline[2] - actualDate[2]) * 365 +
                            (tacheTable[i].Deadline[1] - actualDate[1]) * 30 +
                            (tacheTable[i].Deadline[0] - actualDate[0]);
        }

        printf("Tache #%d - Deadline : %d/%d/%d - Jours restants : %d\n",
               tacheTable[i].id, tacheTable[i].Deadline[0], tacheTable[i].Deadline[1], tacheTable[i].Deadline[2], joursRestants);
    }

    printf("Nombre de taches completes : %d\n", tachesCompletes);
    printf("Nombre de taches incompletes : %d\n", tachesIncompletes);
}




int main() {
    Task tacheTable[MAX_TASKS];
    int sizeTable = 0;

    int menu;
    do {
        printf("Menu:\n");
        printf("1. Ajouter taches.\n");
        printf("2. Modifier une tache.\n");
        printf("3. Supprimer une tache.\n");
        printf("4. Rechercher une tache.\n");
        printf("5. Afficher les taches.\n");
        printf("6. Trier les taches alphabétiquement.\n");
        printf("7. Trier les taches par deadline.\n");
        printf("8.Statistiques.\n");
        printf("9. Sortir du programme.\n");
        printf("Choisissez une option : ");
        scanf("%d", &menu);
        switch (menu) {
            case 1:
                ajoutTache(tacheTable);
                break;
            case 2:

                printf("Entrez l'ID de la tache que vous voulez modifier : ");
                int id;
                scanf("%d", &id);

                for (int i = 0; i <= numTaches; i++) {
                    if (tacheTable[i].id == id) {
                        printf("Que voulez-vous modifier pour cette tache ?\n");
                        printf("1. Modifier la description\n");
                        printf("2. Modifier le statut\n");
                        printf("3. Modifier la deadline\n");
                        printf("Choisissez une option : ");

                        int modificationOption;
                        scanf("%d", &modificationOption);

                        switch (modificationOption) {
                            case 1:
                                printf("deee");
                                modifierDescriptionTache(tacheTable,id);
                                break;
                            case 2:
                                printf("ff");
                                modifierStatutTache(tacheTable,id);
                                break;
                            case 3:
                                printf("gggg");
                                modifierDeadlineTache(tacheTable,id);
                                break;
                            default:
                                printf("Option de modification invalide.\n");
                        }

                    }
                }
                printf("Aucune tache avec cet ID n'a ete trouvee.\n");
                afficherTaches(tacheTable, sizeTable);
                break;
            case 3:
                printf("Entrez l'ID de la tache a supprimer : ");
                int taskId;
                scanf("%d", &taskId);
                supprimerTacheParId(tacheTable,taskId);
                afficherTaches(tacheTable, sizeTable);
                break;
            case 4:
                        printf("Vous voulez rechercher par id (1) ou par titre (2) : ");
                    int searchOption;
                    scanf("%d", &searchOption);
                    if (searchOption == 1) {
                        printf("Entrez l'ID de la tache : ");
                        int taskId;
                        scanf("%d", &taskId);
                        rechercherTacheParId(tacheTable, sizeTable, taskId);
                    } else if (searchOption == 2) {
                        printf("Entrez le titre de la tache : ");
                        getchar();
                        char taskTitle[200];
                        fgets(taskTitle, 200, stdin);
                        taskTitle[strcspn(taskTitle, "\n")] = '\0';
                        rechercherTacheParTitre(tacheTable, sizeTable, taskTitle);
                    } else {
                        printf("Option de recherche invalide.\n");
                    }
                    afficherTaches(tacheTable, sizeTable);
                    break;

            case 5:
                afficherTaches(tacheTable, sizeTable);
                break;
            case 6:
                trierTachesAlphabetiquement(tacheTable, sizeTable);
                printf("Les taches ont ete triees alphabetiquement.\n");
                afficherTaches(tacheTable, sizeTable);
                break;
            case 7:
                trierTachesParDeadline(tacheTable, sizeTable);
                printf("Les taches ont ete triees par deadline.\n");
                afficherTaches(tacheTable, sizeTable);
                break;
            case 8:
             afficherStatistiques(tacheTable, sizeTable);
            case 9:
                printf("A la prochaine!");
                exit(0);

            default:
                printf("Veuillez entrer une option valide.\n");
        }
    } while (menu != 8);

    return 0;
}
