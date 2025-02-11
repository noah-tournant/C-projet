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
    printf("1. Charger une partie sauvegardée\n");
    printf("2. Démarrer une nouvelle partie\n");
    printf("3. Quitter\n");
    printf("Choisissez une option : ");
    scanf("%d", &choice);
    system("clear");
    switch (choice) {
        case 1:
            loadGame(player);
            break;
        case 2:
            printf("Démarrage d'une nouvelle partie (fonctionnalité à implémenter)\n");
            break;
        case 3:
            printf("Au revoir !\n");
            exit(0);
            break;
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
            displayMenu(player);
            break;
    }
}
