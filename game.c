#include "header.h"



void initSupemon(Supemon *supemon, const char *name, int level, int maxHP,int hp, int attack, int defense, int evasion, int accuracy, int speed, Move moves[MAX_MOVES]) {
    supemon->level = level;
    supemon->experience = 0;
    supemon->maxHP = maxHP;
    supemon->HP = hp;
    supemon->attack = attack;
    supemon->defense = defense;
    supemon->evasion = evasion;
    supemon->accuracy = accuracy;
    supemon->speed = speed;
    for (int i = 0; i < MAX_MOVES; i++) {
        supemon->moves[i] = moves[i];
    }
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


Supemon wildSupemons[10];  // Tableau de Supémons sauvages
int wildSupemonCount = 0;  // Compteur pour suivre le nombre de Supémons sauvages

// Fonction pour ajouter un Supemon à la liste des Supémons sauvages
void addSupemonsauvage(Supemon supemon) {
    if (wildSupemonCount < 10) {
        wildSupemons[wildSupemonCount] = supemon;  // Ajouter le Supemon à la liste
        wildSupemonCount++;  // Incrémenter le compteur
    } else {
        printf("La liste des Supémons sauvages est pleine !\n");
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