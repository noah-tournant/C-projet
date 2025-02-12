# C-projet

Voici la documentation pour votre projet C-projet :

## Fichiers du projet

### main.c
Ce fichier contient la fonction principale du programme et le menu principal.

#### Fonctions principales
- `int main()`: Point d'entrée du programme. Initialise le joueur et les Supémons, puis affiche le menu principal.
- `void mainMenu(Player *player)`: Affiche le menu principal et gère les choix de l'utilisateur.

### supemon.c
Ce fichier contient les fonctions pour initialiser et ajouter des Supémons et des joueurs.

#### Fonctions principales
- `void initSupemon(Supemon *supemon, const char *name, int level, int maxHP, int hp, int attack, int defense, int evasion, int accuracy, int speed, int exp, Move moves[MAX_MOVES])`: Initialise un Supémon avec les valeurs données.
- `void addSupemon(Player *player, Supemon supemon)`: Ajoute un Supémon à la liste des Supémons du joueur.
- `void addSupemonsauvage(Supemon supemon)`: Ajoute un Supémon sauvage à la liste des Supémons sauvages.
- `void initPlayer(Player *player, const char *name)`: Initialise un joueur avec le nom donné.

### shop.c
Ce fichier contient les fonctions pour gérer la boutique où les joueurs peuvent acheter et vendre des items.

#### Fonctions principales
- `void shop(Player *player)`: Affiche le menu de la boutique et gère les achats et ventes d'items.
- `void sellItems(Player *player)`: Affiche les items du joueur et permet de les vendre.

### header.h
Ce fichier contient les définitions des structures et les déclarations des fonctions utilisées dans le projet.

#### Structures principales
- `typedef struct { ... } Item`: Représente un item avec un nom, un prix et une valeur d'effet.
- `typedef struct { ... } Move`: Représente un mouvement avec un nom, des dégâts et un buff.
- `typedef struct { ... } Supemon`: Représente un Supémon avec des statistiques et des mouvements.
- `typedef struct { ... } Player`: Représente un joueur avec des Supcoins, des Supémons et des items.

### game.c
Ce fichier contient les fonctions pour sauvegarder et charger le jeu.

#### Fonctions principales
- `void saveGame(Player *player)`: Sauvegarde l'état du joueur dans un fichier.
- `void loadGame(Player *player)`: Charge l'état du joueur depuis un fichier.
- `void displayMenu(Player *player)`: Affiche le menu de démarrage et gère les choix de l'utilisateur.

### centre_supemon.c
Ce fichier contient la fonction pour soigner les Supémons du joueur.

#### Fonctions principales
- `void CentreSupemon(Player *player)`: Affiche le menu du Centre Supémon et soigne les Supémons du joueur.

### battle.c
Ce fichier contient les fonctions pour gérer les combats entre Supémons.

#### Fonctions principales
- `void gainExperience(Supemon *supemon, int exp)`: Ajoute de l'expérience à un Supémon et gère les montées de niveau.
- `void applyMove(Supemon *attacker, Supemon *defender, Move move)`: Applique un mouvement d'un Supémon attaquant à un Supémon défenseur.
- `int captureSupemon(Player *player, Supemon *enemySupemon)`: Tente de capturer un Supémon ennemi.
- `void useItem(Player *player, Supemon *supemon, int itemIndex)`: Utilise un item sur un Supémon.
- `void battle(Player *player)`: Gère un combat entre un Supémon du joueur et un Supémon sauvage.

## Utilisation
1. Compilez le projet avec un compilateur C.
2. Exécutez le programme.
3. Suivez les instructions à l'écran pour jouer au jeu.

## Auteur
Noah Tournant et Enzo Van-nieuwenborg
