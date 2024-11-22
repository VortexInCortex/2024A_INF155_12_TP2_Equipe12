//
// Created by duval on 2024-11-04.
//
#include "donnees.h"
#include "entree.h"
#include "utils.h"
#include "mon_malloc.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAINE 512

//  Definition du type des donnees
struct s_donnees {
    t_entree **entrees;
    size_t taille;
    size_t capacite;
};

//  ----------------------------------
//  Declarations des fonctions privees
//  ----------------------------------
/**
* @name t_donnees_redim
* @short redimensionne un tableau dynamique de donnees passe en parametre.
* @param donnees le tableau de donnees.
* @param nouvelle_capacite la nouvelle capacite du tableau de donnees.
* @return rien.
*/
void t_donnees_redim(t_donnees *donnees, size_t nouvelle_capacite);

/**
* @name t_donnees_chercher_entree
* @short recherhe une entree associee a un mot passe en parametre, pour un tableau de donnees.
* @param donnees le tableau de donnees.
* @param mot le mot dont on cherche l'entree.
* @return un pointeur sur l'entree trouvee ou NULL si aucune entree correspondant a ce mot n'a ete trouvee.
*/
t_entree *t_donnees_chercher_entree(const t_donnees *donnees, char *mot);

// -----------------------------------
// Definitions des fonctions publiques
// -----------------------------------
t_donnees *t_donnees_creer(size_t capacite) {
	// A completer
}

void t_donnees_liberer(t_donnees *donnees) {
	// A completer
}

void t_donnees_afficher(const t_donnees *donnees) {
	// A completer
}

void t_donnees_inserer(t_donnees *donnees, const char *expression, const char *definition) {
	// A completer
}

void t_donnees_chercher_definition(t_donnees *donnees, char *question, char *mot, const char **expression,
                                   const char **definition) {
	// A completer
}

t_donnees *t_donnees_lire_fichier(const char *nom_fichier) {
	// A completer
}

bool t_donnees_ecrire_fichier(t_donnees *donnees, const char *nom_fichier) {
	// A completer
}

void t_donnees_test() {
    printf("------------------------ TEST DONNEES ------------------------\n");

    //  t_donnees_creer
#define CAP 1
    t_donnees *donnees = t_donnees_creer(CAP);
    assert(donnees != NULL);
    assert(donnees->capacite == CAP);
    assert(donnees->taille == 0);

    //  t_donnees_inserer
    t_donnees_inserer(donnees, "Hi", "World!");
    assert(donnees->taille == 1);
    assert(donnees->capacite == 1);
    t_donnees_inserer(donnees, "Hello", "World!");
    assert(donnees->taille == 2);
    assert(donnees->capacite == 2);
    t_donnees_inserer(donnees, "Abracadabra", "World!");
    assert(donnees->taille == 3);
    assert(donnees->capacite == 4);
    t_donnees_inserer(donnees, "Hello tout le monde!", "On dit bonjour.");
    assert(donnees->taille == 3);
    assert(donnees->capacite == 4);

    char *reponses[][3] = {
        {"abracadabra", "abracadabra", "World!"},
        {"hello", "hello tout le monde!", "On dit bonjour."},
        {"hi", "hi", "World!"}
    };
    for (int i = 0; i < 3; i++) {
        assert(strcmp(t_entree_get_mot(donnees->entrees[i]), reponses[i][0]) == 0);
    }

    //  t_donnees_chercher_entree
    t_entree *entree = t_donnees_chercher_entree(donnees, "hi");
    assert(entree != NULL);
    entree = t_donnees_chercher_entree(donnees, "hello");
    assert(entree != NULL);

    //  t_donnees_chercher_definition
    const char *expression;
    const char *definition;
    t_donnees_chercher_definition(donnees, "Que veut dire 'hi!' ?", "hi", &expression, &definition);
    assert(expression != NULL);
    t_donnees_chercher_definition(donnees, "Qu'est-ce que ce 'hello tout le monde!' ?", "hello", &expression,
                                  &definition);
    assert(expression != NULL);

    //  t_donnees_liberer
    t_donnees_liberer(donnees);

    //  t_donnees_creer_fichier
    donnees = t_donnees_lire_fichier("../bd_complete.txt");
    // t_donnees_afficher(tdp);

    char *question = "Qu'est-ce qu'une adresse MAC ?";

    t_donnees_liberer(donnees);

    assert(mon_rapport(false) == 0);

    printf("TEST donnees : OK\n");
}

//  ---------------------------------
//  Definitions des fonctions privees
//  ---------------------------------
void t_donnees_redim(t_donnees *donnees, size_t nouvelle_capacite) {
	// A completer
}

t_entree *t_donnees_chercher_entree(const t_donnees *donnees, char *mot) {
	// A completer
}


