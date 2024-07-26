#include "game_manager.h"

struct game_object* all_playable_object;
struct game_object* current_used_object;

int current_used_object_amount;
int playable_object_amount;

void parse_new_answer(char* answer_line) {
    printf("Working with: '%s'\n", answer_line);
}

void load_game_object(int* is_valid) {
    FILE *game_config_file = fopen(GAME_CONFIG_FILE_NAME, "r");

    if (!game_config_file) {
        (*is_valid) = 0;
        fclose(game_config_file);
        return;
    }

    char* current_line_buffer = calloc(CURRENT_LINE_BUFFER_SIZE, sizeof(char));
    char* current_line;

    int processing_answer = 0;

    while (fgets(current_line_buffer, CURRENT_LINE_BUFFER_SIZE, game_config_file)) {
        current_line = replace_last(current_line_buffer, CURRENT_LINE_BUFFER_SIZE,
                                    "\n", sizeof("\n"),
                                    " ", sizeof(" "));
        printf("Raw line: '%s'\n", current_line_buffer);
        printf("Active line: '%s'\n", current_line);
        if (equals_string(current_line, ANSWER_SECTION_START, sizeof(ANSWER_SECTION_START) / sizeof(char))) {
            processing_answer = 1;
            continue;
        }

        if (equals_string(current_line, ANSWER_SECTION_END, sizeof(ANSWER_SECTION_END) / sizeof(char))) {
            processing_answer = 0;
            continue;
        }

        if (processing_answer) {
            parse_new_answer(current_line);
            continue;
        }

        free(current_line);
    }

    (*is_valid) = 1;
    free(current_line_buffer);
    fclose(game_config_file);
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