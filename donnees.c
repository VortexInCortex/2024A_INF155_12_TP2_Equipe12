//
// Created by duval on 2024-11-04.
//
#include "donnees.h"
#include "entree.h"
#include "utils.h"
#include "mon_malloc.h"

#include <assert.h>
#include <ctype.h>
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
    t_donnees *donnees = mon_malloc(sizeof(t_donnees));
    donnees->entrees = mon_malloc(capacite * sizeof(t_entree *));
    donnees->taille = 0;
    donnees->capacite = capacite;
    return donnees;
}

void t_donnees_inserer(t_donnees *donnees, const char *expression, const char *definition) {
    // 1 : extraire premier mot MINUSCULE
    char mot[MAX_CHAINE] = {0};
    utils_chaine_premier_mot(expression, mot);
    utils_chaine_minuscules(mot);

    t_entree *ptr_entree = NULL;
    if ((ptr_entree = t_donnees_chercher_entree(donnees, mot)) != NULL) {
        t_entree_ajouter(ptr_entree, expression, definition);
    } else {
        if (donnees->taille == donnees->capacite)
            t_donnees_redim(donnees, (donnees->capacite) * 2);

        ptr_entree = t_entree_creer(mot);
        t_entree_ajouter(ptr_entree, expression, definition);

        // Deplacer toutes les entrees actuelles d'une position vers la droite pour matcher les tests
        for (int i = donnees->taille; i > 0; i--) {
            donnees->entrees[i] = donnees->entrees[i - 1];
        }

        // On insere donc la nouvelle entree au debut plutot qu'a la fin
        donnees->entrees[0] = ptr_entree;
        donnees->taille++;
    }
}


void t_donnees_afficher(const t_donnees *donnees) {
    printf("Tableau dynamique de entrees (%llu/%llu) :\n", donnees->taille, donnees->capacite);
    for (int i = 0; i < donnees->taille; i++) {
        printf("  "); // Il y a 2 espaces dans les tests au debut.
        t_entree_afficher(donnees->entrees[i]);
    }
}

void t_donnees_chercher_definition(t_donnees *donnees, char *question, char *mot, const char **expression,
                                   const char **definition) {
    *expression = NULL; // S'assure que si expression et definition pointe sur de la junk
    *definition = NULL; // data, la condition du if de la premiere boucle marche tout de meme

    // Windows ne me laisse pas ecrire dans la question, donc je ne peux pas utiliser utils_chaine_minuscule(question)
    // je suis obliger de copier a une nouvelle chaine et de faire le travail de utils_chaine_minuscule manuellement
    // MEME SI la questionn n'est pas une constante.
    const int longeur_chaine = (int) strlen(question);
    char question_copie[MAX_CHAINE] = {0};
    for (int indice = 0; indice < longeur_chaine; indice++)
        question_copie[indice] = (char) tolower(question[indice]);

    for (int i = 0; i < donnees->taille; i++) {
        const char *buff = t_entree_get_mot(donnees->entrees[i]);
        if (strcmp(buff, mot) == 0) {
            t_entree_chercher(donnees->entrees[i], question_copie, expression, definition);
            return; // Oblige pour sortir de la for loop une fois avoir trouve l'entre contenant le mot
        }
    }
}


t_donnees *t_donnees_lire_fichier(const char *nom_fichier) {
    assert(nom_fichier != NULL);

    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier\n");
    } else {
        t_donnees *donnees = t_donnees_creer(1);
        char ligne[MAX_CHAINE];

        while (fgets(ligne, MAX_CHAINE, fichier) != NULL) {
            strcpy(ligne, utils_chaine_tailler(ligne));
            // Tailler la ligne pour enlever les retours chariot et les espaces
            if (strlen(ligne) == 0) {
                // Ne rien faire, ceci est une ligne vide
            } else {
                char expression[MAX_CHAINE], definition[MAX_CHAINE];
                utils_chaine_decouper(ligne, expression, definition, ":");

                if (*expression && *definition) {
                    // Vérification si l'expression et la définition ne sont pas vides
                    t_donnees_inserer(donnees, expression, definition);
                }
            }
        }

        fclose(fichier);
        return donnees;
    }
}

