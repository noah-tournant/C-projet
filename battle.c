#include "header.h"


void applyMove(Supemon *attacker, Supemon *defender, Move move) {
    // Calculer le taux de réussite de l'attaque
    float hitChance = (float)attacker->accuracy / (attacker->accuracy + defender->evasion) + 0.1;
    if ((float)rand() / RAND_MAX < hitChance) {
        // Attaque réussie
        if (move.damage > 0) {
            // Calculer les dégâts
            int damage = 1; // Default damage
            if (defender->defense > 0) {
                damage = (attacker->attack * move.damage) / defender->defense;
                if (damage <= 0) {
                    damage = 1; // Ensure at least 1 damage
                }
            }
            if (rand() % 2 == 0) {
                damage = (damage + 1) / 2; // Arrondir vers le haut
            } else {
                damage = damage / 2; // Arrondir vers le bas
            }
            defender->HP -= damage;
            if (defender->HP < 0) defender->HP = 0;
            printf(CYAN "%s utilise %s et "RED"inflige %d dégâts à "CYAN"%s.\n" RESET, attacker->name, move.name, damage, defender->name);
        }
        if (move.buff.value != 0) {
            // Appliquer les effets de buff/debuff
            if (move.buff.value > 0) {
                switch (move.buff.statType) {
                    case 1: attacker->attack += move.buff.value; break;
                    case 2: attacker->defense += move.buff.value; break;
                    case 3: attacker->evasion += move.buff.value; break;
                    case 4: attacker->accuracy += move.buff.value; break;
                    case 5: attacker->speed += move.buff.value; break;
                }
                printf(CYAN "%s utilise %s et "GREEN"augmente sa statistique de %d.\n" RESET, attacker->name, move.name, move.buff.value);
            } else {
                switch (move.buff.statType) {
                    case 1: defender->attack += move.buff.value; break;
                    case 2: defender->defense += move.buff.value; break;
                    case 3: defender->evasion += move.buff.value; break;
                    case 4: defender->accuracy += move.buff.value; break;
                    case 5: defender->speed += move.buff.value; break;
                }
                printf(CYAN "%s utilise %s et"BLUE"diminue la statistique de %d de %s.\n" RESET, attacker->name, move.name, -move.buff.value, defender->name);
            }
        }
    } else {
        // Attaque ratée
        printf(MAGENTA "%s a raté son attaque !\n" RESET, attacker->name);
    }
}

void captureSupemon(Player *player, Supemon *enemySupemon) {
    float captureRate = ((float)(enemySupemon->maxHP - enemySupemon->HP) / enemySupemon->maxHP) - 0.5;
    if (captureRate < 0) captureRate = 0; // Ensure capture rate is not negative

    if ((float)rand() / RAND_MAX < captureRate) {
        if (player->supemonCount < MAX_SUPEMON) {
            addSupemon(player, *enemySupemon);
            printf(GREEN "Vous avez capturé %s !\n" RESET, enemySupemon->name);
        } else {
            printf(RED "Vous avez déjà le nombre maximum de Supémons.\n" RESET);
        }
    } else {
        printf(RED "La capture a échoué.\n" RESET);
    }
}

