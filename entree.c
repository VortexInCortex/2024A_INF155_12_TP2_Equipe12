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
	// Allocation dynamique de mémoire pour toutes les variables inclue dans t_entree
	/* Aucun besoin de faire calloc() si on peut juste écraser les données précédentes à une
	 * adresse dans le stack (dans le cas où une valeur serai présente avant d'allouer un
	 * espace dans la mémoire)																*/

	/*t_entree *entree = (t_entree*)malloc(sizeof(t_entree*));
	entree->mot = (char*)malloc(sizeof(mot));
	entree->liste = (t_liste*)malloc(sizeof(t_liste*));

	// Initialisation d'un mot de l'entree?
	entree->mot = 0;
	entree->liste = 0;

	return entree;*/

	return NULL;
}

void t_entree_liberer(t_entree *entree) {
	// Libérer l'espace mémoire du mot et de la liste de paire
	if (entree != NULL) {
		mon_free(entree->mot);
		mon_free(entree->liste);
		mon_free(entree);
	} else { return; }
}

/***********************************************/
				/*QUESTIONS*/
// est ce qu'on est supposer afficher les informations d'entree dans un certaine ordre?
// est ce que je doit aussi afficher la liste de paires expression/définition?
// comment je fait pour afficher la liste de paire et la prochaine paire?
// comment je doit utiliser la variable "mot"
/***********************************************/
void t_entree_afficher(const t_entree *entree) {
	while (entree != NULL) {
		printf("%s", entree->mot);
		t_liste_afficher(entree->liste);
	}

	//printf("%s", entree->mot);
	//printf("%p", entree->liste); // ??? //
}

char *t_entree_get_mot(const t_entree *entree) {
	assert(entree != NULL);
	return entree->mot;
}

void t_entree_chercher(t_entree *entree, const char *question, const char **expression, const char **definition) {
	/*const int size_question = (int) strlen(question);
	const int size_expression = (int) strlen(&&expression);

	for (int index_question = 0; index_question < size_question; index_question++) {
		for (int index_expr = 0; index_expr < )
	}*/

	t_entree *plus_longue_expr = (t_entree*)malloc(sizeof(t_entree));

	while (entree != NULL) {
		for (int index_question = 0; index_question < strlen(question); index_question++) {
			/*********************************/
			if (strcmp(t_entree_get_mot(entree), question)) {
				// ????
			}
			/*********************************/
			if (strcmp(&&expression, question)) {
				t_liste_chercher(entree->liste, question, expression, definition);
			}
			/*********************************/
		}
	}
}

void t_entree_ajouter(t_entree *entree, const char *expression, const char *definition) {
	/*t_entree *res = malloc(sizeof(t_entree));
	assert(res != NULL);

	res->mot = t_entree_get_mot(entree); // IDK
	res->liste = t_liste_ajouter(entree->liste, expression, definition);

	mon_free(res);*/

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
