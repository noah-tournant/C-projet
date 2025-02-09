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
                shop(player );
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

    // Initialiser un Supémon ennemi avec des statistiques proportionnelles
    initSupemon(&enemySupemon, "Wild Supemon", playerSupemon->level, playerSupemon->maxHP, playerSupemon->attack, playerSupemon->defense, playerSupemon->evasion, playerSupemon->accuracy, playerSupemon->speed);

    printf("Un %s sauvage apparaît !\n", enemySupemon.name);

    while (playerSupemon->HP > 0 && enemySupemon.HP > 0) {
        // Déterminer qui commence
        int playerTurn = (playerSupemon->speed > enemySupemon.speed) || (playerSupemon->speed == enemySupemon.speed && rand() % 2 == 0);

        if (playerTurn) {
            // Tour du joueur
            int action;
            printf("Choisissez une action :\n1. Attaque\n2. Changer de Supémon\n3. Utiliser un objet\n4. Fuir\n5. Capturer\n");
            scanf("%d", &action);

            switch (action) {
                case 1:
                    // Le joueur choisit une attaque
                    printf("Choisissez un mouvement :\n");
                    for (int i = 0; i < MAX_MOVES; i++) {
                        printf("%d. %s\n", i + 1, playerSupemon->moves[i].name);
                    }
                    int moveIndex;
                    scanf("%d", &moveIndex);
                    if (moveIndex > 0 && moveIndex <= MAX_MOVES) {
                        applyMove(playerSupemon, &enemySupemon, playerSupemon->moves[moveIndex - 1]);
                    } else {
                        printf("Mouvement invalide.\n");
                    }
                    break;
                case 2:
                     // Le joueur change de Supémon
                     printf("Choisissez un Supémon :\n");
                     for (int i = 0; i < player->supemonCount; i++) {
                         printf("%d. %s\n", i + 1, player->supemons[i].name);
                     }
                     int supemonIndex;
                     scanf("%d", &supemonIndex);
                     if (supemonIndex > 0 && supemonIndex <= player->supemonCount) {
                         player->selectedSupemonIndex = supemonIndex - 1;
                         playerSupemon = &player->supemons[player->selectedSupemonIndex];
                         printf("Vous avez changé pour %s.\n", playerSupemon->name);
                     } else {
                         printf("Choix invalide.\n");
                     }
                     break;
                case 3:
                    // Le joueur utilise un objet
                    break;
                case 4:
                    {
                        float runChance = (float)playerSupemon->speed / (playerSupemon->speed + enemySupemon.speed);
                        if ((float)rand() / RAND_MAX < runChance) {
                            printf("Vous avez réussi à fuir !\n");
                            return; // Terminer le combat
                        } else {
                            printf("La fuite a échoué !\n");
                        }
                    }
                    break;
                case 5:
                    // Le joueur essaie de capturer le Supémon ennemi
                    captureSupemon(player, &enemySupemon);
                    break;
                default:
                    printf("Action invalide. Réessayez.\n");
            }
        } else {
            // Tour de l'ennemi
            int moveIndex = rand() % MAX_MOVES;
            Move enemyMove = enemySupemon.moves[moveIndex];
            printf("L'ennemi %s utilise %s !\n", enemySupemon.name, enemyMove.name);
            applyMove(&enemySupemon, playerSupemon, enemyMove);
        }
    }

    if (playerSupemon->HP <= 0) {
        printf("Votre Supémon est KO !\n");
    } else {
        printf("Vous avez vaincu le %s sauvage !\n", enemySupemon.name);
        // Récompenser le joueur
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
                if (player->supcoins >= 100 && player->itemCount < MAX_ITEMS) {
                    player->supcoins -= 100;
                    strcpy(player->items[player->itemCount].name, "Potion");
                    player->items[player->itemCount].price = 100;
                    player->items[player->itemCount].effectValue = 5;
                    player->itemCount++;
                    printf("You bought a Potion!\n");
                } else {
                    printf("Not enough Supcoins or inventory full.\n");
                }
                break;
            case 2:
                if (player->supcoins >= 300 && player->itemCount < MAX_ITEMS) {
                    player->supcoins -= 300;
                    strcpy(player->items[player->itemCount].name, "Super Potion");
                    player->items[player->itemCount].price = 300;
                    player->items[player->itemCount].effectValue = 10;
                    player->itemCount++;
                    printf("You bought a Super Potion!\n");
                } else {
                    printf("Not enough Supcoins or inventory full.\n");
                }
                break;
            case 3:
                if (player->supcoins >= 700 && player->itemCount < MAX_ITEMS) {
                    player->supcoins -= 700;
                    strcpy(player->items[player->itemCount].name, "Rare Candy");
                    player->items[player->itemCount].price = 700;
                    player->items[player->itemCount].effectValue = 1; // Rare Candy effect
                    player->itemCount++;
                    printf("You bought a Rare Candy!\n");
                } else {
                    printf("Not enough Supcoins or inventory full.\n");
                }
                break;
            case 4:
                // Implement selling items
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
    printf("Votre prénom: ");
    scanf("%49s", player.name);
    initPlayer(&player, player.name);

    Move supmanderMoves[MAX_MOVES] = {
        {"cri", 0, {1, 1}},
        {"griffe", 2, {0, 0}},
    };

    Move supasaurMoves[MAX_MOVES] = {
        {"liane gigoteuse", 2, {0, 0}},
        {"planification", 0, {1, 4}},
    };

    Move supirtleMoves[MAX_MOVES] = {
        {"pistolet à O", 2, {0, 0}},
        {"armure", 0, {1, 2}},
    };

    Move mewtooMoves[MAX_MOVES] = {
        {"balles ombres", 3, {0, 0}},
        {"flex", 0, {2, 1}},
    };

    Move pikachuMoves[MAX_MOVES] = {
        {"vive attaque", 2, {0, 0}},
        {"mimi queue", 0, {1, 2}},
    };

    Move evoliMoves[MAX_MOVES] = {
        {"charge", 2, {0, 0}},
        {"rugissement", 0, {1, 1}},
    };

    Move tiploufMoves[MAX_MOVES] = {
        {"bubulle", 2, {-1, 5}},
        {"mimi queue", 0, {1, 2}},
    };

    Move voltorbeMoves[MAX_MOVES] = {
        {"éclair", 2, {-1, 2}},
        {"charge", 1, {0, 0}},
    };

    Supemon supmander;
    initSupemon(&supmander, "Supmander", 1, 10, 10, 2, 2, 3, 2, 2, supmanderMoves);
    addSupemon(&player, supmander);

    Supemon supasaur;
    initSupemon(&supasaur, "Supasaur", 1, 9, 9, 1, 1, 3, 2, 2, supasaurMoves);
    addSupemon(&player, supasaur);

    Supemon supirtle;
    initSupemon(&supirtle, "Supirtle", 1, 11, 11, 1, 2, 2, 1, 2, supirtleMoves);
    addSupemon(&player, supirtle);

    Supemon mewtoo;
    initSupemon(&mewtoo, "Mewtoo", 1, 20, 20, 3, 3, 3, 2, 3, mewtooMoves);
    addSupemon(&player, mewtoo);

    Supemon pikachu;
    initSupemon(&pikachu, "Pikachu", 1, 8, 8, 1, 1, 3, 2, 3, pikachuMoves);
    addSupemon(&player, pikachu);

    Supemon evoli;
    initSupemon(&evoli, "Evoli", 1, 9, 9, 1, 1, 2, 2, 2, evoliMoves);
    addSupemon(&player, evoli);

    Supemon tiplouf;
    initSupemon(&tiplouf, "Tiplouf", 1, 8, 8, 2, 2, 2, 2, 2, tiploufMoves);
    addSupemon(&player, tiplouf);

    Supemon voltorbe;
    initSupemon(&voltorbe, "Voltorbe", 1, 7, 7, 1, 1, 1, 1, 1, voltorbeMoves);
    addSupemon(&player, voltorbe);

    // Lancer le menu principal
    mainMenu(&player);

    return 0;
}
