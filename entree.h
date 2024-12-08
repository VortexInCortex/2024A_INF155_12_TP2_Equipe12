//
// Created by stephane on 12/11/24.
//

#ifndef ENTREE_H
#define ENTREE_H

#include <stdio.h>

// -------------------------------------------------------
// Declaration du type des entrees pour la base de donnees
// -------------------------------------------------------
/**
 * @details le type des entrees dans le tableau dynamiques des donnees.
 */
typedef struct s_entree t_entree;

// -----------------------------------
// Definitions des fonctions publiques
// -----------------------------------
/**
 * @name t_entree_creer
 * @short retourne l'adresse d'une nouvelle entree pour un mot passe en parametre.
 * @param mot un pointeur sur le mot pour cette entree.
 * @return un pointeur sur la nouvelle entree.
 */
t_entree *t_entree_creer(const char *mot);

/**
 * @name t_entree_liberer
 * @short libere la zone memoire allouee pour une entree.
 * @param entree un pointeur sur l'entree a desallouer.
 * @return rien.
 * @remark toutes les donnees allouees pour cette entree sont liberees.
 */
void t_entree_liberer(t_entree *entree);

/**
 * @name t_entree_afficher
 * @short affiche toutes les informations concernant une entree passee en parametre.
 * @param entree un pointeur sur l'entree.
 * @return rien.
 */
void t_entree_afficher(const t_entree *entree);

/**
 * @name t_entree_get_mot
 * @short retourne le mot associe a une entree passee en parametre.
 * @param entree un pointeur sur l'entree.
 * @return le mot associe a cette entree.
 */
char *t_entree_get_mot(const t_entree *entree);

/**
 * @name t_entree_chercher
 * @short cherche une paire de la liste dont l'expression se trouve dans la question.
 * @param entree un pointeur sur l'entree.
 * @param question un pointeur sur la question dans laquelle chercher l'expression.
 * @param expression un pointeur sur un pointeur dans lequel placer l'adresse de l'expression trouvee.
 * @param definition un pointeur sur un pointeur dans lequel placer l'adresse de la definition trouvee.
 * @return la paire dont l'expression se trouve dans la question et pour laquelle l'expression est de taille maximale.
 */
void t_entree_chercher(t_entree *entree, const char *question, const char **expression, const char **definition);

/**
 * @name t_entree_ajouter
 * @short ajoute une paire a la liste d'une entree passee en parametre.
 * @param entree l'entree a laquelle ajouter la nouvelle paire.
 * @param expression l'expression a ajouter.
 * @param definition la definition de cette expression.
 * @return rien.
 * @remark la zone pointee par entree est mise a jour.
 */
void t_entree_ajouter(t_entree *entree, const char *expression, const char *definition);

/**
 * @name t_entree_ecrire_fichier
 * @short ecrit toutes les donnees de l'entree dans le fichier passe en paarmetre.
 * @param fichier le fichier dans lequel ecrire les donnees.
 * @param entree l'entree a ecrire dans le fichier.
 */
void t_entree_ecrire_fichier(FILE *fichier, const t_entree *entree);

/**
 * @name t_entree_test
 * @short teste toutes les fonctions du module des entrees.
 * @return rien.
 * @remark cette fonction est fournie.
 */
void t_entree_test();

#endif //ENTREE_H
