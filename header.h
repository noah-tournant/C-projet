#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Déclarations des constantes
#define MAX_SUPEMON 100
#define MAX_MOVES 2
#define MAX_ITEMS 10

// Déclarations des structures
typedef struct {
    char name[50];
    int price;
    int effectValue; // Par exemple, pour les potions : combien de HP ils ajoutent
} Item;

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
    int HP;
    int maxHP;
    int attack;
    int defense;
    int speed;
    int accuracy;
    int evasion;
    Move moves[MAX_MOVES];
    int level;
    int experience;
} Supemon;

typedef struct {
    char name[50];
    int supcoins;
    int supemonCount;
    int itemCount;
    int selectedSupemonIndex;
    Supemon supemons[MAX_SUPEMON];
    Item items[MAX_ITEMS];
} Player;

// Déclaration des variables globales
extern Supemon supemonsSauvages[MAX_SUPEMON];
extern int supemonsSauvagesCount;

// Déclarations des fonctions
void initSupemon(Supemon *supemon, const char *name, int level, int maxHP, int hp, int attack, int defense, int evasion, int accuracy, int speed, Move moves[MAX_MOVES]);
void addSupemon(Player *player, Supemon supemon);
void addSupemonsauvage(Supemon supemon);
void initPlayer(Player *player, const char *name);
void applyMove(Supemon *attacker, Supemon *defender, Move move);
int captureSupemon(Player *player, Supemon *enemySupemon);
void battle(Player *player);
void displaySupemon(Supemon *supemon);
void attack(Supemon *attacker, Supemon *defender);
void saveGame(Player *player);
void loadGame(Player *player);
void mainMenu(Player *player);
void shop(Player *player);
void sell(Player *player);
void CentreSupemon(Player *player);
void sellItems(Player *player);
void gainExperience(Supemon *supemon, int exp);
#endif // HEADER_H