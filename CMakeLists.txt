cmake_minimum_required(VERSION 3.29)
project(ChatBotV2 C)

set(CMAKE_C_STANDARD 11)

add_executable(ChatBotV2 main.c
        liste.c
        utils.h
        mon_malloc.c
        utils.c
        entree.c
        paire.h
        paire.c
        entree.h
        liste.h
        mon_malloc.h
        couleurs.c
        donnees.h
        chatBot.h
        couleurs.h
        donnees.c
        chatBot.c)
