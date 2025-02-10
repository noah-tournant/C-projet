#include "header.h"

void CentreSupemon(Player *player) {
    int choice;
    printf("----------------------------------------\n");
    printf("Bienvenue au Centre Supémon !\n");
    printf("Voici vos Supémons :\n");
    for (int i = 0; i < player->supemonCount; i++) {
        printf("%d. %s (HP: %d/%d)\n", i + 1, player->supemons[i].name, player->supemons[i].HP, player->supemons[i].maxHP);
    }
    printf("Voulez-vous soigner tous vos Supémons ? (1: Oui, 2: Non) : ");
    scanf("%d", &choice);

    if (choice == 1) {
        for (int i = 0; i < player->supemonCount; i++) {
            player->supemons[i].HP = player->supemons[i].maxHP;
        }
        printf("Tous vos Supémons ont été soignés !\n");
    } else {
        printf("Vos Supémons n'ont pas été soignés.\n");
    }
}