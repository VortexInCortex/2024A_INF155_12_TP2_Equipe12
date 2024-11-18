//
// Created by stephane on 12/11/24.
//

#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>

// ----------------------------------------------
// Declaration de la structure de liste de paires
// ----------------------------------------------
/**
 * @details le type des listes de paires.
 */
typedef struct s_liste t_liste;

// -----------------------------------
// Definitions des fonctions publiques
// -----------------------------------
/**
 * @name t_liste_creer
 * @short cree et retourne une nouvelle liste a partir d'une expression, de sa definition et du reste de la liste.
 * @return un pointeur sur une nouvelle liste dont le premier element est la paire et le reste est suivant.
 */
t_liste *t_liste_creer_vide();

/**
 * @name t_liste_liberer
 * @short libere toutes les zones memoire allouees pour une liste passee en parametre.
 * @param liste un pointeur sur la liste a liberer.
 * @return rien.
 * @remark toutes les zones memoire allouees pour cette liste sont liberees.
 */
void t_liste_liberer(t_liste *liste);

/**
 * @name t_liste_afficher
 * @short affiche toutes les informations d'une liste de paires.
 * @param liste un pointeur sur la liste.
 * @return rien.
 */
void t_liste_afficher(const t_liste *liste);

/**
 * @name t_liste_ajouter
 * @short ajoute une paire a une liste de paires.
 * @param liste un pointeur sur la liste.
* @param expression une expression.
 * @param definition la definition pour l'expression.
 * @return un pointeur sur la nouvelle liste.
 */
t_liste *t_liste_ajouter(t_liste *liste, const char *expression, const char *definition);

/**
 * @name t_liste_get_infos
 * @short lit la premiere paire de la liste et place l'adresse de son expression dans le parametre expression.
 * Idem avec la definition.
 * @param liste un pointeur sur la liste.
 * @param expression l'adresse du pointeur ou placer l'adresse de l'expression.
 * @param definition l'adresse du pointeur ou placer l'adresse de la definition.
 * @return rien.
 */
void t_liste_get_infos(const t_liste *liste, const char **expression, const char **definition);

/**
 * @name t_liste_chercher
 * @short chercher une paire de la liste dont l'expression est contenue dans la question passee en parametre.
 * Parmi toutes les paires possibles, on choisit celle dont l'expression est la plus longue.
 * @param liste un pointeur sur la liste.
 * @param question un pointeur sur l'expression a chercher.
 * @param expression un pointeur sur une zone pour placer la meilleure expression trouvee.
 * @param definition un pointeur sur une zone pour placer la definition de la meilleure expression trouvee.
 * @return rien.
 * @remark les adresses de la meilleure expression et de sa definition sont placees dans les parametres formels correspondants.
 */
void t_liste_chercher(const t_liste *liste, const char *question, const char **expression,
                      const char **definition);

/**
 * @name t_liste_ecrire_fichier
 * @short ecrit toutes les informations d'une liste dans un fichier dont le nom est passe en parametre.
 * @param fichier le fichier dans lequel ecrire les informations de la liste.
 * @param liste un pointeur sur la liste.
 * @return rien.
 */
void t_liste_ecrire_fichier(FILE *fichier, const t_liste *liste);

/**
 * @name t_liste_test
 * @short teste toutes les fonctions du module de liste.
 * @return rien.
 * @remark cette fonction est fournie.
 */
void t_liste_test();

#endif //LISTE_H
