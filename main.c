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

void applyMove(Supemon *attacker, Supemon *defender, Move move) {
    if (move.damage > 0) {
        defender->HP -= move.damage;
        if (defender->HP < 0) defender->HP = 0;
        printf("%s used %s! It dealt %d damage.\n", attacker->name, move.name, move.damage);
    } else if (move.buff.value != 0) {
        if (move.buff.value > 0) {
            switch (move.buff.statType) {
                case 1: attacker->attack += move.buff.value; break;
                case 2: attacker->defense += move.buff.value; break;
                case 3: attacker->evasion += move.buff.value; break;
                case 4: attacker->accuracy += move.buff.value; break;
                case 5: attacker->speed += move.buff.value; break;
            }
            printf("%s used %s! It increased its stat by %d.\n", attacker->name, move.name, move.buff.value);
        } else {
            switch (move.buff.statType) {
                case 1: defender->attack += move.buff.value; break;
                case 2: defender->defense += move.buff.value; break;
                case 3: defender->evasion += move.buff.value; break;
                case 4: defender->accuracy += move.buff.value; break;
                case 5: defender->speed += move.buff.value; break;
            }
            printf("%s used %s! It decreased the enemy's stat by %d.\n", attacker->name, move.name, -move.buff.value);
        }
    }
}

void battle(Player *player) {
    Supemon *playerSupemon = &player->supemons[0];
    Supemon enemySupemon;
    int randomIndex = rand() % player->supemonCount;
    Supemon *randomSupemon = &player->supemons[randomIndex];
    initSupemon(&enemySupemon, randomSupemon->name, playerSupemon->level, randomSupemon->maxHP, randomSupemon->attack, randomSupemon->defense, randomSupemon->evasion, randomSupemon->accuracy, randomSupemon->speed, randomSupemon->moves);
    
    printf("A wild %s appeared!\n", enemySupemon.name);

    while (playerSupemon->HP > 0 && enemySupemon.HP > 0) {
        int playerTurn = (playerSupemon->speed > enemySupemon.speed) || (playerSupemon->speed == enemySupemon.speed && rand() % 2 == 0);

        if (playerTurn) {
            int action;
            printf("Choose an action:\n1. Move\n2. Change Supemon\n3. Use an item\n4. Run away\n5. Capture\n");
            scanf("%d", &action);

            switch (action) {
                case 1: {
                    int moveChoice;
                    printf("Choose a move:\n1- %s\n2- %s\n3- Cancel\n", playerSupemon->moves[0].name, playerSupemon->moves[1].name);
                    scanf("%d", &moveChoice);

                    if (moveChoice == 1 || moveChoice == 2) {
                        applyMove(playerSupemon, &enemySupemon, playerSupemon->moves[moveChoice - 1]);
                    } else {
                        printf("Move cancelled.\n");
                    }
                    break;
                }
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
            int moveIndex = rand() % MAX_MOVES;
            Move enemyMove = enemySupemon.moves[moveIndex];
            applyMove(&enemySupemon, playerSupemon, enemyMove);
        }
    }

    if (playerSupemon->HP <= 0) {
        printf("Your Supemon fainted!\n");
    } else {
        printf("You defeated the wild %s!\n", enemySupemon.name);
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