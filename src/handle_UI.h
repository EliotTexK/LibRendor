#ifndef HANDLE_UI_H
#define HANDLE_UI_H

#include "handle_map.h"
#include <ncurses.h>

inline WINDOW* message_log;

void init_UI();

void print_message(string message);

void draw_level(int center_x, int center_y, char outside_tile);

void end_UI();

#endif