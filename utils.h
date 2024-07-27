#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <time.h>
#include <stdio.h>

#include "string_utils.h"

void sleep_ms(long milliseconds);

int get_terminal_width();
int get_terminal_height();
void move_cursor_to_row(int row);

#endif //UTILS_H
