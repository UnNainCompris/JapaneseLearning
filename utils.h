#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <time.h>
#include <stdio.h>

#include "string_utils.h"

void sleep_ms(long milliseconds);

int is_digit(char chr, int* digit);
int parse_int(const char* string, int* is_int);

double drand(double start, double end);
int irand(int start, int end);

int get_terminal_width();
int get_terminal_height();
void move_cursor_to_row(int row);

#endif //UTILS_H
