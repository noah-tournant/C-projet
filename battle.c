#include "header.h"

void gainExperience(Supemon *supemon, int exp) {
    supemon->experience += exp;
    int expToNextLevel = 500 + (supemon->level - 1) * 1000;

    while (supemon->experience >= expToNextLevel) {
        supemon->experience -= expToNextLevel;
        supemon->level++;
        expToNextLevel = 500 + (supemon->level - 1) * 1000;

        // Increase stats by 30%
        supemon->maxHP = (int)(supemon->maxHP * 1.3 + (rand() % 2));
        supemon->attack = (int)(supemon->attack * 1.3 + (rand() % 2));
        supemon->defense = (int)(supemon->defense * 1.3 + (rand() % 2));
        supemon->speed = (int)(supemon->speed * 1.3 + (rand() % 2));
        supemon->accuracy = (int)(supemon->accuracy * 1.3 + (rand() % 2));
        supemon->evasion = (int)(supemon->evasion * 1.3 + (rand() % 2));
        supemon->HP =(int)(supemon->maxHP);

        printf(GREEN "%s a atteint le niveau %d !\n" RESET, supemon->name, supemon->level);
    }
}

void applyMove(Supemon *attacker, Supemon *defender, Move move) {
    float hitChance = (float)attacker->accuracy / (attacker->accuracy + defender->evasion) + 0.1;
    if ((float)rand() / RAND_MAX < hitChance) {
        if (move.damage > 0) {
            int damage = 1;
            if (defender->defense > 0) {
                damage = (attacker->attack * move.damage) / defender->defense;
                if (damage <= 0) {
                    damage = 1; 
                }
            }
            if (rand() % 2 == 0) {
                damage = (damage + 1) / 2; 
            } else {
                damage = damage / 2; 
            }
            defender->HP -= damage;
            if (defender->HP < 0) defender->HP = 0;
            printf(CYAN "%s utilise %s et "RED"inflige %d dégâts à "CYAN"%s.\n\n" RESET, attacker->name, move.name, damage, defender->name);
        }
        if (move.buff.value != 0) {
            if (move.buff.value > 0) {
                switch (move.buff.statType) {
                    case 1: attacker->attack += move.buff.value; break;
                    case 2: attacker->defense += move.buff.value; break;
                    case 3: attacker->evasion += move.buff.value; break;
                    case 4: attacker->accuracy += move.buff.value; break;
                    case 5: attacker->speed += move.buff.value; break;
                }
                printf(CYAN "%s "CYAN" utilise "BLUE"%s "CYAN"et "GREEN"augmente sa statistique de %d.\n" RESET, attacker->name, move.name, move.buff.value);
            } else {
                switch (move.buff.statType) {
                    case 1: defender->attack += move.buff.value; break;
                    case 2: defender->defense += move.buff.value; break;
                    case 3: defender->evasion += move.buff.value; break;
                    case 4: defender->accuracy += move.buff.value; break;
                    case 5: defender->speed += move.buff.value; break;
                }
                printf(RED "%s"CYAN" utilise"BLUE" %s"CYAN" et"MAGENTA" diminue la statistique de %d de %s.\n" RESET, attacker->name, move.name, -move.buff.value, defender->name);
            }
        }
    } else {
        printf(RED "%s"MAGENTA" a raté son attaque !\n" RESET, attacker->name);
    }
}

int captureSupemon(Player *player, Supemon *enemySupemon) {
    float captureRate = ((float)(enemySupemon->maxHP - enemySupemon->HP) / enemySupemon->maxHP) - 0.5;
    if (captureRate < 0) captureRate = 0;

    if ((float)rand() / RAND_MAX < captureRate) {
        if (player->supemonCount < MAX_SUPEMON) {
            addSupemon(player, *enemySupemon);
            printf(GREEN "Vous avez capturé"BLUE" %s !\n" RESET, enemySupemon->name);
            return 1;
        } else {
            printf(RED "Vous avez déjà le nombre maximum de Supémons.\n" RESET);
        }
    } else {
        printf(RED "La capture a échoué.\n" RESET);
    }
    return 0;
}

