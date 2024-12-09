//
// Created by duval on 2024-11-04.
//

#include "paire.h"
#include "mon_malloc.h"
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>


#include <stdlib.h>

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
	t_paire *paire = malloc(sizeof(t_paire));
	if (!paire) {
		fprintf(stderr, "ERROR: DEBUG: Couldn't allocate paire\n");
		// ReSharper disable once CppDeclarationHidesLocal
		t_paire *paire = NULL;
	} else {
		size_t exp_len = strlen(expression);
		size_t exp_def = strlen(definition);

		paire->expression = (char *) malloc(exp_len + 1);
		strcpy(paire->expression, expression);
		utils_chaine_minuscules(paire->expression);

		paire->longueur = exp_len;

		paire->definition = (char *) malloc(exp_def + 1);
		strcpy(paire->definition, definition);
	}

	return paire;
}

void t_paire_liberer(t_paire *paire) {
	free(paire->expression);
	free(paire->definition);
	free(paire);
}

void t_paire_afficher(const t_paire *paire) {
	printf("%s : %s", paire->expression, paire->definition);
}

const char *t_paire_get_expression(const t_paire *paire) {
	return paire->expression;
}

size_t t_paire_get_longueur(const t_paire *paire) {
	return paire->longueur;
}

const char *t_paire_get_definition(const t_paire *paire) {
	return paire->definition;
}

bool t_paire_contient(const t_paire *paire, const char *question) {
	bool trouve = true;

	const char *expression_trouve = strstr(question, t_paire_get_expression(paire));

	if (expression_trouve == NULL) //La fonction strstr retourne NULL si l'expression n'est pas trouver dans la question
	{
		trouve = false;
	}

	return trouve;
}

void t_paire_ecrire_fichier(FILE *fichier, t_paire *paire) {
	fprintf(fichier, "%s : %s\n", t_paire_get_expression(paire), t_paire_get_definition(paire));
}

void t_paire_test() {
	printf("------------------------ TEST PAIRE ------------------------\n");

	//  t_paire_creer
	t_paire *paire1 = t_paire_creer("expression simple",
	                                "Definition de cette expression simple.");
	assert(strcmp(paire1->expression, "expression simple") == 0);
	assert(paire1->longueur == 17);
	assert(strcmp(paire1->definition, "Definition de cette expression simple.") == 0);

	t_paire *paire2 = t_paire_creer("protocole de communication",
	                                "Specification de plusieurs regles pour un type de communication particulier.");
	assert(strcmp(paire2->expression, "protocole de communication") == 0);
	assert(paire2->longueur == 26);
	assert(strcmp(paire2->definition, "Specification de plusieurs regles pour un type de communication particulier.") ==
		0);

	//  t_paire_afficher
	//  - redirection de stdout dans un fichier temporaire
	char *nom_fichier_test = "../_t_paire_test.txt";
	utils_stdout_vers_fichier(nom_fichier_test);
	t_paire_afficher(paire1);
	utils_stdout_vers_fichier(NULL);

	//  - test du fichier
	char *lignes1[] = {"expression simple : Definition de cette expression simple."};
	utils_verifier_fichier(nom_fichier_test, lignes1, 1);

	// sans redirection
	// printf("Obtenu  : ");
	// t_paire_afficher(paire1);
	// printf("\n");
	// printf("Attendu : expression simple : Definition de cette expression simple.\n");

	//  t_paire_get_expression
	assert(strcmp(t_paire_get_expression(paire1), "expression simple") == 0);

	//  t_paire_get_longueur
	assert(t_paire_get_longueur(paire1) == 17);

	//  t_paire_get_definition
	assert(strcmp(t_paire_get_definition(paire1), "Definition de cette expression simple.") == 0);

	//  t_paire_contient
	assert(!t_paire_contient(paire1, "test"));
	assert(t_paire_contient(paire1, "Voici une expression simple, tres simple..."));
	assert(!t_paire_contient(paire2, "A quoi sert un bit en informatique ?"));
	assert(t_paire_contient(paire2, "Qu'est-ce qu'un protocole de communication ?"));

	//  t_paire_ecrire_fichier
	//  - creation d'un fichier de test
	FILE *fichier = fopen(nom_fichier_test, "w");
	t_paire_ecrire_fichier(fichier, paire1);
	t_paire_ecrire_fichier(fichier, paire2);
	fclose(fichier);

	//  - validations sur le fichier
	char *lignes2[] = {
		"expression simple : Definition de cette expression simple.\n",
		"protocole de communication : Specification de plusieurs regles pour un type de communication particulier.\n"
	};
	utils_verifier_fichier(nom_fichier_test, lignes2, 2);

	//  t_paire_liberer
	t_paire_liberer(paire1);
	t_paire_liberer(paire2);

	assert(mon_rapport(false) == 0);

	printf("TEST paire : OK\n");
}
