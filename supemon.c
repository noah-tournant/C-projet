#include "header.h"

// Définition globale de supemonsSauvages et supemonsSauvagesCount
Supemon supemonsSauvages[MAX_SUPEMON];
int supemonsSauvagesCount = 0;

void initSupemon(Supemon *supemon, const char *name, int level, int maxHP, int hp, int attack, int defense, int evasion, int accuracy, int speed, Move moves[MAX_MOVES]) {
    // Copier le nom du Supémon
    strcpy(supemon->name, name);
    
    // Initialiser les attributs du Supémon
    supemon->level = level;
    supemon->maxHP = maxHP;
    supemon->HP = hp;
    supemon->attack = attack;
    supemon->defense = defense;
    supemon->evasion = evasion;
    supemon->accuracy = accuracy;
    supemon->speed = speed;
    supemon->experience = 0; // Initialiser l'expérience à 0
    
    // Copier les mouvements du Supémon
    for (int i = 0; i < MAX_MOVES; i++) {
        supemon->moves[i] = moves[i];
    }
}

void addSupemon(Player *player, Supemon supemon) {
    if (player->supemonCount < MAX_SUPEMON) {
        player->supemons[player->supemonCount++] = supemon;
    }
}

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