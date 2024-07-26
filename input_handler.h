#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ENTER_KEYCODE 13
#define BACKSPACE_KEYCODE 8

char* get_buffer();
int get_buffer_size();
int get_buffer_active_length();

int is_empty();

void print_buffer();

void load_buffer(int buffer_size);

void pop_buffer();
void clear_buffer();
void append_to_buffer(const char* char_to_append);

char ask_input();

void validate_buffer();

#endif //INPUT_HANDLER_H