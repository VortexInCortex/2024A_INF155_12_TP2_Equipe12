//
// Created by duval on 2024-11-04.
//

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

// ------------------------------------
// Declarations des fonctions publiques
// ------------------------------------
/**
 * @name utils_chaine_minuscules
 * @short met tous les caracteres de la chaine passee en parametre en minuscules.
 * @param chaine chaine qui doit etre mise en minuscules.
 * @return le debut de la chaine resultat.
 * @remark change la zone pointee.
 */
char *utils_chaine_minuscules(char *chaine);

/**
 * @name utils_chaine_tailler
 * @short enleve les espaces en tete et en fin de chaine.
 * @param chaine la chaine a tailler.
 * @return le debut de la chaine resultat.
 * @remark change la zone pointee.
 */
char *utils_chaine_tailler(char *chaine);

/**
 * @name utils_ligne_decouper
 * @short separe le mot-clef de sa definition.
 * @param ligne pointeur sur la ligne a decouper.
 * @param expression pointeur sur la zone memoire ou placer l'expression'.
 * @param definition pointeur sur la zone memoire ou placer la definition.
 * @return rien.
 * @remark change les zones pointees par expression et definition.
 */
void utils_chaine_decouper(char *ligne, char *expression, char *definition, const char *delimiteurs);

/**
 * @name utils_premier_mot
 * @short trouve le premier mot d'une expression passee en parametre.
 * @param expression pointeur sur la zone memoire de l'expression.
 * @param mot pointeur sur la zone memoire ou placer le prermier mot.
 * @return rien.
 * @remark change la zone pointee par mot.
 */
void utils_chaine_premier_mot(const char *expression, char *mot);

/**
 * @name utils_saisir_oui_non
 * @short demande une reponse oui ou non a l'utilisateur.
 * @return true si l'utilisateur a repondu oui, non sinon.
 */
bool utils_saisir_oui_non();

/**
 * @name utils_fichier_ligne_suivante
 * @short lit la prochaine ligne dans le fichier specifie.
 * @param nom_fichier le nom du fichier dans lequel lire la prochaine ligne.
 * @return pointeur sur le debut de la prochaine ligne.
 * @remark cette fonction vous est fournie.
 */
char *utils_fichier_ligne_suivante(const char *nom_fichier);

/**
 * @name utils_test
 * @short teste les fonctions du module des utilitaires.
 * @return rien.
 * @remark cette fonction est fournie.
 */
void utils_test();

#endif //UTILS_H
