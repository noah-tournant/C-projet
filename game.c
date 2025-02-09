#include "header.h"



void initSupemon(Supemon *supemon, const char *name, int level, int maxHP,int hp, int attack, int defense, int evasion, int accuracy, int speed, Move moves[MAX_MOVES]) {
    supemon->level = level;
    supemon->maxHP = maxHP;
    supemon->HP = hp;
    supemon->attack = attack;
    supemon->defense = defense;
    supemon->evasion = evasion;
    supemon->accuracy = accuracy;
    supemon->speed = speed;
    supemon->experience = 0; // Initialiser l'expérience à 0
    for (int i = 0; i < MAX_MOVES; i++) {
        supemon->moves[i] = moves[i];
    }
}

void addSupemon(Player *player, Supemon supemon) {
    if (player->supemonCount < MAX_SUPEMON) {
        player->supemons[player->supemonCount++] = supemon;
    }
}

Supemon supemonsSauvages[MAX_SUPEMON];
int supemonsSauvagesCount = 0;

void addSupemonsauvage(Supemon supemon) {
    if (supemonsSauvagesCount < MAX_SUPEMON) {
        supemonsSauvages[supemonsSauvagesCount++] = supemon;
    } else {
        printf("La liste des Supémons sauvages est pleine.\n");
    }
}

void initPlayer(Player *player, const char *name) {
    strcpy(player->name, name);
    player->supcoins = 1000;
    player->supemonCount = 0;
    player->itemCount = 0;
    player->selectedSupemonIndex = 0;
}

void displaySupemon(Supemon *supemon) {
    printf("Nom: %s\n", supemon->name);
    printf("Niveau: %d\n", supemon->level);
    printf("PV: %d/%d\n", supemon->HP, supemon->maxHP);
    printf("Attaque: %d\n", supemon->attack);
    printf("Défense: %d\n", supemon->defense);
    printf("Evasion: %d\n", supemon->evasion);
    printf("Précision: %d\n", supemon->accuracy);
    printf("Vitesse: %d\n", supemon->speed);
}

void applyMove(Supemon *attacker, Supemon *defender, Move move) {
    // Calculer le taux de réussite de l'attaque
    float hitChance = (float)attacker->accuracy / (attacker->accuracy + defender->evasion) + 0.1;
    if ((float)rand() / RAND_MAX < hitChance) {
        // Attaque réussie
        if (move.damage > 0) {
            // Calculer les dégâts
            int damage = (attacker->attack * move.damage) / defender->defense;
            if (rand() % 2 == 0) {
                damage = (damage + 1) / 2; // Arrondir vers le haut
            } else {
                damage = damage / 2; // Arrondir vers le bas
            }
            defender->HP -= damage;
            if (defender->HP < 0) defender->HP = 0;
            printf("%s utilise %s et inflige %d dégâts à %s.\n", attacker->name, move.name, damage, defender->name);
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
                printf("%s utilise %s et augmente sa statistique de %d.\n", attacker->name, move.name, move.buff.value);
            } else {
                switch (move.buff.statType) {
                    case 1: defender->attack += move.buff.value; break;
                    case 2: defender->defense += move.buff.value; break;
                    case 3: defender->evasion += move.buff.value; break;
                    case 4: defender->accuracy += move.buff.value; break;
                    case 5: defender->speed += move.buff.value; break;
                }
                printf("%s utilise %s et diminue la statistique de %d de %s.\n", attacker->name, move.name, -move.buff.value, defender->name);
            }
        }
    } else {
        // Attaque ratée
        printf("%s a raté son attaque !\n", attacker->name);
    }
}


void saveGame(Player *player) {
    FILE *file = fopen("savegame.dat", "wb");
    if (file != NULL) {
        fwrite(player, sizeof(Player), 1, file);
        fclose(file);
        printf("Sauvegarde réussie !\n");
    } else {
        printf("Erreur de sauvegarde.\n");
    }
}


void loadGame(Player *player) {
    FILE *file = fopen("savegame.dat", "rb");
    if (file != NULL) {
        fread(player, sizeof(Player), 1, file);
        fclose(file);
        printf("Chargement réussi !\n");
    } else {
        printf("Aucune sauvegarde trouvée.\n");
    }
}
 
void captureSupemon(Player *player, Supemon *enemySupemon) {
    float captureRate = ((float)(enemySupemon->maxHP - enemySupemon->HP) / enemySupemon->maxHP) - 0.5;
    if (captureRate < 0) captureRate = 0; // Ensure capture rate is not negative

    if ((float)rand() / RAND_MAX < captureRate) {
        if (player->supemonCount < MAX_SUPEMON) {
            addSupemon(player, *enemySupemon);
            printf("Vous avez capturé %s !\n", enemySupemon->name);
        } else {
            printf("Vous avez déjà le nombre maximum de Supémons.\n");
        }
    } else {
        printf("La capture a échoué.\n");
    }
}