//
// Created by duval on 2024-11-10.
//
#include "mon_malloc.h"

#undef malloc
#undef free

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "couleurs.h"

static size_t malloc_calls = 0;
static size_t free_calls = 0;

void *mon_malloc(size_t taille) {
    malloc_calls++;
    return malloc(taille);
}

void mon_free(void *ptr) {
    free_calls++;
    free(ptr);
}

long long mon_rapport(bool affiche) {
    if (affiche) {
        couleurs_set(STYLE_UNDERLINE, FG_BRIGHT_GREEN, BG_BRIGHT_WHITE);
        couleurs_set(STYLE_BOLD, FG_BRIGHT_GREEN, BG_BRIGHT_WHITE);
        printf("mon_rapport :\n");
        couleurs_reset();
        couleurs_set(STYLE_BOLD, FG_BRIGHT_GREEN, BG_BRIGHT_WHITE);
        printf("  malloc calls: %ld\n", malloc_calls);
        printf("  free calls: %ld\n", free_calls);
    }

    if (malloc_calls != free_calls) {
        couleurs_set(STYLE_BOLD, FG_BRIGHT_RED, BG_BRIGHT_WHITE);
        printf("ATTENTION : Le nombre d'allocations differe du nombre de desallocations !\n");
    }
    couleurs_reset();

    return (long long) malloc_calls - (long long) free_calls;
}