void useItem(Player *player, Supemon *supemon, int itemIndex) {
    if (itemIndex < 0 || itemIndex >= player->itemCount) {
        printf(RED "Item invalide.\n" RESET);
        return;
    }

    Item *item = &player->items[itemIndex];
    if (strcmp(item->name, "Potion") == 0) {
        supemon->HP += 5;
        if (supemon->HP > supemon->maxHP) {
            supemon->HP = supemon->maxHP;
        }
        printf(GREEN "%s utilise une Potion et récupère 5 PV.\n" RESET, supemon->name);
    } else if (strcmp(item->name, "Super Potion") == 0) {
        supemon->HP += 10;
        if (supemon->HP > supemon->maxHP) {
            supemon->HP = supemon->maxHP;
        }
        printf(GREEN "%s utilise une Super Potion et récupère 10 PV.\n" RESET, supemon->name);
    } else if (strcmp(item->name, "Bonbon Giga Rare") == 0) {
        gainExperience(supemon, 500 + (supemon->level - 1) * 1000); // Add enough experience to level up
        printf(GREEN "%s utilise un Bonbon Giga Rare et gagne un niveau.\n" RESET, supemon->name);
    }

    for (int i = itemIndex; i < player->itemCount - 1; i++) {
        player->items[i] = player->items[i + 1];
    }
    player->itemCount--;
    player->items[player->itemCount].name[0] = '\0';
}

