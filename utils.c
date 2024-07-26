#include "utils.h"

int equals_string(const char* first, const char* second, int check_length) {
    for (int i = 0; i < check_length ; i++) {
        if (first[i] == second[i]) {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
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
