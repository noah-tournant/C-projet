#include "header.h"



void initSupemon(Supemon *supemon, const char *name, int level, int maxHP, int attack, int defense, int evasion, int accuracy, int speed, char *spell1, char *spell2) {
    strcpy(supemon->name, name);
    supemon->level = level;
    supemon->experience = 0;
    supemon->maxHP = maxHP;
    supemon->HP = maxHP;
    supemon->attack = attack;
    supemon->defense = defense;
    supemon->evasion = evasion;
    supemon->accuracy = accuracy;
    supemon->speed = speed;
    supermon->spell1= spell1;
    supermon->spell2= spell2;
    
}

void initPlayer(Player *player, const char *name) {
    strcpy(player->name, name);
    player->supcoins = 500; 
    player->supemonCount = 0;
    player->itemCount = 0;
}


void addSupemon(Player *player, Supemon supemon) {
    if (player->supemonCount < MAX_SUPEMON) {
        player->supemons[player->supemonCount] = supemon;
        player->supemonCount++;
    } else {
        printf("Vous ne pouvez pas avoir plus de Supémons.\n");
    }
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
    printf("1er sort: %d\n", supemon->spell1;)
    printf("2eme sort: %d\n", supemon->spell2;)
}


void attack(Supemon *attacker, Supemon *defender) {
    int hitChance = attacker->accuracy * 100 / (attacker->accuracy + defender->evasion) + 10;
    if (rand() % 100 < hitChance) {
        // Attaque réussie
        int damage = (attacker->attack * 3) / defender->defense;
        defender->HP -= damage;
        printf("%s attaque %s et inflige %d dégâts.\n", attacker->name, defender->name, damage);
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