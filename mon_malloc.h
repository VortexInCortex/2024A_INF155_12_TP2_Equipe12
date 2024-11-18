//
// Created by duval on 2024-11-10.
//

#ifndef MM_H
#define MM_H

#define malloc mon_malloc
#define free mon_free

#include <stdbool.h>
#include <stddef.h>

/**
 * @name mon_malloc
 * @short comme malloc, retourne l'adresse d'une nouvelle zone memoire de taille 'size'.
 *        La fonction compte le nombre d'allocations'.
 * @param taille un pointeur sur le mot pour cette entree.
 * @return un pointeur sur la nouvelle zone memoire.
 */
void *mon_malloc(size_t taille);

/**
 * @name mon_free
 * @short comme free, libere une zone memoire prealablement allouee.
 * La fonction compte le nombre de desallocations.
 * @param ptr le pointeur d'une zone precedemment allouee.
 * @return rien.
 */
void mon_free(void *ptr);

/**
 * @name mon_rapport
 * @short affiche le nombre total des allocations et le nombre total des desallocations memoire effectuees.
 * @param affiche si true, affiche le rapport, sinon, ne l'affiche pas.
 * @return la difference allocations - desallocations.
 */
long long mon_rapport(bool affiche);

#endif //MM_H
