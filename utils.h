#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <time.h>
#include <stdio.h>

int equals_string(const char* first, const char* second, int check_length);
char* repeat(int times, char* to_repeat);

void sleep_ms(long milliseconds);

int get_terminal_width();
int get_terminal_height();
void move_cursor_to_row(int row);

#endif //UTILS_H
