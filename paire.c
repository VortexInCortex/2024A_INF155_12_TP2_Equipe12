//
// Created by duval on 2024-11-04.
//

#include "paire.h"
#include "mon_malloc.h"
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

//  -----------------------------------
//  Definition de la structure de paire
//  -----------------------------------
/**
 * @details la structure d'une paire. Elle contient une expression et sa definition.
 */
struct s_paire {
    char *expression; //  L'expression dont on donne une definition.
    size_t longueur; //  La longueur de l'expression en nombre de caracteres.
    char *definition; //  La definition associee a l'expression.
};

//  ----------------------------------
//  Definition des fonctions publiques
//  ----------------------------------
t_paire *t_paire_creer(const char *expression, const char *definition) {
	// A completer
}

void t_paire_liberer(t_paire *paire) {
	// A completer
}

void t_paire_afficher(const t_paire *paire) {
	// A completer
}

const char *t_paire_get_expression(const t_paire *paire) {
	// A completer
}

size_t t_paire_get_longueur(const t_paire *paire) {
	// A completer
}

const char *t_paire_get_definition(const t_paire *paire) {
	// A completer
}

bool t_paire_contient(const t_paire *paire, const char *question) {
	// A completer
}

void t_paire_ecrire_fichier(FILE *fichier, t_paire *paire) {
	// A completer
}

void t_paire_test() {
    printf("------------------------ TEST PAIRE ------------------------\n");

    //  t_paire_creer
    t_paire *paire1 = t_paire_creer("expression",
                                    "definition.");
    assert(strcmp(paire1->expression, "expression") == 0);
    assert(paire1->longueur==10);
    assert(strcmp(paire1->definition, "definition.") == 0);

    //  t_paire_afficher
    t_paire_afficher(paire1);
    printf("\n");

    //  t_paire_get_expression
    assert(strcmp(t_paire_get_expression(paire1), "expression") == 0);

    //  t_paire_get_longueur
    assert(t_paire_get_longueur(paire1) == 10);

    //  t_paire_get_definition
    assert(strcmp(t_paire_get_definition(paire1), "definition.") == 0);

    t_paire *paire2 = t_paire_creer("protocole de communication",
                                    "Specification de plusieurs regles pour un type de communication particulier");

    //  t_paire_contient
    assert(!t_paire_contient(paire1, "test"));
    assert(t_paire_contient(paire1, "expression"));
    assert(!t_paire_contient(paire2, "A quoi sert un bit en informatique ?"));
    assert(t_paire_contient(paire2, "Qu'est-ce qu'un protocole de communication ?"));

    //  t_paire_liberer
    t_paire_liberer(paire1);
    t_paire_liberer(paire2);

    assert(mon_rapport(false) == 0);

    printf("TEST paire : OK\n");
}
