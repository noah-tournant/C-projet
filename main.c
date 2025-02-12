#include "header.h"

extern Supemon supemonsSauvages[MAX_SUPEMON];
extern int supemonsSauvagesCount;

int main() {
    Player player;
    
    printf(BOLD MAGENTA"Votre prénom: ");
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
    initSupemon(&supmander, "Supmander", 1, 10, 10, 2, 2, 3, 2, 2,0, supmanderMoves);
    
    Supemon supasaur;
    initSupemon(&supasaur, "Supasaur", 1, 9, 9, 1, 1, 3, 2, 2, 0, supasaurMoves);

    Supemon supirtle;
    initSupemon(&supirtle, "Supirtle", 1, 11, 11, 1, 2, 2, 1, 2, 0, supirtleMoves);

    Supemon mewtoo;
    initSupemon(&mewtoo, "Mewtoo", 1, 20, 20, 3, 3, 3, 2, 3, 0, mewtooMoves);
    addSupemonsauvage(mewtoo);

    Supemon pikachu;
    initSupemon(&pikachu, "Pikachu", 1, 8, 8, 1, 1, 3, 2, 3, 0, pikachuMoves);
    addSupemonsauvage(pikachu);

    Supemon evoli;
    initSupemon(&evoli, "Evoli", 1, 9, 9, 1, 1, 2, 2, 2, 0, evoliMoves);
    addSupemonsauvage(evoli);

    Supemon tiplouf;
    initSupemon(&tiplouf, "Tiplouf", 1, 8, 8, 2, 2, 2, 2, 2, 0, tiploufMoves);
    addSupemonsauvage(tiplouf);

    Supemon voltorbe;
    initSupemon(&voltorbe, "Voltorbe", 1, 7, 7, 1, 1, 1, 1, 1, 0, voltorbeMoves);
    addSupemonsauvage(voltorbe);

    printf(BOLD CYAN"Choisissez entre "RED"1:Supmander,"BLUE" 2:Supasaur "CYAN" et "GREEN" 3:Supirtle\n"RESET);
    scanf("%d", &player.selectedSupemonIndex);
    system("clear");

    while (player.selectedSupemonIndex < 1 || player.selectedSupemonIndex > 3) {
        printf("Choix invalide\n");
        printf(BOLD CYAN"Choisissez entre "RED"1:Supmander,"BLUE" 2:Supasaur "CYAN" et "GREEN" 3:Supirtle\n"RESET);
        scanf("%d", &player.selectedSupemonIndex);
        while (getchar() != '\n'); // Clear input buffer
    }

    if (player.selectedSupemonIndex == 1) {
        printf(RED"Vous avez choisi Supmander\n"RESET);
        addSupemon(&player, supmander);
    } else if (player.selectedSupemonIndex == 2) {
        printf(BLUE"Vous avez choisi Supasaur\n"RESET);
        addSupemon(&player, supasaur);
    } else if (player.selectedSupemonIndex == 3) {
        printf(GREEN"Vous avez choisi Supirtle\n"RESET);
        addSupemon(&player, supirtle);
    }

    mainMenu(&player);

    return 0;
}

void mainMenu(Player *player) {
    int choice;

    displayMenu(player);

    printf("\n" BOLD CYAN "Bienvenue, %s ! Que voulez-vous faire ?\n" RESET, player->name);
    do {
        printf(BOLD "\n----------------------------------------\n" RESET);
        printf(BOLD MAGENTA "\nMenu Principal\n" RESET);
        printf(BOLD "\n----------------------------------------\n\n" RESET);
        printf(GREEN "1. Combattre dans la nature\n" RESET);
        printf(BLUE "2. Accéder au magasin\n" RESET);
        printf(MAGENTA "3. Centre Supémon\n" RESET);
        printf(CYAN "4. Sauvegarder le jeu\n" RESET);
        printf(RED "5. Quitter\n" RESET);
        printf(YELLOW "\nChoisissez une option : "RESET);

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        system("clear");

        switch (choice) {
            case 1:
                battle(player);
                break;
            case 2:
                shop(player);
                break;
            case 3:
                CentreSupemon(player);
                break;
            case 4:
                saveGame(player);
                break;
            case 5:
                printf("Au revoir !\n");
                exit(0);
                break;
            default:
                printf(RED "Choix invalide. Essayez encore.\n" RESET);
        }
    } while (choice != 5);
}
