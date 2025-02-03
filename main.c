#include "header.h"


void mainMenu(Player *player) {
    int choice;
    do {
        printf("\nBienvenue, %s ! Que voulez-vous faire ?\n", player->name);
        printf("1. Combattre dans la nature\n");
        printf("2. Accéder au magasin\n");
        printf("3. Centre Supémon\n");
        printf("4. Sauvegarder le jeu\n");
        printf("5. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Lancer un combat
                break;
            case 2:
                // Accéder au magasin
                break;
            case 3:
                // Centre Supémon
                break;
            case 4:
                saveGame(player);
                break;
            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Essayez encore.\n");
        }
    } while (choice != 4);
}

int main() {
    Player player;
    initPlayer(&player, "Noah");

    // Ajouter des Supémons par défaut
    Supemon supmander;
    initSupemon(&supmander, "Supmander", 1, 10, 1, 1, 1, 2, 1);
    addSupemon(&player, supmander);

    // Lancer le menu principal
    mainMenu(&player);

    return 0;
}
