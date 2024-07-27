#include "game_manager.h"

game_object* all_playable_object;
game_object* current_used_object;

int current_used_object_amount;
int playable_object_amount;

int parse_new_answer(char* answer_line) {
    printf("Working with: '%s'\n", answer_line);

    int raw_data_length = 0;
    char** raw_data = split(answer_line, "|", -1, &raw_data_length);

    if (raw_data_length != 3) {
        return 0;
    }

    char* display_text = raw_data[0];
    int answer_amount = 0;
    char** possible_answer = split(raw_data[1], ";", -1, &answer_amount);
    char* hint_text = raw_data[2];

    game_object new_game_object = {display_text, possible_answer, answer_amount, hint_text};
    if (all_playable_object == NULL) {
        all_playable_object = malloc(sizeof(new_game_object));
    } else {
        all_playable_object = realloc(all_playable_object, sizeof(new_game_object) * (playable_object_amount + 1));
    }
    all_playable_object[playable_object_amount] = new_game_object;
    playable_object_amount++;

    return 1;
}

void load_game_object(int* is_valid) {
    FILE *game_config_file = fopen(GAME_CONFIG_FILE_NAME, "r");

    if (!game_config_file) {
        printf("File not found !\n");
        (*is_valid) = 0;
        fclose(game_config_file);
        return;
    }

    char* current_line_buffer = calloc(CURRENT_LINE_BUFFER_SIZE, sizeof(char));
    char* current_line;

    int is_processing_answer = 0;

    while (fgets(current_line_buffer, CURRENT_LINE_BUFFER_SIZE, game_config_file)) {
        current_line = replace(current_line_buffer, "\n", "", -1);
        if (strequals(current_line, ANSWER_SECTION_START)) {
            is_processing_answer = 1;
        }

        else if (strequals(current_line, ANSWER_SECTION_END)) {
            is_processing_answer = 0;
        }

        else if (is_processing_answer) {
            if (!parse_new_answer(current_line)) {
                (*is_valid) = 0;
                free(current_line_buffer);
                fclose(game_config_file);
                return;
            }
        }

        free(current_line);
    }

    (*is_valid) = 1;
    free(current_line_buffer);
    fclose(game_config_file);
}

game_object* get_all_playable_object() {
    return all_playable_object;
}

game_object* get_current_object() {
    return current_used_object;
}

int get_current_object_amount() {
    return current_used_object_amount;
}

int get_playable_object_amount() {
    return playable_object_amount;
}