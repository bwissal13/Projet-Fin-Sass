#include <stdio.h>
typedef struct {
    int id;
    char Title[200];
    char Description[500];
} Ajouter;
void ajoutTache(Ajouter tacheTable[], int sizeTable[]) {
    getchar();
    printf("Combien de taches voulez-vous ajouter ? : ");
    int numTaches;
    scanf("%d", &numTaches);

    for (int i = sizeTable[0]; i < sizeTable[0] + numTaches; i++) {
        tacheTable[i].id = i + 1;
        printf("Titre : ");
        getchar();
        fgets(tacheTable[i].Title, 200, stdin);
        printf("Description : ");
        fgets(tacheTable[i].Description,200, stdin);
    }

    sizeTable[0] += numTaches;
}void afficherTaches(Ajouter tacheTable[], int size) {
    if (size == 0) {
        printf("La liste des taches est vide.\n");
        return;
    }

    printf("Liste des taches:\n");
    for (int i = 0; i < size; i++) {
        printf("Titre: %s", tacheTable[i].Title);
        printf("Description: %s", tacheTable[i].Description);
        printf("\n");
    }
}



int main() {
    Ajouter tacheTable[200];
    int sizeTable[1] = {0};

    int menu;
    do {
        printf("Menu:\n");
        printf("1. Ajouter taches.\n");
        printf("2. Modifier une tache.\n");
        printf("3. Supprimer une tache.\n");
        printf("4. Rechercher une tache.\n");
        printf("5. Afficher les taches.\n");
        printf("6. Statistiques.\n");
        printf("7. Sortir du programme.\n");
        printf("Choisissez une option : ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                ajoutTache(tacheTable, sizeTable);
                break;
            case 2:
                break;
            case 3:

                break;
            case 4:

                break;
            case 5:
             afficherTaches(tacheTable, sizeTable[0]);
                break;
            case 6:

                break;
            case 7:
              printf("A la prochaine.\n");
                break;
            default:
                printf("Veuillez entrer une option valide.\n");
        }
    } while (menu != 8);

    return 0;
}
