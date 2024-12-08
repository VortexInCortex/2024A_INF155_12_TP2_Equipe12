//
// Created by stephane on 12/11/24.
//

#ifndef CHATBOT_H
#define CHATBOT_H

// ------------------------------------
// Declarations des fonctions publiques
// ------------------------------------
/**
 * @name chatBot
 * @short execute une session complete du ChatBot.
 * @param nom_fichier_donnees le nom du fichier de donnees. Si NULL, la ChatBot va creer une base de donnees vide.
 * @return rien.
 * @details Commence par lire le fichier de donnees dont le nom est donne en parametre.
 * Si le nom est vide, le ChatBot creer une base de donnees vide.\n
 * Ensuite, le ChatBot pose des questions, jusqu'a ce que l'utilisateur choisisse de quitter.
 * Quand l'utilisateur desire quitter l'application, on sauvegarde la base de donnees, on desalloue la memoire utilisee
 * et on quitte l'application.
 */
void chatBot(const char *nom_fichier_donnees);

/**
 * @name chatBot_test
 * @short teste les fonctions du module de chatBot.
 * @returns rien.
 * @remark cette fonction est fournie.
 */
void chatBot_test();

#endif //CHATBOT_H
