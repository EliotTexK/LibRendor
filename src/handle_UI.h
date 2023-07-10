#ifndef HANDLE_UI_H
#define HANDLE_UI_H

#include "game_obj.h"
#include <string>
#include <ncurses.h>

struct handle_map;

struct handle_UI {
    static WINDOW* message_log;
    static char draw_buffer[VIEW_WIDTH][VIEW_HEIGHT];
    static void init_UI();
    static void print_message(std::string message);
    static void draw_level(int center_x, int center_y, char outside_tile);
    static void end_UI();
};

#endif