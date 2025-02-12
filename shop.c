#include "header.h"


void shop(Player *player) {
    int choice;
    do {
        printf(BOLD "----------------------------------------\n\n" RESET);
        printf(BOLD MAGENTA "Bienvenue à la boutique !\n\n" RESET);
        printf(BOLD "----------------------------------------\n\n" RESET);
        printf(CYAN "Vous avez "GREEN"%d Supcoins.\n" RESET, player->supcoins);
        printf(BLUE "1. Acheter Potion: " YELLOW "100 Supcoins\n" RESET);
        printf(BLUE "2. Acheter Super Potion: "YELLOW"300 Supcoins\n" RESET);
        printf(BLUE "3. Acheter Bonbon Giga Rare: "YELLOW"700 Supcoins\n" RESET);
        printf(GREEN "4. Vendre des items\n" RESET);
        printf(RED "5. Quitter la boutique\n" RESET);
        printf(CYAN "\nChoisissez une option : " RESET);

        if (scanf("%d", &choice) != 1) {
            // If input is not an integer, clear the input buffer and set choice to an invalid value
            while (getchar() != '\n');
            choice = -1;
        }

        system("clear");

        switch (choice) {
            case 1:
                if (player->supcoins >= 100 && player->itemCount < MAX_ITEMS) {
                    player->supcoins -= 100;
                    strcpy(player->items[player->itemCount].name, "Potion");
                    player->items[player->itemCount].price = 100;
                    player->items[player->itemCount].effectValue = 5;
                    player->itemCount++;
                    printf(GREEN "\nTu as acheté une Potion!\n" RESET);
                } else {
                    printf(RED "C'est la desh ou t'as plus de place.\n" RESET);
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
                    printf(RED "C'est la desh ou t'as plus de place.\n" RESET);
                }
                break;
            case 3:
                if (player->supcoins >= 700 && player->itemCount < MAX_ITEMS) {
                    player->supcoins -= 700;
                    strcpy(player->items[player->itemCount].name, "Bonbon Giga Rare");
                    player->items[player->itemCount].price = 700;
                    player->items[player->itemCount].effectValue = 1; 
                    player->itemCount++;
                    printf(GREEN "Tu as acheté un Bonbon Giga Rare !\n" RESET);
                } else {
                    printf(RED "C'est la desh ou t'as plus de place.\n" RESET);
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

    printf(GREEN "Voici vos items :\n" RESET);
    for (int i = 0; i < player->itemCount; i++) {
        printf(BLUE "%d. %s "YELLOW"(Prix de vente: %d Supcoins)\n" RESET, i + 1, player->items[i].name, player->items[i].price/2);
    }

    int choice;
    printf(CYAN "Choisissez un item à vendre (0 pour annuler) : " RESET);

    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        choice = -1;
    }

    system("clear");

    if (choice > 0 && choice <= player->itemCount) {
        int sellPrice = player->items[choice - 1].price / 2;
        player->supcoins += sellPrice;
        printf(GREEN "Vous avez vendu %s pour %d Supcoins.\n" RESET, player->items[choice - 1].name, sellPrice);

        for (int i = choice - 1; i < player->itemCount - 1; i++) {
            player->items[i] = player->items[i + 1];
        }
        player->itemCount--;
    } else if (choice != 0) {
        printf(RED "Choix invalide.\n" RESET);
    }
}