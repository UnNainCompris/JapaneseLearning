#include "string_utils.h"

int strlength(const char* string) {
    if (string == NULL) {
        return 0;
    }

    int size = 0;
    while (string[size]) {
        size++;
    }
    return size;
}

char* copy(const char* string) {
    if (string == NULL) {
        return NULL;
    }

    int string_length = strlength(string);
    char* copy = malloc((string_length + 1) * sizeof(char));
    if (!copy) {
        return NULL;
    }
    for (int index = 0 ; index < string_length ; index++) {
        copy[index] = string[index];
    }
    copy[string_length] = '\0';
    return copy;
}

char* substring(const char* string, int start, int end) {
    if (!string) {
        return NULL;
    }

    const int string_length = strlength(string);

    start = min(max(start, 0), string_length);
    end = min(max(end, 0), string_length);

    if (start == end) {
        return copy("");
    }

    if (start >= end) {
        return NULL;
    }

    char* result = calloc(end - start + 1, sizeof(char));
    if (!result) {
        return NULL; // Handle calloc failure
    }

    for (int index = start ; index < end ; index++) {
        if (string[index]) {
            result[index - start] = string[index];
        } else {
            break;
        }
    }

    result[end - start] = '\0';
    return result;
}

int count_matching_row_char(const char* string, const char* model) {
    if (string == NULL || model == NULL) {
        return 0;
    }

    int matching = 0, model_length = strlength(model);
    while (matching < model_length && string[matching] && model[matching]) {
        if (string[matching] == model[matching]) {
            matching++;
        } else {
            break;
        }
    }

    return matching;
}

int count_matching_char(const char* string, const char* model) {
    int matching = 0, model_length = strlength(model);
    while (matching < model_length && string[model_length] && model[model_length]) {
        if (string[matching] == model[matching]) {
            matching++;
        } else {
            break;
        }
    }

    return matching;
}

int* find_index(const char* string, const char* model, int* amount_of_index) {
    if (string == NULL || model == NULL) {
        return NULL;
    }

    int should_free_index_amount = 0;
    if (amount_of_index == NULL) {
        amount_of_index = malloc(sizeof(int));
        should_free_index_amount = 1;
    }

    int model_length = strlength(model);
    (*amount_of_index) = count(string, model);
    int* buffer = calloc(*amount_of_index, sizeof(int));
    if (!buffer) {
        return NULL;
    }
    int buffer_index = 0;

    for (int index = 0 ; index < strlength(string) ; index++) {
        if (string[index] == model[0]) {
            char* sub = substring(string, index, index + model_length);
            if (start_with(sub, model)) {
                buffer[buffer_index] = index;
                index += model_length - 1;
                buffer_index++;
            }
            free(sub);
        }
    }

    if (should_free_index_amount) {
        free(amount_of_index);
    }

    return buffer;
}


int start_with(const char* string, const char* model) {
    if (string == NULL || model == NULL) {
        return 0;
    }

    for (int i = 0 ; i < strlength(model) ; i++) {
        if (string[i] != model[i]) {
            return 0;
        }
    }
    return 1;
}

int count(const char* string, const char* model) {
    int found = 0;
    int model_length = strlength(model);

    for (int index = 0 ; index < strlength(string) ; index++) {
        if (string[index] == model[0]) {
            char* sub = substring(string, index, index + model_length);
            if (start_with(sub, model)) {
                found++;
                index += model_length - 1;
            }
            free(sub);
        }
    }

    return found;
}
#include <stdio.h>
char* replace(const char* string, const char* to_replace, const char* replacement, int limit) {
    printf("1a\n");
    int string_length = strlength(string);
    printf("2a\n");
    int to_replace_length = strlength(to_replace);
    printf("3a\n");
    int replacement_length = strlength(replacement);
    printf("4a\n");

    int max_length = max(to_replace_length, replacement_length) * string_length;
    printf("5a %i\n", max_length);
    char* buffer = calloc((max_length * 10), sizeof(char));
    printf("6a\n");
    int active_buffer_size = 0;
    printf("7a\n");

    int amount_of_replace = 0;
    printf("8a\n");

    for (int i = 0 ; i < string_length ; i++) {
        char* sub = substring(string, i, to_replace_length + i);
        printf("b\n");
        if (count_matching_row_char(sub, to_replace) == to_replace_length && amount_of_replace != limit) {
            printf("c\n");
            for (int replacement_index = 0 ; replacement_index < replacement_length ; replacement_index++) {
                printf("d\n");
                buffer[active_buffer_size] = replacement[replacement_index];
                active_buffer_size++;
            }
            printf("e\n");
            amount_of_replace++;
            i += to_replace_length - 1;
        } else {
            printf("f\n");
            buffer[active_buffer_size] = string[i];
            active_buffer_size++;
        }
        printf("g\n");
        free(sub);
        printf("h\n");
    }
    active_buffer_size++;
    char* replaced_string = realloc(buffer, (active_buffer_size + 1) * sizeof(char));
    if(!replaced_string) {
        printf("x\n");
        return buffer;
    } else {
        printf("y\n");
        buffer[active_buffer_size] = '\0';
        return replaced_string;
    }
}

