#include <stdbool.h>
#include <stdio.h>

#include "utils.h"
#include "paire.h"
#include "donnees.h"
#include "liste.h"
#include "entree.h"
#include "chatBot.h"
#include "mon_malloc.h"

//#define TESTS true

void tests() {
    utils_test(); //  0 mallocs
    t_paire_test(); //  6 mallocs
    t_liste_test(); //  8 mallocs
    t_entree_test(); //  10 mallocs
    t_donnees_test(); //  1668 mallocs
    chatBot_test(); //  14 mallocs
    printf("Fin des tests!\n");

    mon_rapport(true);

    printf("Il devrait y avoir 1706 allocations/desallocations...\n");
}

int main(void) {
#if TESTS
    tests();
#else
    // decommenter l'une des 3 lignes suivantes selon la base de donnees que vous desirez
    // chatBot(NULL);   //  aucune base de connaissances
    // chatBot("../dictionnaire (test).txt");  //  base de connaissances minimale
    chatBot("../dictionnaire (complet).txt"); //  base de connaissances plus evoluee
#endif
    return 0;
}
