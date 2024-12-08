//
// Created by stephane on 12/11/24.
//
#include "entree.h"
#include "mon_malloc.h"
#include "liste.h"
#include "utils.h"

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

    //  t_entree_creer
    t_entree *entree = t_entree_creer("protocole");

    //  t_entree_ajouter
    entree->liste = t_liste_ajouter(entree->liste, "protocole de communication", "def. du prot de comm.");
    entree->liste = t_liste_ajouter(entree->liste, "protocole", "def. de protocole.");

    //  t_entree_afficher
    char *nom_fichier_test = "../_t_entree_test.txt";
    utils_stdout_vers_fichier(nom_fichier_test);
    t_entree_afficher(entree);
    utils_stdout_vers_fichier(NULL);
    char *lignes1[] = {
            "[protocole] : protocole : def. de protocole. - protocole de communication : def. du prot de comm.\n"};
    utils_verifier_fichier(nom_fichier_test, lignes1, 1);

    //  sans redirection
//    printf("Obtenu  : ");
//    t_entree_afficher(entree);
//    printf("Attendu : [protocole] : protocole : def. de protocole. - protocole de communication : def. du prot de comm.\n");

    //  t_entree_get_mot
    assert(strcmp(t_entree_get_mot(entree), "protocole") == 0);

    //  t_entree_chercher
    const char *expression, *definition;
    t_entree_chercher(entree, "Qu'est-ce qu'un protocole en technologie de l'information ?", &expression, &definition);
    assert(strcmp(expression, "protocole") == 0);
    assert(strcmp(definition, "def. de protocole.") == 0);

    t_entree_chercher(entree, "C'est quoi un protocole de communication en informatique ?", &expression, &definition);
    assert(strcmp(expression, "protocole de communication") == 0);
    assert(strcmp(definition, "def. du prot de comm.") == 0);

    //  t_entree_ecrire_fichier
    //  - creation fichier temporaire
    FILE *fichier = fopen(nom_fichier_test, "w");
    t_entree_ecrire_fichier(fichier, entree);
    fclose(fichier);

    //  - verification du fichier
    char *lignes2[] = {"protocole : def. de protocole.\n", "protocole de communication : def. du prot de comm.\n"};
    utils_verifier_fichier(nom_fichier_test, lignes2, 2);

    //  t_entree_liberer
    t_entree_liberer(entree);

    assert(mon_rapport(false) == 0);

    printf("TEST entree : OK\n");
}
