#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

struct game_object {
    char* display_text;
    char** possible_answer;
    char* hint_text;
    char* other_text;
};

void load_game_object(int* is_valid);

struct game_object* get_all_playable_object();
struct game_object* get_current_object();

int get_current_object_amount();
int get_playable_object_amount();

#endif //GAME_MANAGER_H
