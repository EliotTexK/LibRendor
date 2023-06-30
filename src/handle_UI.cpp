#include "handle_UI.h"

void init_UI() {
    initscr();              // start ncurses
    start_color();          // start color mode
    curs_set(0);            // don't display the cursor
    noecho();               // don't echo input characters to the terminal
    cbreak();               // don't buffer characters before carriage return
    keypad(stdscr,true);    // you must add this line or arrow keys won't work
	
    message_log = newwin(6, VIEW_WIDTH, VIEW_HEIGHT, 0);
    scrollok(message_log, true);  // enables terminal-esque scrolling text
}

void print_message(string message) {
    wprintw(message_log, message.c_str());
    wprintw(message_log,"\n");
    wrefresh(message_log);
}

void draw_level(int center_x, int center_y, char outside_tile) {
    for (int x = 0; x < VIEW_WIDTH; x++) {
        for (int y = 0; y < VIEW_HEIGHT; y++) {
            int draw_x = center_x - VIEW_WIDTH/2 + x;
            int draw_y = center_y - VIEW_HEIGHT/2 + y;
            if (is_in_level_bounds(draw_x, draw_y)) {
                if (objects_map[draw_x][draw_y]) {
                    mvaddch(y,x,objects_map[draw_x][draw_y]->display_char);
                } else if (level_terrain[draw_x][draw_y]) {
                    mvaddch(y,x,level_terrain[draw_x][draw_y]);
                } else {
                    mvaddch(y,x,' ');
                }
            } else {
                mvaddch(y,x,outside_tile);
            }
        }
    }
}

void end_UI() {
    endwin();
}