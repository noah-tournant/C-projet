#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUPEMON 10
#define MAX_MOVES 2
#define MAX_ITEMS 10


// Définir une structure pour les objets
typedef struct {
    char name[50];
    int price;
    int effectValue; // Par exemple, pour les potions : combien de HP ils ajoutent
} Item;

// Définir une structure pour les mouvements
typedef struct {
    char name[50];
    int damage;
    struct {
        int value;
        int statType; // 1:atk, 2:def, 3:evasion, 4:accuracy, 5:speed
    } buff;
} Move;

typedef struct {
    char name[50];
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

// Définir une structure pour le joueur
typedef struct {
    char name[50];
    int supcoins;
    Supemon supemons[MAX_SUPEMON];
    int supemonCount;
    int selectedSupemonIndex;
    Item items[MAX_ITEMS];
    int itemCount;
    
} Player;

// Déclaration des fonctions
void initSupemon(Supemon *supemon, const char *name, int level, int maxHP, int hp,int attack, int defense, int evasion, int accuracy, int speed, Move moves[MAX_MOVES]);
void initPlayer(Player *player, const char *name);
void addSupemon(Player *player, Supemon supemon);
void displaySupemon(Supemon *supemon);
void attack(Supemon *attacker, Supemon *defender);
void saveGame(Player *player);
void loadGame(Player *player);
void mainMenu(Player *player);
void battle(Player *player);
void shop(Player *player);
void applyMove(Supemon *attacker, Supemon *defender, Move move);
void battle(Player *player);
void shop(Player *player);
void addSupemonsauvage(Supemon supemon);
void sell(Player *player);
void CentreSupemon(Player *player);
void captureSupemon(Player *player, Supemon *enemySupemon);
void sellItems(Player *player);
#endif // HEADER_H