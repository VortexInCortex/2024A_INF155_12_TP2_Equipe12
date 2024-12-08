//
// Created by stephane on 12/11/24.
//
#include "entree.h"
#include "mon_malloc.h"
#include "liste.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
	t_entree *entree = (t_entree *) malloc(sizeof(t_entree));

	entree->mot = (char *) malloc(sizeof(mot));
	strcpy(entree->mot, mot);

	entree->liste = t_liste_creer_vide();

	return entree;
}

void t_entree_liberer(t_entree *entree) {
	free(entree->mot);
	t_liste_liberer(entree->liste);
	free(entree);
}

void t_entree_afficher(const t_entree *entree) {
	printf("%s", entree->mot);
	t_liste_afficher(entree->liste);
}

char *t_entree_get_mot(const t_entree *entree) {
	assert(entree != NULL);
	return entree->mot;
}

void t_entree_chercher(t_entree *entree, const char *question, const char **expression, const char **definition) {
	t_liste_chercher(entree->liste, question, expression, definition);
}

void t_entree_ajouter(t_entree *entree, const char *expression, const char *definition) {
	t_liste_ajouter(entree->liste, expression, definition);
}

void t_entree_ecrire_fichier(FILE *fichier, const t_entree *entree) {
	assert(entree != NULL);
	t_liste_ecrire_fichier(fichier, entree->liste);
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
