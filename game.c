#include "header.h"


void saveGame(Player *player) {
    FILE *file = fopen("savegame.dat", "wb");
    if (file != NULL) {
        fwrite(player, sizeof(Player), 1, file);
        fclose(file);
        printf("Sauvegarde réussie !\n");
    } else {
        printf("Erreur de sauvegarde.\n");
    }
}


void loadGame(Player *player) {
    FILE *file = fopen("savegame.dat", "rb");
    if (file != NULL) {
        fread(player, sizeof(Player), 1, file);
        fclose(file);
        printf("Chargement réussi !\n");
    } else {
        printf("Aucune sauvegarde trouvée.\n");
    }
}
 
