#include "header.h"


void CentreSupemon(Player *player) {
    int choice;
    printf(BOLD "----------------------------------------\n" RESET);
    printf(BOLD MAGENTA "Bienvenue au Centre Supémon !\n" RESET);
    printf(BOLD "----------------------------------------\n" RESET);
    printf(CYAN "Voici vos Supémons :\n" RESET);
    for (int i = 0; i < player->supemonCount; i++) {
        printf(GREEN "%d. %s (HP: %d/%d)\n" RESET, i + 1, player->supemons[i].name, player->supemons[i].HP, player->supemons[i].maxHP);
    }
    printf(YELLOW "Voulez-vous soigner tous vos Supémons ? (1: Oui, 2: Non) : " RESET);
    scanf("%d", &choice);

    if (choice == 1) {
        for (int i = 0; i < player->supemonCount; i++) {
            player->supemons[i].HP = player->supemons[i].maxHP;
        }
        printf(GREEN "Tous vos Supémons ont été soignés !\n" RESET);
    } else {
        printf(RED "Vos Supémons n'ont pas été soignés.\n" RESET);
    }
}