char* replace_first(const char* string, const char* to_replace, const char* replacement) {
    return replace(string, to_replace, replacement, 1);
}

char* replace_from_end(const char* string, const char* to_replace, const char* replacement, int limit) {
    int string_length = strlength(string);
    int to_replace_length = strlength(to_replace);
    int replacement_length = strlength(replacement);

    int max_length = max(to_replace_length, replacement_length) * string_length;
    char* buffer = calloc(max_length, sizeof(char));
    int active_buffer_size = 0;

    int max_amount_of_replace = count(string, to_replace);
    int current_replace_index = 0;

    for (int i = 0 ; i < string_length ; i++) {
        char* sub = substring(string, i, to_replace_length + i);
        if (count_matching_row_char(sub, to_replace) == to_replace_length) {
            if (max_amount_of_replace - current_replace_index <= limit) {
                for (int replacement_index = 0; replacement_index < replacement_length; replacement_index++) {
                    buffer[active_buffer_size] = replacement[replacement_index];
                    active_buffer_size++;
                }
            } else {
                for (int replacement_index = 0; replacement_index < to_replace_length; replacement_index++) {
                    buffer[active_buffer_size] = to_replace[replacement_index];
                    active_buffer_size++;
                }
            }

            i += to_replace_length - 1;
            current_replace_index++;
        } else {
            buffer[active_buffer_size] = string[i];
            active_buffer_size++;
        }
        free(sub);
    }
    active_buffer_size++;
    buffer[active_buffer_size] = '\0';
    char* replaced_string = realloc(buffer, active_buffer_size * sizeof(char));
    if(!replaced_string) {
        return buffer;
    } else {
        return replaced_string;
    }
}

char* replace_last(const char* string, const char* to_replace, const char* replacement) {
    return replace_from_end(string, to_replace, replacement, 1);
}

char** split(char* string, const char* splitter, int limit, int* string_amount) {
    int max_split = count(string, splitter) + 1;
    int required_split_amount = (limit <= 0 ? max_split : limit);

    char** buffer = malloc(required_split_amount * sizeof(char*));
    int buffer_index = 0;

    if (required_split_amount == 1) {
        buffer[0] = string;
        buffer_index++;
    } else {
        int last_index = 0, index_amount = 0, splitter_length = strlength(splitter);
        int* split_index_list = find_index(string, splitter, &index_amount);

        if (split_index_list == NULL) {
            return NULL;
        }

        for (int i = 0 ; i < index_amount ; i++) {
            int current_index = split_index_list[i];
            buffer[buffer_index] = substring(string, last_index, current_index);
            last_index = current_index + splitter_length;
            buffer_index++;
        }
        buffer[buffer_index] = substring(string, last_index, strlength(string));
        buffer_index++;
        free(split_index_list);
    }

    if (string_amount != NULL) {
        (*string_amount) = buffer_index;
    }

    return buffer;
}

int strequals(const char* first, const char* second) {
    int index = 0;
    while (1) {
        if (!first[index] && !second[index]) {
            return 1;
        }

        if (first[index] != second[index]) {
            return 0;
        }

        index++;
    }
}

char* repeat(int times, const char* string) {
    int string_length = strlength(string);
    char* buffer = calloc((times * string_length) + 1, sizeof(char));
    int buffer_index = 0;

    for (int i = 0 ; i < times ; i++) {
        for (int x = 0 ; x < string_length ; x++) {
            buffer[buffer_index] = string[x];
            buffer_index++;
        }
    }

    buffer[times * string_length] = '\0';
    return buffer;
}

char to_upper(char chr) {
    if (chr >= 97 && chr <= 122) {
        return chr - 32;
    } else {
        return chr;
    }
}

char* str_to_upper(char* string) {
    int string_length = strlength(string);
    char* buffer = malloc((string_length + 1) * sizeof(char));

    for (int index = 0 ; string[index] ; index++) {
        buffer[index] = to_upper(string[index]);
    }

    buffer[string_length] = '\0';

    return buffer;
}

char to_lower(char chr) {
    if (chr >= 65 && chr <= 90) {
        return chr + 32;
    } else {
        return chr;
    }
}

char* str_to_lower(char* string) {
    int string_length = strlength(string);
    char* buffer = malloc((string_length + 1) * sizeof(char));

    for (int index = 0 ; string[index] ; index++) {
        buffer[index] = to_lower(string[index]);
    }

    buffer[string_length] = '\0';

    return buffer;
}

