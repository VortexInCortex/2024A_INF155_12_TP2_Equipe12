//
// Created by root on 11/09/24.
//

#ifndef COULEURS_H
#define COULEURS_H

// Styles de caracteres
#define STYLE_RESET         0
#define STYLE_BOLD          1
#define STYLE_DIM           2
#define STYLE_ITALIC        3
#define STYLE_UNDERLINE     4
#define STYLE_BLINK         5
#define STYLE_INVERSE       7
#define STYLE_HIDDEN        8
#define STYLE_STRIKETHROUGH 9

// Couleurs d'avant-plan
#define FG_BLACK            30
#define FG_RED              31
#define FG_GREEN            32
#define FG_YELLOW           33
#define FG_BLUE             34
#define FG_MAGENTA          35
#define FG_CYAN             36
#define FG_WHITE            37
#define FG_BRIGHT_BLACK     90
#define FG_BRIGHT_RED       91
#define FG_BRIGHT_GREEN     92
#define FG_BRIGHT_YELLOW    93
#define FG_BRIGHT_BLUE      94
#define FG_BRIGHT_MAGENTA   95
#define FG_BRIGHT_CYAN      96
#define FG_BRIGHT_WHITE     97

// Couleurs d'arriere-plan
#define BG_BLACK            40
#define BG_RED              41
#define BG_GREEN            42
#define BG_YELLOW           43
#define BG_BLUE             44
#define BG_MAGENTA          45
#define BG_CYAN             46
#define BG_WHITE            47
#define BG_BRIGHT_BLACK     100
#define BG_BRIGHT_RED       101
#define BG_BRIGHT_GREEN     102
#define BG_BRIGHT_YELLOW    103
#define BG_BRIGHT_BLUE      104
#define BG_BRIGHT_MAGENTA   105
#define BG_BRIGHT_CYAN      106
#define BG_BRIGHT_WHITE     107

/**
 * @name couleurs_set
 * @short specifie une style, une couleur de fond et une couleur d'avant-plan pour les caracteres affiches dans la console.
 * @param style le style de caractere.
 * @param couleur_avant_plan la coucleur d'avant-plan.
 * @param couleur_arriere_plan la couleur d'arriere-plan.
 * @return rien.
 */
void couleurs_set(int style, int couleur_avant_plan, int couleur_arriere_plan);

/**
 * @name couleurs_reset
 * @short remet les valeurs par defaut pour le style, la couleur d'avant-plan et la couleur d'arriere-plan pour les caracteres affiches dans la console.
 * @return rien.
 */
void couleurs_reset();

#endif //COULEURS_H
