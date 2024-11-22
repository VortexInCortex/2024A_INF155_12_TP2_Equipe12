cmake_minimum_required(VERSION 3.29)
project(ChatBotV2 C)

set(CMAKE_C_STANDARD 11)

add_executable(ChatBotV2 main.c
        utils.h
        utils.c
        paire.h
        paire.c
        donnees.h
        donnees.c
        mon_malloc.h
        mon_malloc.c
        couleurs.h
        couleurs.c
        liste.h
        liste.c
        entree.h
        entree.c
        chatBot.h
        chatBot.c)
