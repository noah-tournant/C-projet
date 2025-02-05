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
                battle(player);
                break;
            case 2:
                shop(player);
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
    } while (choice != 5);
}

void battle(Player *player) {
    Supemon *playerSupemon = &player->supemons[player->selectedSupemonIndex];
    Supemon enemySupemon;

    // Select a random Supémon from the player's list to base the enemy Supémon on
    int randomIndex = rand() % MAX_SUPEMON;
    Supemon *randomSupemon = &player->supemons[randomIndex];

    // Initialize the enemy Supémon with the same level and proportional stats
    initSupemon(&enemySupemon, randomSupemon->name, playerSupemon->level, 
                randomSupemon->maxHP, randomSupemon->attack, randomSupemon->defense, 
                randomSupemon->evasion, randomSupemon->accuracy, randomSupemon->speed);

    printf("A wild %s appeared!\n", enemySupemon.name);

    while (playerSupemon->HP > 0 && enemySupemon.HP > 0) {
        // Determine who goes first
        int playerTurn = (playerSupemon->speed > enemySupemon.speed) || 
                         (playerSupemon->speed == enemySupemon.speed && rand() % 2 == 0);

        if (playerTurn) {
            // Player's turn
            int action;
            printf("Choose an action:\n1. Move\n2. Change Supemon\n3. Use an item\n4. Run away\n5. Capture\n");
            scanf("%d", &action);

            switch (action) {
                case 1:
                    // Player chooses a move
                    break;
                case 2:
                    // Player changes Supemon
                    break;
                case 3:
                    // Player uses an item
                    break;
                case 4:
                    // Player tries to run away
                    break;
                case 5:
                    // Player tries to capture the enemy Supemon
                    break;
                default:
                    printf("Invalid action. Try again.\n");
            }
        } else {
            // Enemy's turn
            int moveIndex = rand() % MAX_MOVES;
            Move enemyMove = enemySupemon.moves[moveIndex];
            printf("Enemy %s uses %s!\n", enemySupemon.name, enemyMove.name);
            // Apply move effects
        }
    }


    if (playerSupemon->HP <= 0) {
        printf("Your Supemon fainted!\n");
    } else {
        printf("You defeated the wild %s!\n", enemySupemon.name);
        // Reward player
    }
}

    if (playerSupemon->HP <= 0) {
        printf("Your Supemon fainted!\n");
    } else {
        printf("You defeated the wild %s!\n", enemySupemon.name);
        // Reward player
    }
}

void shop(Player *player) {
    int choice;
    do {
        printf("Welcome to the shop! You have %d Supcoins.\n", player->supcoins);
        printf("1. Buy Potion (100 Supcoins)\n");
        printf("2. Buy Super Potion (300 Supcoins)\n");
        printf("3. Buy Rare Candy (700 Supcoins)\n");
        printf("4. Sell items\n");
        printf("5. Exit shop\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Buy Potion
                break;
            case 2:
                // Buy Super Potion
                break;
            case 3:
                // Buy Rare Candy
                break;
            case 4:
                // Sell items
                break;
            case 5:
                printf("Thank you for visiting the shop!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);
}


int main() {
    Player player;
    initPlayer(&player, "Noah");

    // Ajouter des Supémons par défaut
    Supemon supmander;
    initSupemon(&supmander, "Supmander", 1, 10, 1, 1, 1, 2, 1);
    addSupemon(&player, supmander);

    Supemon supasaur;
    initSupemon(&supasaur, "Supasaur", 1, 9, 1, 1, 3, 2, 2);
    addSupemon(&player, supmander);

    Supemon supirtle;
    initSupemon(&supirtle, "Supirtle", 1, 11, 1, 2, 2, 1, 2);
    addSupemon(&player, supmander);
    // Lancer le menu principal
    mainMenu(&player);

    return 0;
}