bool t_donnees_ecrire_fichier(t_donnees *donnees, const char *nom_fichier) {
    FILE *file = fopen(nom_fichier, "w");
    bool ouvert = false;

    if (file == NULL) {
        ouvert = false; // Return false if the file cannot be opened
    } else {
        // Iterate through all entries in the t_donnees structure
        for (int i = 0; i < donnees->taille; i++) {
            t_entree_ecrire_fichier(file, donnees->entrees[i]);
        }

        fclose(file); // Close the file after writing
        ouvert = true;
    }


    return ouvert; // Return true to indicate success
}

void t_donnees_liberer(t_donnees *donnees) {
    for (size_t i = 0; i < donnees->taille; i++) {
        t_entree_liberer(donnees->entrees[i]);
    }
    free(donnees->entrees);
    free(donnees);
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

    // t_donnees_afficher
    char *nom_fichier = "../_t_donnees_test.txt";
    utils_stdout_vers_fichier(nom_fichier);
    t_donnees_afficher(donnees);
    utils_stdout_vers_fichier(NULL);
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    char *lignes1[] = {
        "Tableau dynamique de entrees (3/4) :\n",
        "  [abracadabra] : abracadabra : World!\n",
        "  [hello] : hello tout le monde! : On dit bonjour. - hello : World!\n",
        "  [hi] : hi : World!\n"
    };
    utils_verifier_fichier(nom_fichier, lignes1, 4);

    //  sans redirection
    // printf("Obtenu  : ");
    // t_donnees_afficher(donnees);
    // printf("Attendu : Tableau dynamique de entrees (3/4) :\n"
    //     "  [abracadabra] : abracadabra : World!\n"
    //     "  [hello] : hello tout le monde! : On dit bonjour. - hello : World!\n"
    //     "  [hi] : hi : World!");

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

    //  t_donnees_lire_fichier
    t_donnees_liberer(donnees);
    //  - creation d'un fichier temporaire pour le test
    FILE *fichier = fopen(nom_fichier, "w");
    fprintf(fichier, "    \n");
    fprintf(fichier, "    test     : Ceci est un fichier de test\n");
    fprintf(fichier, "               \n");
    fprintf(fichier, "chaine  de caracteres :        Une suite de caracteres terminee par le caractere '\\0'.\n");
    fprintf(fichier, "    \n");
    fprintf(fichier, "\n");
    fclose(fichier);

    //  - lecture du fichier de donnees
    donnees = t_donnees_lire_fichier(nom_fichier);

    //  - test sur le fichier
    assert(donnees->taille == 2);
    assert(donnees->capacite == 2);
    assert(strcmp(t_entree_get_mot(donnees->entrees[0]), "chaine") == 0);
    assert(strcmp(t_entree_get_mot(donnees->entrees[1]), "test") == 0);

    //  t_donnees_ecrire_fichier
    //  - ecriture du fichier de test
    t_donnees_ecrire_fichier(donnees, nom_fichier + 3); //  sauter "../"

    //  - tests sur le fichier
    char *lignes2[] = {
        "chaine  de caracteres : Une suite de caracteres terminee par le caractere '\\0'.\n",
        "test : Ceci est un fichier de test\n"
    };
    utils_verifier_fichier(nom_fichier + 3, lignes2, 2);
    // JAI DU AJOUTER +3 POUR SAUTER ../ SINON ON LIT PAS LE MEME FICHIER QU'ECRIT, CE QUI NE SEMBLE PAS FAIRE DE SENS

    //  t_donnees_redim
    t_donnees_redim(donnees, 321);
    assert(donnees->capacite == 321);

    //  t_donnees_liberer
    t_donnees_liberer(donnees);

    assert(mon_rapport(false) == 0);

    printf("TEST donnees : OK\n");
}

//  ---------------------------------
//  Definitions des fonctions privees
//  ---------------------------------
void t_donnees_redim(t_donnees *donnees, size_t nouvelle_capacite) {
    t_entree **nouvelles_entrees = realloc(donnees->entrees, nouvelle_capacite * sizeof(t_entree *));
    if (nouvelles_entrees == NULL) {
        printf("ERROR: DEBUG: Memory allocation of t_donnees_redim FAILED\n");
    } else {
        donnees->entrees = nouvelles_entrees;
        donnees->capacite = nouvelle_capacite;
    }
}


t_entree *t_donnees_chercher_entree(const t_donnees *donnees, char *mot) {
    t_entree *entree_cherche = NULL;
    for (size_t i = 0; i < donnees->taille; i++) {
        if (strcmp(t_entree_get_mot(donnees->entrees[i]), mot) == 0) {
            entree_cherche = donnees->entrees[i];
        }
    }
    return entree_cherche;
}