void battle(Player *player) {
    Supemon *playerSupemon = NULL;
    int supemonIndex;
    do {
        printf(CYAN "Choisissez un Supémon pour le combat :\n" RESET);
        for (int i = 0; i < player->supemonCount; i++) {
            printf(BLUE"%d. %s (HP: %d/%d)\n" RESET, i + 1, player->supemons[i].name, player->supemons[i].HP, player->supemons[i].maxHP);
        }
        if (scanf("%d", &supemonIndex) != 1) {
            while (getchar() != '\n');
            supemonIndex = -1;
        }
        supemonIndex--;
        if (supemonIndex < 0 || supemonIndex >= player->supemonCount || player->supemons[supemonIndex].HP == 0) {
            printf(RED "Choix invalide. Veuillez choisir un Supémon avec des PV.\n" RESET);
        }
    } while (supemonIndex < 0 || supemonIndex >= player->supemonCount || player->supemons[supemonIndex].HP == 0);

    player->selectedSupemonIndex = supemonIndex;
    playerSupemon = &player->supemons[player->selectedSupemonIndex];
    Supemon enemySupemon;
    
    srand(time(NULL));

    int randomIndex = rand() % supemonsSauvagesCount;
    enemySupemon = supemonsSauvages[randomIndex];

    enemySupemon.level = playerSupemon->level;
    for (int i = 1; i < enemySupemon.level; i++) {
        enemySupemon.maxHP = (int)(enemySupemon.maxHP * 1.3 + (rand() % 2));
        enemySupemon.attack = (int)(enemySupemon.attack * 1.3 + (rand() % 2));
        enemySupemon.defense = (int)(enemySupemon.defense * 1.3 + (rand() % 2));
        enemySupemon.speed = (int)(enemySupemon.speed * 1.3 + (rand() % 2));
        enemySupemon.accuracy = (int)(enemySupemon.accuracy * 1.3 + (rand() % 2));
        enemySupemon.evasion = (int)(enemySupemon.evasion * 1.3 + (rand() % 2));
    }
    enemySupemon.HP = enemySupemon.maxHP;
    int playerTurn = (playerSupemon->speed > enemySupemon.speed) ? 1 : 0;
    printf(BLUE "%s "GREEN"sauvage apparaît !\n" RESET, enemySupemon.name);
    int itemsUsed = 0;
    while (playerSupemon->HP > 0 && enemySupemon.HP > 0) {
        
        printf(BLUE "PV de %s:"GREEN" %d\n" RESET, playerSupemon->name, playerSupemon->HP);
        printf(RED "PV de %s:"GREEN" %d\n\n" RESET, enemySupemon.name, enemySupemon.HP);
        if (playerTurn) {
            int action;
            printf(CYAN "Choisissez une action :\n"RED"1. Attaque\n"BLUE"2. Changer de Supémon\n"CYAN"3. Utiliser un objet\n"YELLOW"4. Fuir\n"GREEN"5. Capturer\n\n" RESET);
            if (scanf("%d", &action) != 1) {
                while (getchar() != '\n');
                action = -1;
            }
            system("clear");
            playerTurn = 0; 

            switch (action) {
                case 1:
                    printf(CYAN "Choisissez un mouvement :\n" RESET);
                    for (int i = 0; i < MAX_MOVES; i++) {
                        if (playerSupemon->moves[i].name[0] != '\0') {
                            printf(RED"%d. %s\n" RESET, i + 1, playerSupemon->moves[i].name);
                        } else {
                            printf(RED"%d. (Aucun mouvement)\n" RESET, i + 1);
                        }
                    }
                    int moveIndex;
                    if (scanf("%d", &moveIndex) != 1) {
                        while (getchar() != '\n');
                        moveIndex = -1;
                    }
                    system("clear");
                    if (moveIndex > 0 && moveIndex <= MAX_MOVES) {
                        applyMove(playerSupemon, &enemySupemon, playerSupemon->moves[moveIndex - 1]);
                    } else {
                        printf(RED "Mouvement invalide.\n" RESET);
                    }
                    break;
                case 2:
                    printf(CYAN "Choisissez un Supémon :\n" RESET);
                    for (int i = 0; i < player->supemonCount; i++) {
                        printf(BLUE"%d. %s\n" RESET, i + 1, player->supemons[i].name);
                    }
                    if (scanf("%d", &supemonIndex) != 1) {
                        while (getchar() != '\n');
                        supemonIndex = -1;
                    }
                    if (supemonIndex > 0 && supemonIndex <= player->supemonCount) {
                        player->selectedSupemonIndex = supemonIndex - 1;
                        playerSupemon = &player->supemons[player->selectedSupemonIndex];
                        printf(GREEN "Vous avez changé pour"BLUE" %s.\n" RESET, playerSupemon->name);
                    } else {
                        printf(RED "Choix invalide.\n" RESET);
                    }
                    break;
                case 3:
                    if (itemsUsed < 4) {
                        printf(CYAN "Choisissez un objet :\n" RESET);
                        for (int i = 0; i < player->itemCount; i++) {
                            printf(BLUE"%d. %s\n" RESET, i + 1, player->items[i].name);
                        }
                        int itemIndex;
                        if (scanf("%d", &itemIndex) != 1) {
                            while (getchar() != '\n');
                            itemIndex = -1;
                        }
                        system("clear");
                        if (itemIndex > 0 && itemIndex <= player->itemCount) {
                            useItem(player, playerSupemon, itemIndex - 1);
                            itemsUsed++;
                        } else {
                            printf(RED "Objet invalide.\n" RESET);
                        }
                    } else {
                        printf(RED "Vous avez déjà utilisé le nombre maximum d'objets dans ce combat.\n" RESET);
                    }
                    break;
                case 4:
                    {
                        float runChance = (float)playerSupemon->speed / (playerSupemon->speed + enemySupemon.speed);
                        if ((float)rand() / RAND_MAX < runChance) {
                            printf(GREEN "Vous avez réussi à fuir !\n" RESET);
                            return; 
                        } else {
                            printf(RED "La fuite a échoué !\n" RESET);
                        }
                    }
                    break;
                case 5:
                    if (captureSupemon(player, &enemySupemon)) {
                        printf("Bien joué tu as capturé le %s\n" , enemySupemon.name);
                        return; 
                    }
                    break;
                default:
                    printf(RED "Action invalide. Réessayez.\n" RESET);
            }
        } else {
            int moveIndex = rand() % MAX_MOVES;
            Move enemyMove = enemySupemon.moves[moveIndex];
            printf(CYAN "L'ennemi "RED"%s "CYAN"utilise"BLUE" %s !\n\n" RESET, enemySupemon.name, enemyMove.name);
            applyMove(&enemySupemon, playerSupemon, enemyMove);
            playerTurn = 1;
        }
    }

    if (playerSupemon->HP <= 0) {
        printf(RED "Votre Supémon est KO !\n" RESET);
    } else {
        printf(GREEN "Vous avez vaincu le %s sauvage !\n" RESET, enemySupemon.name);
        int expGained = 500;
        gainExperience(playerSupemon, expGained);
        int goldReward = 300;
        player->supcoins += goldReward;
        printf(GREEN "Vous avez gagné 300 Supcoins !\n");
    }
}