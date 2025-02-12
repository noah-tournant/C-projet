#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void saveGame(Player *player) {
    FILE *file = fopen("savegame.dat", "wb");
    if (file != NULL) {
        fwrite(player, sizeof(Player), 1, file);
        fclose(file);
        printf("Sauvegarde réussie !\n");
    } else {
        printf("Erreur de sauvegarde.\n");
    }
}

void loadGame(Player *player) {
    FILE *file = fopen("savegame.dat", "rb");
    if (file != NULL) {
        fread(player, sizeof(Player), 1, file);
        fclose(file);
        printf("Chargement réussi !\n");

    } else {
        printf("Aucune sauvegarde trouvée.\n");
    }
}

void displayMenu(Player *player) {
    int choice;
    do {
        printf("1. Charger une partie sauvegardée\n");
        printf("2. Démarrer une nouvelle partie\n");
        printf("3. Quitter\n");
        printf("Choisissez une option : ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        system("clear");

        switch (choice) {
            case 1:
                loadGame(player);
                break;
            case 2:
                printf("Démarrage d'une nouvelle partie\n");
                break;
            case 3:
                printf("Au revoir !\n");
                exit(0);
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice < 1 || choice > 3);
}
