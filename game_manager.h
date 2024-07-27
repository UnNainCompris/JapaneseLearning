#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#define GAME_CONFIG_FILE_NAME "game_config.txt"
#define CURRENT_LINE_BUFFER_SIZE 512

#define ANSWER_SECTION_START "-<ANSWER>-"
#define ANSWER_SECTION_END "-</ANSWER>-"

#include <stdio.h>

#include "string_utils.h"

struct game_object {
    char* display_text;
    char** possible_answer;
    char* hint_text;
};

void load_game_object(int* is_valid);

struct game_object* get_all_playable_object();
struct game_object* get_current_object();

int get_current_object_amount();
int get_playable_object_amount();

#endif //GAME_MANAGER_H
