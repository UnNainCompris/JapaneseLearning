#include "utils.h"

void sleep_ms(long milliseconds) {
    clock_t start = clock();
    while (1) {
        if (clock() - start >= milliseconds) {
            break;
        }
    }
}

int is_digit(char chr, int* digit) {
    int raw_digit_value = chr - '0';
    if (0 <= raw_digit_value && raw_digit_value <= 9) {
        if (digit != NULL) {
            (*digit) = raw_digit_value;
        }
        return 1;
    }
    return 0;
}

int parse_int(const char* string, int* is_int) {
    int number_length = strlength(string);
    int int_sign = 1;
    int index = 0;
    if (string[0] == '-') {
        index++;
        int_sign = -1;
        number_length--;
    } else if(string[0] == '+') {
        index++;
        int_sign = 1;
        number_length--;
    }

    (*is_int) = 0;

    if (number_length > 10) { // "2147483647"
        return 0;
    }

    char* number_validator_buffer = calloc(number_length, sizeof(char));
    int final_number = 0;
    int number_position = number_length;

    while (string[index]) {
        const char current_digit = string[index];
        int digit = 0;
        if (!is_digit(current_digit, &digit)) {
            free(number_validator_buffer);
            return 0;
        }
        int exp = 1;
        for (int i = 0 ; i < number_position - 1 ; i++)
            exp *= 10;
        final_number += digit * exp;
        number_validator_buffer[number_length - number_position] = digit;
        number_position--;
        index++;
    }
    if (number_length == 10) {
        int max_signed_int_value[] = {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
        int is_last_equals = 0; // Check if the int value is in the bound of a real int value
        for (int i = 0; i < 10; i++) {
            if (number_validator_buffer[i] == max_signed_int_value[i]) {
                if (i == 0) {
                    is_last_equals = 1;
                }
            } else if (number_validator_buffer[i] < max_signed_int_value[i]) {
                is_last_equals = 0;
            } else if (number_validator_buffer[i] > max_signed_int_value[i]) {
                if (is_last_equals || i == 0) {
                    free(number_validator_buffer);
                    return 0;
                }
            }
        }
    }

    (*is_int) = 1;
    free(number_validator_buffer);
    return final_number * int_sign;
}

double drand(double start, double end) {
    int current_value = rand();
    double factor = (double)current_value / (double)RAND_MAX;
    return (factor * (end - start)) + start;
}

int irand(int start, int end) {
    return (int) drand(start, end);
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
