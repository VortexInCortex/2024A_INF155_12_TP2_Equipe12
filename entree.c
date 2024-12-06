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
	// S'il n'y a pas de mot à associer avec la nouvelle entree
	if (!mot)
		return NULL;

	// Allocation dynamique de mémoire pour toutes les variables inclue dans t_entree
	t_entree *entree = (t_entree*)malloc(sizeof(t_entree*));
	entree->mot = (char*)malloc(sizeof(mot));
	entree->liste = (t_liste*)malloc(sizeof(t_liste*));

	// Initialisation d'un mot de l'entree
	entree->mot = 0;
	entree->liste = 0;

	return entree;
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
	assert(entree != NULL);
	printf("Mot : %s", entree->mot);
}

char *t_entree_get_mot(const t_entree *entree) {
	// Si entree n'est pas nulle, alors retourne le mot associé à entree
	return entree != NULL ? entree->mot : NULL;
}

void t_entree_chercher(t_entree *entree, const char *question, const char **expression, const char **definition) {
	// Vérifier si les variables en param sont vides
	assert(entree != NULL);
	assert(question != NULL);
	assert(expression != NULL);
	assert(definition != NULL);

	// Placer l'adresse de l'expression de la paire dans expression (Idem pour definition)
	t_liste_get_infos(entree->liste, expression, definition);

	for (int i = 0; i < sizeof(entree->liste.paire); i++) {
		// Si l'expression est dans la question
		if (strstr(question, *expression)) {
			//*expression = ;
			//*definition = ;
		}
	}
}

void t_entree_ajouter(t_entree *entree, const char *expression, const char *definition) {
	assert(entree != NULL);
	assert(expression != NULL);
	assert(definition != NULL);

	//entree->liste->paire = realloc(entree->liste.paire, sizeof(entree->liste.paire) * sizeof(t_paire));
}

void t_entree_ecrire_fichier(FILE *fichier, const t_entree *entree) {
	assert(entree != NULL);
	assert(fichier != NULL);

	fprintf(fichier, "Mot : %s", entree->mot);
	for (int i = 0; i < sizeof(entree->liste); i++) {
		//fprintf(fichier, "\nExpression : %s Definition : %s", )
	}
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
