#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "paire.h"
#include "donnees.h"
#include "liste.h"
#include "entree.h"
#include "chatBot.h"
#include "mon_malloc.h"


void tests() {
    utils_test(); //  0 mallocs
    t_paire_test(); //  6 mallocs
    t_liste_test(); //  8 mallocs
    t_entree_test(); //  10 mallocs
    t_donnees_test(); //  38 mallocs
    chatBot_test(); //  14 mallocs
    printf("Fin des tests!\n");

    mon_rapport(true);

    printf("Sur tous les tests, il y a 76 allocations/desallocations...\n");
}

int main(int argc, char **argv) {
    tests();
//    chatBot("bd_complete.txt");
    return 0;

    if (argc != 2) {
        fprintf(stderr, "Usage : ./ChatBotV2 <nom fichier donnees>\n");
        fprintf(stderr, "        ./ChatBotV2 -debug\n");
        fprintf(
                stderr,
                "NOTE: Le fichier de donnees doit se trouver dans le repertoire parent du repertoire ou se trouve l'executable.");
        exit(-1);
    }

    if (!strcmp(argv[1], "-debug")) {
        tests();
    } else {
        chatBot(argv[1]);
    }

    return 0;
}
