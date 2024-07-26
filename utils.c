#include "utils.h"

int equals_string(const char* first, const char* second, int check_length) {
    for (int i = 0 ; i < check_length ; i++) {
        if (first[i] == second[i]) {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}

char* replace_last(const char* string, int string_length,
                   const char* to_replace, int to_replace_length,
                   const char* replacement, int replacement_length) {
    to_replace_length--; replacement_length--; string_length--; // because char* start at 1 byte when empty

    int max_length = max(to_replace_length, replacement_length) * string_length;

    char* buffer = calloc(max_length, sizeof(char));
    char* clone_buffer = calloc(max_length, sizeof(char));

    int buffer_index = 0;

    int matching = 0;
    int index = 0;

    for (int i = 0 ; i <= string_length ; i++) {
        while (matching < to_replace_length) {
            if (string[i + matching] == to_replace[matching]) {
                matching++;
            } else {
                break;
            }
        }

        if (matching == to_replace_length) {
            for (int x = 0 ; x <= max(buffer_index, i) ; x++) {
                buffer[x] = clone_buffer[x];
            }
            buffer_index = i;

            while (index < replacement_length) {
                buffer[buffer_index] = replacement[index];
                index++;
                buffer_index++;
            }

            for (int x = i ; x < i + to_replace_length - 1 ; x++) {
                clone_buffer[x] = string[x];
            }

            i += to_replace_length - 1;
            index = 0;
        } else {
            buffer[buffer_index] = string[i];
            buffer_index++;
        }

        clone_buffer[i] = string[i];
        matching = 0;
    }

    free(clone_buffer);
    return buffer;
}

char* replace(const char* string, int string_length,
                   const char* to_replace, int to_replace_length,
                   const char* replacement, int replacement_length) {
    to_replace_length--; replacement_length--; string_length--; // because char* start at 1 byte when empty

    int max_length = max(to_replace_length, replacement_length) * string_length;

    char* buffer = calloc(max_length, sizeof(char));
    int buffer_index = 0;

    int matching = 0;
    int index = 0;

    for (int i = 0 ; i <= string_length ; i++) {
        while (matching < to_replace_length) {
            if (string[i + matching] == to_replace[matching]) {
                matching++;
            } else {
                break;
            }
        }

        if (matching == to_replace_length) {
            while (index < replacement_length) {
                buffer[buffer_index] = replacement[index];
                index++;
                buffer_index++;
            }

            i += to_replace_length - 1;
            index = 0;
        } else {
            buffer[buffer_index] = string[i];
            buffer_index++;
        }

        matching = 0;
    }

    return buffer;
}

char* repeat(int times, char* to_repeat) {
    char* buffer = calloc(times + 1, sizeof(char));

    for (int i = 0 ; i < times ; i++) {
        strcat(buffer, to_repeat);
    }

    return buffer;
}

void sleep_ms(long milliseconds) {
    struct timespec req, rem;
    req.tv_sec = milliseconds / 1000;
    req.tv_nsec = (milliseconds % 1000) * 1000000L;
    nanosleep(&req, &rem);
}

int get_terminal_width() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return -1;
    }

    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int get_terminal_height() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return -1;
    }

    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void move_cursor_to_row(int row) {
    printf("\033[H%s", repeat(row - 1, "\n"));
}
