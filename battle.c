#include "header.h"

void battle(Player *player) {
    Supemon *playerSupemon = &player->supemons[player->selectedSupemonIndex];
    Supemon enemySupemon;

    // Sélectionner un Supémon sauvage au hasard
    int randomIndex = rand() % supemonsSauvagesCount;
    enemySupemon = supemonsSauvages[randomIndex];

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