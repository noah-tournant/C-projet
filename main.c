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

    // Select a random Supémon from the player's list to base the enemy Supémon on
    int randomIndex = rand() % MAX_SUPEMON;
    Supemon *randomSupemon = &player->supemons[randomIndex];

    // Initialize the enemy Supémon with the same level and proportional stats
    initSupemon(&enemySupemon, randomSupemon->name, playerSupemon->level, 
                randomSupemon->maxHP,randomSupemon->HP, randomSupemon->attack, randomSupemon->defense, 
                randomSupemon->evasion, randomSupemon->accuracy, randomSupemon->speed, randomSupemon->moves);

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
    printf("Votre prénom\n");
    scanf("%49s", player.name);
    initPlayer(&player, player.name);

    Move supmanderMoves[MAX_MOVES] = {
        {"cri", 0, 1},
        {"griffe", 2, 0},
        {"", 0, 0},
        {"", 0, 0},
    };

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
    initSupemon(&supmander, "Supmander", 1, 10,10, 1, 1, 1, 2, 1, supmanderMoves);
   
    Supemon supasaur;
    initSupemon(&supasaur, "Supasaur", 1, 9,9, 1, 1, 3, 2, 2, supasaurMoves);
   
    Supemon supirtle;
    initSupemon(&supirtle, "Supirtle", 1, 11,11, 1, 2, 2, 1, 2, supirtleMoves);

    Supemon mewtoo;
    initSupemon(&mewtoo, "Mewtoo", 1, 20,20, 3, 3, 3, 2, 3, mewtooMoves);
    addSupemonsauvage(mewtoo);

    Supemon pikachu;
    initSupemon(&pikachu, "Pikachu", 1, 8,8, 1, 1, 3, 2, 3, pikachuMoves);
    addSupemonsauvage(pikachu);

    Supemon evoli;
    initSupemon(&evoli, "Evoli", 1, 9,9, 1, 1, 2, 2, 2, evoliMoves);
    addSupemonsauvage(evoli);

    Supemon tiplouf;
    initSupemon(&tiplouf, "Tiplouf", 1, 8,8, 2, 2, 2, 2, 2, tiploufMoves);
    addSupemonsauvage(tiplouf);

    Supemon voltorbe;
    initSupemon(&voltorbe, "Voltorbe", 1,7,7, 1, 1, 1, 1, 1, voltorbeMoves);
    addSupemonsauvage(voltorbe);

    printf("choissiez entre 1:Supmander, 2:Supasaur et 3:Supirtle\n");
    scanf("%d", &player.selectedSupemonIndex);
    if (player.selectedSupemonIndex == 1){
        printf("vous avez choisi Supmander\n");
        addSupemon(&player, supmander);
    }
    else if (player.selectedSupemonIndex == 2){
        printf("vous avez choisi Supasaur\n");
        addSupemon(&player, supasaur);
    }
    else if (player.selectedSupemonIndex == 3){
        printf("vous avez choisi Supirtle\n");
        addSupemon(&player, supirtle);
    }
    else{
        printf("choix invalide\n");
    }
    // Lancer le menu principal
    mainMenu(&player);

    return 0;
}