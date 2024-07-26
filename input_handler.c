#include "input_handler.h"

char* input_buffer;
int active_length = 0;
int buffer_size;

char* get_buffer() {
    return input_buffer;
}

int get_buffer_active_length() {
    return active_length;
}

int get_buffer_size() {
    return buffer_size;
}

int is_empty() {
    return active_length > 0;
}

void print_buffer() {
    printf("\r%s\033[K", input_buffer);
}

void load_buffer(int new_buffer_size) {
    if (input_buffer != 0) {
        printf("Free buffer");
        free(input_buffer);
    }
    buffer_size = new_buffer_size;

    input_buffer = calloc(buffer_size, sizeof(char));
}

void pop_buffer() {
    if (active_length > 0) {
        active_length--;
    }

    input_buffer[active_length] = *"";
}

void clear_buffer() {
    while (is_empty()) {
        pop_buffer();
    }
}

void append_to_buffer(const char* char_to_append) {
    if (active_length >= buffer_size) {
        active_length = buffer_size - 1;
    }

    input_buffer[active_length] = *char_to_append;
    active_length++;
}

char ask_input() {
    return getch();
}

void validate_buffer() {
    if (get_buffer() == 0) {
        printf("The buffer isn't valid !\n");
        system("pause");
        exit(1);
    }
}