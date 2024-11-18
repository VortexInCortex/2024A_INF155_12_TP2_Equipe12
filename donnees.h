//
// Created by duval on 2024-11-04.
//

#ifndef DONNEES_H
#define DONNEES_H

#include <stdbool.h>
#include <stddef.h>

// -------------------------------
// Declaration du type des donnees
// -------------------------------
/**
 * @details le type pour un tableau dynamique de donnees.
 */
typedef struct s_donnees t_donnees;

// ------------------------------------
// Declarations des fonctions publiques
// ------------------------------------
/**
 * @name t_donnees_creer
 * @short cree un nouveau tableau de donneees dont on donne la capacite en parametre.
 * @param capacite la capacite pour le nouveau tableau de donnees.
 * @return un pointeur sur le nouveau tableau de donnees.
 */
t_donnees *t_donnees_creer(size_t capacite);

/**
 * @name t_donnees_liberer
 * @short libere toutes les allocations memoire pour un tableau de donnees passe en parametre.
 * @param donnees le tableau de donnees a desallouer.
 * @return rien.
 */
void t_donnees_liberer(t_donnees *donnees);

/**
 * @name t_donnees_afficher
 * @short affiche toutes les informations contenues dans un tableau de donnees passe en parametre.
 * @param donnees le tableau de donnees.
 * @return rien.
 */
void t_donnees_afficher(const t_donnees *donnees);

/**
* @name t_donnees_inserer
* @short insere une paire dans un tableau de donnees passe en parametre. L'expression et la definition sont passees en parametres.
* @param donnees le tableau de donnees.
* @param expression l'expression de la nouvelle paire.
* @param definition la definition de la nouvelle paire.
* @return rien.
*/
void t_donnees_inserer(t_donnees *donnees, const char *expression, const char *definition);

/**
* @name t_donnees_chercher_definition
* @short recherche, dans une base de donnees, la meilleure paire qui correspond a un mot se trouvant dans une question et
* place l'adresse de son expression et l'adresse de sa definition dans les parametres correspondants.\n
* Si rien n'a ete trouve, place NULL dans les zones pointees par expression et definition.
* @param donnees le tableau de donnees.
* @param question la question dans laquelle chercher le mot.
* @param mot le mot qui commence l'expression cherchee.
* @param expression pointeur ou placer l'expression trouvee.
* @param definition pointeur ou placer la definition trouvee.
* @return rien.
* @attention la question doit etre en lettres minuscules.
*/
void t_donnees_chercher_definition(t_donnees *donnees, char *question, char *mot, const char **expression,
                                   const char **definition);

/**
 * @name t_donnees_creer_fichier
 * @short cree un tableau dynamique de donnees a partir du contenu d'un fichier.
 * @param nom_fichier le nom du fichier a lire.
 * @return un pointeur sur un nouveau tableau dynamique de donnees contenant toutes les donnees contenues dans le fichier.
 */
t_donnees *t_donnees_lire_fichier(const char *nom_fichier);

/**
 * @name t_donnees_ecrire_fichier
 * @short cree un fichier a partir d'un tableau de donnees.
 * @param donnees un pointeur sur le tableau de donnees.
 * @param nom_fichier le nom du fichier a lire.
 * @return true si l'ecriture s'est bien passee, false sinon.
 */
bool t_donnees_ecrire_fichier(t_donnees *donnees, const char *nom_fichier);

/**
 * @name t_donnees_test
 * @short teste les fonctions du module des donnees.
 * @return rien.
 * @remark cette fonction est fournie.
 */
void t_donnees_test();

#endif //DONNEES_H
