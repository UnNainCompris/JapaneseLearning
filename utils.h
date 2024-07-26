#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <time.h>
#include <stdio.h>

int equals_string(const char* first, const char* second, int check_length);
int start_with(char* string, char* model, int model_length);
int slength(const char* string);
char* replace_last(const char* string, int string_length,const char* to_replace, int to_replace_length,const char* replacement, int replacement_length);
char* replace(const char* string, int string_length,const char* to_replace, int to_replace_length,const char* replacement, int replacement_length);
char* repeat(int times, char* to_repeat);

void sleep_ms(long milliseconds);

int get_terminal_width();
int get_terminal_height();
void move_cursor_to_row(int row);

#endif //UTILS_H
