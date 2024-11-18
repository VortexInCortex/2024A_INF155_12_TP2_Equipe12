//
// Created by duval on 2024-11-04.
//

#ifndef PAIRE_H
#define PAIRE_H

#include <stdbool.h>
#include <stdio.h>

// ------------------------------------------------------------
// Declaration de la structure de paire [expression/definition]
// ------------------------------------------------------------
/**
 * @details le type des paires (expression, definition).
 */
typedef struct s_paire t_paire;

// ------------------------------------
// Declarations des fonctions publiques
// ------------------------------------
/**
 * @name t_paire_creer
 * @short cree et retourne une nouvelle paire expression/definition.
 * @param expression pointeur sur la zone memoire de l'expression'.
 * @param definition pointeur sur la zone memoire de la definition.
 * @return la nouvelle paire.
 * @remark l'expression est mise en minuscule dans la paire.
 */
t_paire *t_paire_creer(const char *expression, const char *definition);

/**
 * @name t_paire_liberer
 * @short libere la zone memoire allouee pour une paire.
 * @param paire pointeur sur la paire a liberer.
 * @return rien.
 * @remark toute le zones memoire allouees pour cette paire sont desallouees.
 */
void t_paire_liberer(t_paire *paire);

/**
 * @name t_paire_afficher
 * @short affiche l'expression d'une paire ainsi que sa definition.
 * @param paire pointeur sur la paire.
 * @return rien.
 */
void t_paire_afficher(const t_paire *paire);

/**
 * @name t_paire_get_expression
 * @short retourne l'expression associee a une paire passee en parametre.
 * @param paire pointeur sur la paire.
 * @return l'expression associee a cette paire.
 */
const char *t_paire_get_expression(const t_paire *paire);

/**
 * @name t_paire_get_expression
 * @short retourne la longueur de l'expression associee a une paire passee en parametre.
 * @param paire pointeur sur la paire.
 * @return la longueur de l'expression associee a cette paire.
 */
size_t t_paire_get_longueur(const t_paire *paire);

/**
 * @name t_paire_get_definition
 * @short retourne la definition associee a une paire passee en parametre.
 * @param paire pointeur sur la paire.
 * @return la definition associee a cette paire.
 */
const char *t_paire_get_definition(const t_paire *paire);

/**
 * @name t_paire_contient
 * @short cherche si l'expression d'une paire se trouve dans une question.
 * @param paire pointeur sur la paire.
 * @param question pointeur sur la question dans laquelle chercher.
 * @return true si l'expression a ete trouvee, false sinon.
 */
bool t_paire_contient(const t_paire *paire, const char *question);

/**
 * @name t_paire_ecrire_fichier
 * @short ecrit les informations d'une paire dans un fichier passe en parametre.
 * @param fichier le fichier dans lequel ecrire.
 * @param paire pointeur sur la paire.
 * @return rien.
 */
void t_paire_ecrire_fichier(FILE *fichier, t_paire *paire);

/**
 * @name t_paire_test
 * @short teste toutes les fonctions du module des paires.
 * @return rien.
 * @remark cette fonction est fournie.
 */
void t_paire_test();

#endif //PAIRE_H
