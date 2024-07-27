#include "utils.h"

void sleep_ms(long milliseconds) {
    clock_t start = clock();
    while (1) {
        if (clock() - start >= milliseconds) {
            break;
        }
    }
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
    char* total_linebreak = repeat(row - 1, "\n");
    printf("\033[H%s", total_linebreak);
    free(total_linebreak);
}
