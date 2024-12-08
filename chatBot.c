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
void chatBot(const char *nom_fichier_donnees) {
	// A completer
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

    char *lignes[] = {"ram : memoire vive a acces aleatoire.\n"};
    utils_verifier_fichier(nom_fichier, lignes, 1);

    //  sans redirection
//    printf("Obtenu  : ");
//    chatBot_repondre_question(donnees, question);
//    printf("Attendu : ram : memoire vive a acces aleatoire.\n");

    t_donnees_liberer(donnees);

    assert(mon_rapport(false) == 0);

    printf("TEST chatBot : OK\n");
}

//  ----------------------------------
//  Definitions des fonctions privees
//  ----------------------------------
bool chatBot_repondre_question(t_donnees *donnees, char *question) {
	// A completer
}

bool chatBot_poser_question(t_donnees *donnees) {
	// A completer
}
