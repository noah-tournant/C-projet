#include "header.h"

void shop(Player *player) {
    int choice;
    do {
        printf("Welcome to the shop! You have %d Supcoins.\n", player->supcoins);
        printf("1. Buy Potion (100 Supcoins)\n");
        printf("2. Buy Super Potion (300 Supcoins)\n");
        printf("3. Buy Rare Candy (700 Supcoins)\n");
        printf("4. Sell items\n");
        printf("5. Exit shop\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (player->supcoins >= 100 && player->itemCount < MAX_ITEMS) {
                    player->supcoins -= 100;
                    strcpy(player->items[player->itemCount].name, "Potion");
                    player->items[player->itemCount].price = 100;
                    player->items[player->itemCount].effectValue = 5;
                    player->itemCount++;
                    printf("Tu as acheté une Potion!\n");
                } else {
                    printf("c'est la desh loser ou t'as plus de place.\n");
                }
                break;
            case 2:
                if (player->supcoins >= 300 && player->itemCount < MAX_ITEMS) {
                    player->supcoins -= 300;
                    strcpy(player->items[player->itemCount].name, "Super Potion");
                    player->items[player->itemCount].price = 300;
                    player->items[player->itemCount].effectValue = 10;
                    player->itemCount++;
                    printf("Tu as acheté une Super Potion!\n");
                } else {
                    printf("c'est la desh loser ou t'as plus de place.\n");
                }
                break;
            case 3:
                if (player->supcoins >= 700 && player->itemCount < MAX_ITEMS) {
                    player->supcoins -= 700;
                    strcpy(player->items[player->itemCount].name, "Bonbon Giga Rare");
                    player->items[player->itemCount].price = 700;
                    player->items[player->itemCount].effectValue = 1; // Rare Candy effect
                    player->itemCount++;
                    printf("Tu as acheté un Bonbon Giga Rare !\n");
                } else {
                    printf("c'est la desh loser ou t'as plus de place.\n");
                }
                break;
            case 4:
                sellItems(player);
                break;
            case 5:
                printf("Merci d'avoir visité la boutique!\n");
                break;
            default:
                printf("Choix invalide veuillez réessayer .\n");
        }
    } while (choice != 5);
}

void sellItems(Player *player) {
    if (player->itemCount == 0) {
        printf("Vous n'avez aucun item à vendre.\n");
        return;
    }

    printf("Voici vos items :\n");
    for (int i = 0; i < player->itemCount; i++) {
        printf("%d. %s (Prix de vente: %d Supcoins)\n", i + 1, player->items[i].name, player->items[i].price * 80 / 100);
    }

    int choice;
    printf("Choisissez un item à vendre (0 pour annuler) : ");
    scanf("%d", &choice);

    if (choice > 0 && choice <= player->itemCount) {
        int sellPrice = player->items[choice - 1].price * 80 / 100;
        player->supcoins += sellPrice;
        printf("Vous avez vendu %s pour %d Supcoins.\n", player->items[choice - 1].name, sellPrice);

        // Supprimer l'item vendu de l'inventaire
        for (int i = choice - 1; i < player->itemCount - 1; i++) {
            player->items[i] = player->items[i + 1];
        }
        player->itemCount--;
    } else if (choice != 0) {
        printf("Choix invalide.\n");
    }
}