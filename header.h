#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUPEMON 10
#define MAX_MOVES 5
#define MAX_ITEMS 10



#define MAX_SUPEMON 10
#define MAX_MOVES 5
#define MAX_ITEMS 10

// Définir une structure pour les mouvements
typedef struct {
    char name[20];
    int damage;
    int statChange;
} Move;

// Définir une structure pour les Supémons
typedef struct {
    char name[20];
    int level;
    int experience;
    int maxHP;
    int HP;
    int attack;
    int defense;
    int evasion;
    int accuracy;
    int speed;
    Move moves[MAX_MOVES];
} Supemon;

// Définir une structure pour les objets
typedef struct {
    char name[20];
    int price;
    int effectValue; // Par exemple, pour les potions : combien de HP ils ajoutent
} Item;

// Définir une structure pour le joueur
typedef struct {
    char name[50];
    int supcoins;
    Supemon supemons[MAX_SUPEMON];
    int supemonCount;
    Item items[MAX_ITEMS];
    int itemCount;
    Supemon *selectedSupemon;
} Player;

// Déclaration des fonctions
void initSupemon(Supemon *supemon, const char *name, int level, int maxHP, int attack, int defense, int evasion, int accuracy, int speed);
void initPlayer(Player *player, const char *name);
void addSupemon(Player *player, Supemon supemon);
void displaySupemon(Supemon *supemon);
void attack(Supemon *attacker, Supemon *defender);
void saveGame(Player *player);
void loadGame(Player *player);
void mainMenu(Player *player);

#endif // HEADER_H
