//
// Created by duval on 2024-11-04.
//
#include "utils.h"
#include "mon_malloc.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAINE 512

//  ----------------------------------
//  Definition des fonctions publiques
//  ----------------------------------
char *utils_chaine_minuscules(char *chaine) {
    const int longeur_chaine = (int) strlen(chaine);

    for (int indice = 0; indice < longeur_chaine; indice++)
        chaine[indice] = (char) tolower(chaine[indice]);

    return chaine;
}

char *utils_chaine_tailler(char *chaine) {
    const int length = (int) strlen(chaine);

    if (length == 0) {
        printf("ERROR: DEBUG: La chaine passe a utils_chaine_tailler etait de taille nulle!");
    } else {
        int start_index = -1;
        while (isspace(chaine[0])) {
            start_index++;
            if (!isspace(chaine[start_index]))
                chaine = chaine + start_index;
        }
        for (int end_index = length - start_index - 1; isspace(chaine[end_index]) && end_index >= 0; end_index--) {
            chaine[end_index] = 0;
        }
    }

    return chaine;
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
    int nb_delims = (int) strlen(delimiteurs);
    int length = (int) strlen(ligne);
    for (int index_delims = 0; index_delims < nb_delims; index_delims++) {
        for (int index = 1; index < length; index++) {
            if (ligne[index + 1] == delimiteurs[index_delims]) {
                // Taille de tableau que l'on veut allouer
                const int longueur_expression = index + 1;
                const int longueur_definition = (length - (index + 2)) + 1;

                // // Si l'espace de stockage dans expression ou definition est trop petit, annuler le stockage pour eviter
                // // de corrompre d'autres donnees(0xC000000005) | On utilise strictement plus grand pour pouvoir stocker le \0 a la fin
                // if ((strlen(expression) > longueur_expression) && (strlen(definition) > longueur_definition)) {
                for (int i = 0; i < longueur_expression; i++)
                    expression[i] = ligne[i];
                expression[longueur_expression] = 0; // Inserer le 0 apres le string
                for (int i = 0; i < longueur_definition; i++)
                    definition[i] = ligne[i + (longueur_expression + 1)]; // l'expression en paranthese est l'offset
                definition[longueur_definition] = 0; // Inserer le 0 apres le string
                // } else
                //     printf("ERROR: DEBUG: Trop peu d'espace dans le pointeur expression donnee a la fonction \"utils_chaine_decouper\"\n");
            }
        }
    }
}

void utils_chaine_premier_mot(const char *expression, char *mot) {
    for (int index = 0; !isspace(expression[index]); index++) {
        // **S'assurer que l'expression a ete taille avant d'appeler premier mot.**
        if (!isspace(expression[index]) && isspace(expression[index + 1])) {
            // Taille de tableau que l'on veut allouer
            const int longueur_mot = index + 1;

            // // Si l'espace de stockage dans mot est trop petit, annuler le stockage pour eviter
            // // de corrompre d'autres donnees(0xC000000005) | On utilise strictement plus grand pour pouvoir stocker le \0 a la fin
            // if (strlen(mot) > index)
            for (int i = 0; i < longueur_mot; i++)
                mot[i] = expression[i];
            mot[longueur_mot] = 0; // Inserer le 0 apres le string
            // else
            //     printf("ERROR: DEBUG: Trop peu d'espace dans le pointeur mot donnee a la fonction \"utils_chaine_premier_mot\"\n");
        }
    }
}

bool utils_saisir_oui_non() {
    bool choix = false;
    char reponse[4] = {0};
    const char oui[4] = "oui\0";
    const char non[4] = "non\0";

    printf("Oui ou non? : ");
    fflush(stdin);
    scanf("%4[A-Za-z]s", &reponse);
    utils_chaine_minuscules(reponse);

    if (strcmp(reponse, oui) == 0)
        choix = true;
    else if (strcmp(reponse, non) == 0)
        choix = false;
    else
        do {
            printf("\nSaisissez oui ou non : ");
            fflush(stdin);
            scanf("%4[A-Za-z]s", &reponse);
            utils_chaine_minuscules(reponse);
            if (strcmp(reponse, oui) == 0)
                choix = true;
        } while ((strcmp(reponse, oui) != 0) && (strcmp(reponse, non) != 0));
    return choix;
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
    while ((ligne = utils_fichier_ligne_suivante("../test_utils.txt"))) {
        assert(strcmp(ligne, lignes[nb]));
        nb++;
    }

    //  utils_ligne_decouper
    char *decoupes[][2] = {
        {"test", "Ceci est un fichier de test."},
        {"chaine  de caracteres", "Une suite de caracteres terminee par le caractere '\\0'."}
    };
    // ReSharper disable once CppTooWideScope
    char mot_clef[MAX_CHAINE];
    // ReSharper disable once CppTooWideScope
    char definition[MAX_CHAINE];
    for (int i = 0; i < sizeof(lignes) / sizeof(lignes[0]); i++) {
        utils_chaine_decouper(lignes[i], mot_clef, definition, ":");
        assert(strcmp(mot_clef, decoupes[i][0]) == 0);
        assert(strcmp(definition, decoupes[i][1]) == 0);
    }

    //  test utils_premier_mot
    char *expressions[][2] = {
        {"langage", "langage"},
        {"", ""},
        {"bit de parie", "bit"},
        {"serveur DNS", "serveur"}
    };
    for (int i = 0; i < sizeof(expressions) / sizeof(expressions[0]); i++) {
        utils_chaine_premier_mot(expressions[i][0], buffer);
        assert(strcmp(buffer, expressions[i][1]) == 0);
    }

    mon_rapport(false);

    printf("TEST utils : OK\n");
}
