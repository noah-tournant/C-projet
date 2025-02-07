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
    // Initialize player's Supemon (first in the list)
    Supemon *playerSupemon = &player->supemons[0];

    // Initialize enemy Supemon (randomly chosen from player's list)
    Supemon enemySupemon;
    int randomIndex = rand() % player->supemonCount;
    Supemon *randomSupemon = &player->supemons[randomIndex];
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
            printf("Your turn...\n\n %s (enemy)\n--------------------\n HP : %d/%d        Lvl:%d\n Atk: %d           Def:%d\n Acc:%d        Eva:%d\n-------------------------- \n %s (%s)\n--------------------\n HP : %d/%d        Lvl:%d\n Atk: %d           Def:%d\n Acc:%d        Eva:%d\n--------------------------\n\n ------------------------------\n | choisissez une action\n |    1- Mouvements     |\n |    2- changer de supémon     | \n |    3- Utiliser un objet    |\n |    4- Capturer     |\n |    5- Fuir    |\n ------------------------\n",
                enemySupemon.name, enemySupemon.HP, enemySupemon.maxHP, enemySupemon.level, enemySupemon.attack, enemySupemon.defense, enemySupemon.accuracy, enemySupemon.evasion,
                playerSupemon->name, player->name, playerSupemon->HP, playerSupemon->maxHP, playerSupemon->level, playerSupemon->attack, playerSupemon->defense, playerSupemon->accuracy, playerSupemon->evasion);
            printf("1, 2, 3, 4, 5 : ");
            scanf("%d", &action);

            switch (action) {
                case 1:
                    
                    break;
                case 2:
                    // Player changes Supemon
                    break;
                case 3:
                    // Player uses an item
                    break;
                case 4:
                    // capturer
                    break;
                case 5:
                    // fuir
                    break;
                default:
                    printf("Invalid action. Try again.\n");
            }
        } else {
            // Enemy's turn
            int moveIndex = rand() % MAX_MOVES;
            Move enemyMove = enemySupemon.moves[moveIndex];
            printf("Enemy %s uses %s!\n", enemySupemon.name, enemyMove.name);2
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


void shop(Player *player) {
    int choice;
    do {
        printf("Welcome to the shop! You have %d Supcoins.\n", player->supcoins);
        printf("1. Buy items\n");
        printf("2. Sell items\n");
        printf("3. Exit shop\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int buyChoice;
                displayItemsForSale();
                printf("Voici les items à acheter: ");
                scanf("%d", &buyChoice);

                switch (buyChoice) {
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
                    default:
                        printf("Invalid choice. Try again.\n");
                }
                break;
            }
            case 2: {
                int sellChoice;
                displayPlayerItems(player);
                printf("Choose an item to sell: ");
                scanf("%d", &sellChoice);

                if (sellChoice > 0 && sellChoice <= player->itemCount) {
                    int itemIndex = sellChoice - 1;
                    int sellingPrice = player->items[itemIndex].price / 2;
                    player->supcoins += sellingPrice;
                    printf("You sold %s for %d Supcoins.\n", player->items[itemIndex].name, sellingPrice);

                    // Remove the sold item from the inventory
                    for (int i = itemIndex; i < player->itemCount - 1; i++) {
                        player->items[i] = player->items[i + 1];
                    }
                    player->itemCount--;
                } else {
                    printf("Invalid choice. Try again.\n");
                }
                break;
            }
            case 3:
                printf("Thank you for visiting the shop!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);
}



int main() {
    Player player;
    initPlayer(&player, "Noah");

    Move supmanderMoves[MAX_MOVES] = {
        {"cri", 0, 1},
        {"griffe", 2, 0},
        {"", 0, 0},
        {"", 0, 0},
    }

    // Define moves for Supasaur
    Move supasaurMoves[MAX_MOVES] = {
        {"liane gigoteuse", 2, 0},
        {"planification", 0, 1},
        {"", 0, 0},
        {"", 0, 0},
    };

    // Define moves for Supirtle
    Move supirtleMoves[MAX_MOVES] = {
        {"pistolet à O", 2, 0},
        {"armure", 0, 1},
        {"", 0, 0},
        {"", 0, 0},
      
    };
     Move mewtooMoves[MAX_MOVES] = {
        {"balles ombres", 3, 0},
        {"flex", 0, 2},
        {"", 0, 0},
        {"", 0, 0}
    };
    Move pikachuMoves[MAX_MOVES] = {
        {"vive attaque", 2, 0},
        {"mimi queue", 0, 1},
        {"", 0, 0},
        {"", 0, 0}
    };

    // Define moves for Evoli
    Move evoliMoves[MAX_MOVES] = {
        {"charge", 2, 0},
        {"rugissement", 0, 1},
        {"", 0, 0},
        {"", 0, 0}
    };

    // Define moves for Tiplouf
    Move tiploufMoves[MAX_MOVES] = {
        {"ecume", 2, 0},
        {"bulle d'O", 3, 0},
        {"", 0, 0},
        {"", 0, 0}
    };

    // Define moves for Voltorbe
    Move voltorbeMoves[MAX_MOVES] = {
        {"etincelle", 2, 0},
        {"charge", 1, 0},
        {"", 0, 0},
        {"", 0, 0}
    };

    Supemon supmander;
    initSupemon(&supmander, "Supmander", 1, 10, 1, 1, 1, 2, 1, supmanderMoves);
    addSupemon(&player, supmander);

    Supemon supasaur;
    initSupemon(&supasaur, "Supasaur", 1, 9, 1, 1, 3, 2, 2, supasaurMoves);
    addSupemon(&player, supasaur);

    Supemon supirtle;
    initSupemon(&supirtle, "Supirtle", 1, 11, 1, 2, 2, 1, 2, supirtleMoves);
    addSupemon(&player, supirtle);

    Supemon mewtoo;
    initSupemon(&mewtoo, "Mewtoo", 1, 20, 3, 3, 3, 2, 3, mewtooMoves);
    addSupemon(&player, mewtoo);

    Supemon pikachu;
    initSupemon(&pikachu, "Pikachu", 1, 8, 1, 1, 3, 2, 3, pikachuMoves);
    addSupemon(&player, pikachu);

    Supemon evoli;
    initSupemon(&evoli, "Evoli", 1, 9, 1, 1, 2, 2, 2, evoliMoves);
    addSupemon(&player, evoli);

    Supemon tiplouf;
    initSupemon(&tiplouf, "Tiplouf", 1, 8, 2, 2, 2, 2, 2, tiploufMoves);
    addSupemon(&player, tiplouf);

    Supemon voltorbe;
    initSupemon(&voltorbe, "Voltorbe", 1, 7, 1, 1, 1, 1, 1, voltorbeMoves);
    addSupemon(&player, voltorbe);

    // Lancer le menu principal
    mainMenu(&player);

    return 0;
}