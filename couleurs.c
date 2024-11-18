//
// Created by root on 11/09/24.
//
#include "couleurs.h"
#include <stdio.h>

#define ESCAPE "\033["
#define RESET "0m"

void couleurs_set(int style, int couleur_avant_plan, int couleur_arriere_plan) {
    printf("%s%d;%d;%dm", ESCAPE, style, couleur_avant_plan, couleur_arriere_plan);
    fflush(stdout);
}

void couleurs_reset() {
    printf("%s0m", ESCAPE);
    fflush(stdout);
}
