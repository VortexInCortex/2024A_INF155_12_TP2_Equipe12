//
// Created by stephane on 12/11/24.
//
#include "entree.h"
#include "mon_malloc.h"
#include "liste.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>

// ---------------------------------------------------------------
// Declaration de la structure des entrees pour la base de donnees
// ---------------------------------------------------------------
/**
 * @details la structure des entrees dans le tableau dynamiques des donnees.
 */
struct s_entree {
    char *mot;
    t_liste *liste;
};

//  ----------------------------------
//  Definition des fonctions publiques
//  ----------------------------------
t_entree *t_entree_creer(const char *mot) {
	// A completer
}

void t_entree_liberer(t_entree *entree) {
	// A completer
}

void t_entree_afficher(const t_entree *entree) {
	// A completer
}

char *t_entree_get_mot(const t_entree *entree) {
	// A completer
}

void t_entree_chercher(t_entree *entree, const char *question, const char **expression, const char **definition) {
	// A completer
}

void t_entree_ajouter(t_entree *entree, const char *expression, const char *definition) {
	// A completer
}

void t_entree_ecrire_fichier(FILE *fichier, const t_entree *entree) {
	// A completer
}

void t_entree_test() {
    printf("------------------------ TEST ENTREE ------------------------\n");

    t_entree *entree = t_entree_creer("protocole");
    entree->liste = t_liste_ajouter(entree->liste, "protocole de communication", "def. du prot de comm.");
    entree->liste = t_liste_ajouter(entree->liste, "protocole", "def. de protocole.");

    t_entree_afficher(entree);

    t_entree_liberer(entree);

    assert(mon_rapport(false) == 0);

    printf("TEST entree : OK\n");
}
