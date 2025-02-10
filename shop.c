#include "header.h"


void shop(Player *player) {
    int choice;
    do {
        printf(BOLD "----------------------------------------\n" RESET);
        printf(BOLD MAGENTA "Bienvenue à la boutique !\n" RESET);
        printf(BOLD "----------------------------------------\n" RESET);
        printf(CYAN "Vous avez %d Supcoins.\n" RESET, player->supcoins);
        printf(GREEN "1. Acheter Potion (100 Supcoins)\n" RESET);
        printf(GREEN "2. Acheter Super Potion (300 Supcoins)\n" RESET);
        printf(GREEN "3. Acheter Bonbon Giga Rare (700 Supcoins)\n" RESET);
        printf(YELLOW "4. Vendre des items\n" RESET);
        printf(RED "5. Quitter la boutique\n" RESET);
        printf(CYAN "Choisissez une option : " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (player->supcoins >= 100 && player->itemCount < MAX_ITEMS) {
                    player->supcoins -= 100;
                    strcpy(player->items[player->itemCount].name, "Potion");
                    player->items[player->itemCount].price = 100;
                    player->items[player->itemCount].effectValue = 5;
                    player->itemCount++;
                    printf(GREEN "Tu as acheté une Potion!\n" RESET);
                } else {
                    printf(RED "C'est la desh loser ou t'as plus de place.\n" RESET);
                }
                break;
            case 2:
                if (player->supcoins >= 300 && player->itemCount < MAX_ITEMS) {
                    player->supcoins -= 300;
                    strcpy(player->items[player->itemCount].name, "Super Potion");
                    player->items[player->itemCount].price = 300;
                    player->items[player->itemCount].effectValue = 10;
                    player->itemCount++;
                    printf(GREEN "Tu as acheté une Super Potion!\n" RESET);
                } else {
                    printf(RED "C'est la desh loser ou t'as plus de place.\n" RESET);
                }
                break;
            case 3:
                if (player->supcoins >= 700 && player->itemCount < MAX_ITEMS) {
                    player->supcoins -= 700;
                    strcpy(player->items[player->itemCount].name, "Bonbon Giga Rare");
                    player->items[player->itemCount].price = 700;
                    player->items[player->itemCount].effectValue = 1; // Rare Candy effect
                    player->itemCount++;
                    printf(GREEN "Tu as acheté un Bonbon Giga Rare !\n" RESET);
                } else {
                    printf(RED "C'est la desh loser ou t'as plus de place.\n" RESET);
                }
                break;
            case 4:
                sellItems(player);
                break;
            case 5:
                printf(MAGENTA "Merci d'avoir visité la boutique!\n" RESET);
                break;
            default:
                printf(RED "Choix invalide, veuillez réessayer.\n" RESET);
        }
    } while (choice != 5);
}

void sellItems(Player *player) {
    if (player->itemCount == 0) {
        printf(RED "Vous n'avez aucun item à vendre.\n" RESET);
        return;
    }

    printf(CYAN "Voici vos items :\n" RESET);
    for (int i = 0; i < player->itemCount; i++) {
        printf(GREEN "%d. %s (Prix de vente: %d Supcoins)\n" RESET, i + 1, player->items[i].name, player->items[i].price * 80 / 100);
    }

    int choice;
    printf(YELLOW "Choisissez un item à vendre (0 pour annuler) : " RESET);
    scanf("%d", &choice);

    if (choice > 0 && choice <= player->itemCount) {
        int sellPrice = player->items[choice - 1].price * 80 / 100;
        player->supcoins += sellPrice;
        printf(GREEN "Vous avez vendu %s pour %d Supcoins.\n" RESET, player->items[choice - 1].name, sellPrice);

        // Supprimer l'item vendu de l'inventaire
        for (int i = choice - 1; i < player->itemCount - 1; i++) {
            player->items[i] = player->items[i + 1];
        }
        player->itemCount--;
    } else if (choice != 0) {
        printf(RED "Choix invalide.\n" RESET);
    }
}