void battle(Player *player) {
    Supemon *playerSupemon = NULL;
    player->selectedSupemonIndex = 0; // Sélectionner le premier Supémon par défaut
    if (player->selectedSupemonIndex < 0 || player->selectedSupemonIndex >= player->supemonCount) {
        printf(RED "Erreur: Supémon sélectionné invalide.\n" RESET);
        return;
    }
    playerSupemon = &player->supemons[player->selectedSupemonIndex];
    Supemon enemySupemon;

    // Sélectionner un Supémon sauvage au hasard
    int randomIndex = rand() % supemonsSauvagesCount;
    enemySupemon = supemonsSauvages[randomIndex];

    // Déterminer qui commence
    int playerTurn = (playerSupemon->speed > enemySupemon.speed) ? 1 : 0;
        
    while (playerSupemon->HP > 0 && enemySupemon.HP > 0) {
        printf(CYAN "PV de %s: %d\n" RESET, playerSupemon->name, playerSupemon->HP);
        printf(RED "PV de l'ennemi %s: %d\n" RESET, enemySupemon.name, enemySupemon.HP);
        if (playerTurn) {
            // Tour du joueur
            int action;
            printf(CYAN "Choisissez une action :\n"RED"1. Attaque\n"BLUE"2. Changer de Supémon\n"CYAN"3. Utiliser un objet\n"YELLOW"4. Fuir\n"GREEN"5. Capturer\n\n" RESET);
            scanf("%d", &action);
            playerTurn = 0; // Passer le tour à l'ennemi

            switch (action) {
                case 1:
                    // Le joueur choisit une attaque
                    printf(CYAN "Choisissez un mouvement :\n" RESET);
                    for (int i = 0; i < MAX_MOVES; i++) {
                        if (playerSupemon->moves[i].name[0] != '\0') {
                            printf(RED"%d. %s\n" RESET, i + 1, playerSupemon->moves[i].name);
                        } else {
                            printf(RED"%d. (Aucun mouvement)\n" RESET, i + 1);
                        }
                    }
                    int moveIndex;
                    scanf("%d", &moveIndex);
                    if (moveIndex > 0 && moveIndex <= MAX_MOVES) {
                        applyMove(playerSupemon, &enemySupemon, playerSupemon->moves[moveIndex - 1]);
                    } else {
                        printf(RED "Mouvement invalide.\n" RESET);
                    }
                    break;
                case 2:
                    // Le joueur change de Supémon
                    printf(CYAN "Choisissez un Supémon :\n" RESET);
                    for (int i = 0; i < player->supemonCount; i++) {
                        printf(BLUE"%d. %s\n", i + 1, player->supemons[i].name);
                    }
                    int supemonIndex;
                    scanf("%d", &supemonIndex);
                    if (supemonIndex > 0 && supemonIndex <= player->supemonCount) {
                        player->selectedSupemonIndex = supemonIndex - 1;
                        playerSupemon = &player->supemons[player->selectedSupemonIndex];
                        printf(GREEN "Vous avez changé pour"BLUE" %s.\n" RESET, playerSupemon->name);
                    } else {
                        printf(RED "Choix invalide.\n" RESET);
                    }
                    break;
                case 3:
                    // Le joueur utilise un objet
                    break;
                case 4:
                    {
                        float runChance = (float)playerSupemon->speed / (playerSupemon->speed + enemySupemon.speed);
                        if ((float)rand() / RAND_MAX < runChance) {
                            printf(GREEN "Vous avez réussi à fuir !\n" RESET);
                            return; // Terminer le combat
                        } else {
                            printf(RED "La fuite a échoué !\n" RESET);
                        }
                    }
                    break;
                case 5:
                    // Le joueur essaie de capturer le Supémon ennemi
                    captureSupemon(player, &enemySupemon);
                    break;
                default:
                    printf(RED "Action invalide. Réessayez.\n" RESET);
            }
        } else {
            // Tour de l'ennemi
            int moveIndex = rand() % MAX_MOVES;
            Move enemyMove = enemySupemon.moves[moveIndex];
            printf(RED "L'ennemi %s utilise %s !\n" RESET, enemySupemon.name, enemyMove.name);
            applyMove(&enemySupemon, playerSupemon, enemyMove);
            playerTurn = 1; // Passer le tour au joueur
        }
    }

    if (playerSupemon->HP <= 0) {
        printf(RED "Votre Supémon est KO !\n" RESET);
    } else {
        printf(GREEN "Vous avez vaincu le %s sauvage !\n" RESET, enemySupemon.name);
        // Récompenser le joueur
    }
}