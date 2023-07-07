#include "handle_UI.h"
#include "handle_map.h"

WINDOW* handle_UI::message_log;

void handle_UI::init_UI() {
    initscr();              // start ncurses
    start_color();          // start color mode
    curs_set(0);            // don't display the cursor
    noecho();               // don't echo input characters to the terminal
    cbreak();               // don't buffer characters before carriage return
    keypad(stdscr,true);    // you must add this line or arrow keys won't work
	
    message_log = newwin(6, VIEW_WIDTH, VIEW_HEIGHT, 0);
    scrollok(message_log, true);  // enables terminal-esque scrolling text
}

void handle_UI::print_message(std::string message) {
    wprintw(message_log, "%s", message.c_str());
    wprintw(message_log,"\n");
    wrefresh(message_log);
}

void handle_UI::draw_level(int center_x, int center_y, char outside_tile) {
    for (int x = 0; x < VIEW_WIDTH; x++) {
        for (int y = 0; y < VIEW_HEIGHT; y++) {
            int draw_x = center_x - VIEW_WIDTH/2 + x;
            int draw_y = center_y - VIEW_HEIGHT/2 + y;
            if (is_in_level_bounds(draw_x, draw_y)) {
                // if everything is working, obj should point to a valid game_obj_data,
                // or nullptr if it has been recently removed from the game
                game_obj_rc* obj = handle_map::objs_map[draw_x][draw_y];
                if (obj) {
                    if (obj->data) {
                        mvaddch(y,x,obj->data->display_char);
                    }
                } else {
                    mvaddch(y,x,' ');
                }
            } else {
                mvaddch(y,x,outside_tile);
            }
        }
    }
}

void handle_UI::end_UI() {
    curs_set(1);
    echo();
    nocbreak();
    endwin();
}