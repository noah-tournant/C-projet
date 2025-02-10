#include "header.h"

extern Supemon supemonsSauvages[MAX_SUPEMON];
extern int supemonsSauvagesCount;

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
    addSupemonsauvage(mewtoo);

    Supemon pikachu;
    initSupemon(&pikachu, "Pikachu", 1, 8, 8, 1, 1, 3, 2, 3, pikachuMoves);
    addSupemonsauvage(pikachu);

    Supemon evoli;
    initSupemon(&evoli, "Evoli", 1, 9, 9, 1, 1, 2, 2, 2, evoliMoves);
    addSupemonsauvage(evoli);

    Supemon tiplouf;
    initSupemon(&tiplouf, "Tiplouf", 1, 8, 8, 2, 2, 2, 2, 2, tiploufMoves);
    addSupemonsauvage(tiplouf);

    Supemon voltorbe;
    initSupemon(&voltorbe, "Voltorbe", 1, 7, 7, 1, 1, 1, 1, 1, voltorbeMoves);
    addSupemonsauvage(voltorbe);

    printf("choissiez entre 1:Supmander, 2:Supasaur et 3:Supirtle\n");
    scanf("%d", &player.selectedSupemonIndex);
    if (player.selectedSupemonIndex == 1) {
        printf("vous avez choisi Supmander\n");
        addSupemon(&player, supmander);
    } else if (player.selectedSupemonIndex == 2) {
        printf("vous avez choisi Supasaur\n");
        addSupemon(&player, supasaur);
    } else if (player.selectedSupemonIndex == 3) {
        printf("vous avez choisi Supirtle\n");
        addSupemon(&player, supirtle);
    } else {
        printf("choix invalide\n");
    }
    // Lancer le menu principal
    mainMenu(&player);

    return 0;
}

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
                CentreSupemon(player);
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
