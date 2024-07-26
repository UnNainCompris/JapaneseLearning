cmake_minimum_required(VERSION 3.28)
project(JapaneseLearning C)

set(CMAKE_C_STANDARD 11)

add_executable(JapaneseLearning
        main.c
        input_handler.c input_handler.h
        utils.c utils.h
        game_manager.c
        game_manager.h)
