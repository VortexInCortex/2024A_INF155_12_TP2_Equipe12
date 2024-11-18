//
// Created by duval on 2024-11-04.
//
#include "utils.h"
#include "mon_malloc.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAINE 512

//  ----------------------------------
//  Definition des fonctions publiques
//  ----------------------------------
char *utils_chaine_minuscules(char *chaine) {
	// A completer
}

char *utils_chaine_tailler(char *chaine) {
	// A completer
}

char *utils_fichier_ligne_suivante(const char *nom_fichier) {
    static FILE *fichier = NULL;
    static char tampon[MAX_CHAINE];

    if (fichier == NULL) {
        assert(nom_fichier != NULL);
        fichier = fopen(nom_fichier, "r");
        assert(fichier != NULL);
    }

    char *ligne;

    do {
        ligne = fgets(tampon, MAX_CHAINE, fichier);
        if (ligne != NULL) {
            ligne = utils_chaine_tailler(ligne);
        }
    } while (ligne != NULL && *ligne == '\0');

    if (ligne == NULL) {
        fichier = NULL; //  remise a zero pour le prochain fichier a lire
    }

    return ligne;
}

void utils_chaine_decouper(char *ligne, char *expression, char *definition, const char *delimiteurs) {
	// A completer
}

void utils_chaine_premier_mot(const char *expression, char *mot) {
	// A completer
}

bool utils_saisir_oui_non() {
	// A completer
}

void utils_test() {
    printf("------------------------ TEST UTILS ------------------------\n");
    char buffer[MAX_CHAINE];

    //  test utils_chaine_minuscules
    strncpy(buffer, "Je suis une GRANDE chaine !!! 1234567", MAX_CHAINE);
    assert(strcmp(utils_chaine_minuscules(buffer), "je suis une grande chaine !!! 1234567") == 0);

    //  test utils_chaine_tailler
    strncpy(buffer, "    i2c          ", MAX_CHAINE);
    assert(strcmp(utils_chaine_tailler(buffer), "i2c") == 0);
    strncpy(buffer, "    un arbre   \n", MAX_CHAINE);
    assert(strcmp(utils_chaine_tailler(buffer), "un arbre") == 0);

    //  test utils_fichier_ligne_suivante
    char lignes[2][MAX_CHAINE];
    strcpy(lignes[0], "test:Ceci est un fichier de test.");
    strcpy(lignes[1], "chaine  de caracteres:Une suite de caracteres terminee par le caractere '\\0'.");
    int nb = 0;
    char *ligne;
    while (ligne = utils_fichier_ligne_suivante("../test_utils.txt")) {
        assert(strcmp(ligne, lignes[nb]));
        nb++;
    }

    //  utils_ligne_decouper
    char *decoupes[][2] = {
            {"test",                  "Ceci est un fichier de test."},
            {"chaine  de caracteres", "Une suite de caracteres terminee par le caractere '\\0'."}
    };
    char mot_clef[MAX_CHAINE];
    char definition[MAX_CHAINE];
    for (int i = 0; i < sizeof(lignes) / sizeof(lignes[0]); i++) {
        utils_chaine_decouper(lignes[i], mot_clef, definition, ":");
        assert(strcmp(mot_clef, decoupes[i][0]) == 0);
        assert(strcmp(definition, decoupes[i][1]) == 0);
    }

    //  test utils_premier_mot
    char *expressions[][2] = {{"langage",      "langage"},
                              {"",             ""},
                              {"bit de parie", "bit"},
                              {"serveur DNS",  "serveur"}};
    for (int i = 0; i < sizeof(expressions) / sizeof(expressions[0]); i++) {
        utils_chaine_premier_mot(expressions[i][0], buffer);
        assert(strcmp(buffer, expressions[i][1]) == 0);
    }

    mon_rapport(false);

    printf("TEST utils : OK\n");
}
