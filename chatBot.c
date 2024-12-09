//
// Created by stephane on 12/11/24.
//
#include "chatBot.h"
#include "donnees.h"
#include "mon_malloc.h"
#include "utils.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#define MAX_CHAINE 512

//  ----------------------------------
//  Declarations des fonctions privees
//  ----------------------------------
/**
 * @name chatBot_repondre_question
 * @short Repond a une question passee en parametre selon les donnees qui se trouvent dans la base de donnees.
 * @param donnees le tableau de donnees sur lequel sera basee la reponse.
 * @param question la question qui a ete posee par l'utilisateur.
 * @return true si le bot a pu donner une reponse, false sinon.
 */
bool chatBot_repondre_question(t_donnees *donnees, char *question);

/**
 * @name chatBot_poser_question
 * @short Pose une question et essaye d'y repondre. S'il ne parvient pas a repondre, le ChatBot permet a l'utilisateur
 * d'ajouter une nouvelle expression et sa definition dans la base de donnees.
 * @param donnees le tableau de donnees.
 * @return false si l'utilsateur veut quitter, true sinon.
 */
bool chatBot_poser_question(t_donnees *donnees);

//  -----------------------------------
//  Definitions des fonctions publiques
//  -----------------------------------
void chatBot(const char *nom_fichier) {
    char file_start[4] = "../";
    char file_path[MAX_CHAINE] = {0};
    strcat(file_path, file_start);
    strcat(file_path, nom_fichier);

    // Load data from the file
    t_donnees *donnees = t_donnees_lire_fichier(file_path);
    if (!donnees) {
        printf("DEBUG: ERREEUR : Peut pas lire fichier : '%s'.\n", file_path);
    } else {
        printf("Bienvenue dans le ChatBot ! Tapez 'quitter' pour arreter.\n");

        // Pose question jusqu'a ce que l'utilisateur ecrit 'quitter'
        while (chatBot_poser_question(donnees)) {
        }

        // Save the data back to the file
        if (!t_donnees_ecrire_fichier(donnees, file_path)) {
            printf("DEBUG: ERREUR : impossible d'ecrire les donnees dans le fichier.\n");
        }

        // free(tout)
        t_donnees_liberer(donnees);
    }
}


void chatBot_test() {
    printf("------------------------ TEST CHATBOT ------------------------\n");

    t_donnees *donnees = t_donnees_lire_fichier("../bd_simple.txt");

    //  chatBot_repondre_question
    char question[] = "Pourquoi avoir plus de RAM dans un ordinateur!?";
    const char *nom_fichier = "../_chatBot_test.txt";
    utils_stdout_vers_fichier(nom_fichier);
    chatBot_repondre_question(donnees, question);
    utils_stdout_vers_fichier(NULL);
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);

    char *lignes[] = {"ram : memoire vive a acces aleatoire.\n"};
    utils_verifier_fichier(nom_fichier, lignes, 1);

    //  sans redirection
    // printf("Obtenu  : ");
    // chatBot_repondre_question(donnees, question);
    // printf("Attendu : ram : memoire vive a acces aleatoire.\n");

    t_donnees_liberer(donnees);

    assert(mon_rapport(false) == 0);

    printf("TEST chatBot : OK\n");
}

//  ----------------------------------
//  Definitions des fonctions privees
//  ----------------------------------
bool chatBot_repondre_question(t_donnees *donnees, char *question) {
    assert(donnees != NULL);
    assert(question != NULL);

    bool repondu = false;

    const char *expression = NULL;
    const char *definition = NULL;

    char *question_minuscules = utils_chaine_minuscules(question);
    char question_copie[MAX_CHAINE] = {0};
    strcpy(question_copie, question_minuscules);

    // Extract the keyword from the question en parcourant tous les mots de la question jusqu'a trouver un match
    char mot[MAX_CHAINE] = {0};
    /* get the first token */
    char *token = strtok(question_copie, " ");
    strcpy(mot, token);
    while (expression == NULL && definition == NULL && token != NULL) {
        // Search for an answer in the data
        t_donnees_chercher_definition(donnees, question_minuscules, mot, &expression, &definition);
        token = strtok(NULL, " ");
        if (token != NULL)
            strcpy(mot, token);
    }

    if (expression != NULL && definition != NULL) {
        printf("%s : %s\n", expression, definition);
        repondu = true;
    } else {
        printf("Desole, je n'ai pas trouve de reponse a votre question.\n");
        repondu = false;
    }
    return repondu;
}

bool chatBot_poser_question(t_donnees *donnees) {
    assert(donnees != NULL);

    char question[MAX_CHAINE];

    bool run = true;

    // Prompt the user for a question
    printf("Posez votre question (ou tapez 'quitter' pour arreter) : ");
    if (!fgets(question, MAX_CHAINE, stdin)) {
        printf("Erreur de lecture.\n");
        run = false;
    } else {
        question[strcspn(question, "\n")] = '\0'; // Remove the newline character

        // Check if the user wants to quit
        if (strcmp(question, "quitter") == 0) {
            run = false;
        } else {
            const char *expression = NULL;
            const char *definition = NULL;

            // Attempt to answer the question
            if (!chatBot_repondre_question(donnees, question)) {
                // If no answer is found, prompt the user to add a new entry
                printf("Je n'ai pas de reponse. Voulez-vous ajouter une definition ? (oui/non) : ");
                char reponse[10];
                if (!fgets(reponse, sizeof(reponse), stdin)) {
                    printf("Erreur de lecture.\n");
                    run = false;
                } else {
                    reponse[strcspn(reponse, "\n")] = '\0';

                    if (strcmp(reponse, "oui") == 0) {
                        char nouvelle_expression[MAX_CHAINE];
                        char nouvelle_definition[MAX_CHAINE];

                        printf("Entrez l'expression : ");
                        if (!fgets(nouvelle_expression, MAX_CHAINE, stdin)) {
                            printf("Erreur de lecture.\n");
                            run = false;
                        } else {
                            nouvelle_expression[strcspn(nouvelle_expression, "\n")] = '\0';

                            printf("Entrez la definition : ");
                            if (!fgets(nouvelle_definition, MAX_CHAINE, stdin)) {
                                printf("Erreur de lecture.\n");
                                run = false;
                            } else {
                                nouvelle_definition[strcspn(nouvelle_definition, "\n")] = '\0';

                                // Add the new expression and definition to the data
                                t_donnees_inserer(donnees, nouvelle_expression, nouvelle_definition);
                                printf("Nouvelle definition ajoutee !\n");
                            }
                        }
                    }
                }
            }
        }
    }

    return run;
}

