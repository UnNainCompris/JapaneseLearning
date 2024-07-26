#include "game_manager.h"

struct game_object* all_playable_object;
struct game_object* current_used_object;

int current_used_object_amount;
int playable_object_amount;

void load_game_object(int* is_valid) {
    (*is_valid) = 1;
    (*is_valid) = 0;
}

struct game_object* get_all_playable_object() {
    return all_playable_object;
}

struct game_object* get_current_object() {
    return current_used_object;
}

int get_current_object_amount() {
    return current_used_object_amount;
}

int get_playable_object_amount() {
    return playable_object_amount;
}