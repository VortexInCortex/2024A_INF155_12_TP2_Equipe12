//
// Created by stephane on 12/11/24.
//

#include "liste.h"
#include "paire.h"
#include "mon_malloc.h"
#include "utils.h"

#include <malloc.h>
#include <assert.h>
#include <string.h>

//  ---------------------------------------------
//  Definition de la structure de liste de paires
//  ---------------------------------------------
/**
 * @details le type pour une liste de paires. Un element de liste contient un pointeur sur une paire (expression, definition)
 * ainsi qu'un pointeur sur l'element suivant de la liste.
 */
struct s_liste {
    t_paire *paire;
    t_liste *suivante;
};

//  ----------------------------------
//  Definition des fonctions publiques
//  ----------------------------------
t_liste *t_liste_creer_vide() {
    return NULL;
}

t_liste *t_liste_ajouter(t_liste *liste, const char *expression, const char *definition) {
    t_liste *res = malloc(sizeof(t_liste));
    assert(res != NULL);

    res->paire = t_paire_creer(expression, definition);
    res->suivante = liste;

    return res;
}

void t_liste_afficher(const t_liste *liste) {
    while (liste != NULL) {
        t_paire_afficher(liste->paire);
        liste = liste->suivante;
        if (liste != NULL) {
            printf(" - ");
        }
    }
    printf("\n");
}

void t_liste_get_infos(const t_liste *liste, const char **expression, const char **definition) {
    assert(liste != NULL);

    t_paire *paire = liste->paire;
    *expression = t_paire_get_expression(paire);
    *definition = t_paire_get_definition(paire);
}

void t_liste_chercher(const t_liste *liste, const char *question, const char **expression, const char **definition) {
    t_paire *plus_longue_paire = NULL;

    while (liste != NULL) {
        t_paire *paire = liste->paire;
        if (t_paire_contient(paire, question)) {
            if (plus_longue_paire == NULL ||
                t_paire_get_longueur(paire) > t_paire_get_longueur(plus_longue_paire)) {
                plus_longue_paire = paire;
            }
        }

        liste = liste->suivante;
    }

    if (plus_longue_paire != NULL) {
        *expression = t_paire_get_expression(plus_longue_paire);
        *definition = t_paire_get_definition(plus_longue_paire);
    } else {
        *expression = NULL;
        *definition = NULL;
    }
}

void t_liste_ecrire_fichier(FILE *fichier, const t_liste *liste) {
    while (liste != NULL) {
        t_paire_ecrire_fichier(fichier, liste->paire);
        liste = liste->suivante;
    }
}

void t_liste_liberer(t_liste *liste) {
    while (liste != NULL) {
        t_liste *suivant = liste->suivante;
        t_paire_liberer(liste->paire);
        free(liste);
        liste = suivant;
    }
}

void t_liste_test() {
    printf("------------------------ TEST LISTE ------------------------\n");

    //  t_liste_creer_vide
    t_liste *liste = t_liste_creer_vide();
    assert(liste == NULL);

    //  t_liste_ajouter
    liste = t_liste_ajouter(liste, "bit de signe", "bit indiquant le signe d'un nombre dans la norme IEEE754.");
    assert(strcmp(t_paire_get_expression(liste->paire), "bit de signe") == 0);
    assert(
        strcmp(t_paire_get_definition(liste->paire), "bit indiquant le signe d'un nombre dans la norme IEEE754.") ==
        0);

    liste = t_liste_ajouter(liste, "disque dur",
                            "Un disque dur est une memoire de masse utilisee principalement dans les ordinateurs");
    assert(strcmp(t_paire_get_expression(liste->paire), "disque dur") == 0);
    assert(
        strcmp(t_paire_get_definition(liste->paire),
            "Un disque dur est une memoire de masse utilisee principalement dans les ordinateurs") ==
        0);

    //  t_liste_afficher
    char *nom_fichier = "../_t_liste_test.txt";
    utils_stdout_vers_fichier(nom_fichier);
    t_liste_afficher(liste);
    utils_stdout_vers_fichier(NULL);
    char *lignes1[] = {
        "disque dur : Un disque dur est une memoire de masse utilisee principalement dans les ordinateurs - bit de signe : bit indiquant le signe d'un nombre dans la norme IEEE754.\n"
    };
    utils_verifier_fichier(nom_fichier, lignes1, 1);

    // sans redirection
    // printf("Obtenu  : ");
    // t_liste_afficher(liste);
    // printf(
    //     "Attendu : disque dur : Un disque dur est une memoire de masse utilisee principalement dans les ordinateurs - bit de signe : bit indiquant le signe d'un nombre dans la norme IEEE754.\n");

    //  t_liste_get_infos
    const char *expression;
    const char *definition;
    t_liste_get_infos(liste, &expression, &definition);
    assert(strcmp(expression, "disque dur") == 0);
    assert(
        strcmp(definition, "Un disque dur est une memoire de masse utilisee principalement dans les ordinateurs") ==
        0);

    //  t_liste_chercher
    t_liste_chercher(liste, "qu'est-ce qu'un disque dur ?", &expression, &definition);
    assert(strcmp(expression, "disque dur") == 0);
    assert(
        strcmp(definition, "Un disque dur est une memoire de masse utilisee principalement dans les ordinateurs") ==
        0);

    //  t_liste_ecrire_fichier
    //  - creation d'un fichier temporaire pour le test
    FILE *fichier = fopen(nom_fichier, "w");
    t_liste_ecrire_fichier(fichier, liste);
    fclose(fichier);

    //  - validation du fichier
    char ligne[512];
    fichier = fopen(nom_fichier, "r");
    fgets(ligne, 512, fichier);
    assert(strcmp(ligne,
            "disque dur : Un disque dur est une memoire de masse utilisee principalement dans les ordinateurs\n") ==
        0);
    fgets(ligne, 512, fichier);
    assert(strcmp(ligne, "bit de signe : bit indiquant le signe d'un nombre dans la norme IEEE754.\n") == 0);

    //  - suppression du fichier
    remove(nom_fichier);

    //  t_liste_liberer
    t_liste_liberer(liste);

    assert(mon_rapport(false) == 0);

    printf("TEST liste : OK\n");
}
