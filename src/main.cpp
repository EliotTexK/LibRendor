#include <random>
#include <ctime>
#include <ncurses.h>
#include <stdexcept>
#include "utility.h"
#include "game_object.h"
#include "cave_gen.h"

WINDOW* message_log;

char level_terrain[LEVEL_WIDTH][LEVEL_HEIGHT];
game_object* objects_map[LEVEL_WIDTH][LEVEL_HEIGHT];

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

char place_game_object(game_object& go) {
    if (!is_in_level_bounds(go.x,go.y)) {
        return 1;
    }
    if (objects_map[go.x][go.y] != nullptr) {
        return 2;
    }
    if (level_terrain[go.x][go.y] != 0) {
        return 3;
    }
    objects_map[go.x][go.y] = &go;
    return 0;
}

char move_game_object(game_object& go, int new_x, int new_y) {
    if (!is_in_level_bounds(new_x,new_y)) {
        print_message(go.name + " can't go that way");
        return 1;
    }
    if (objects_map[new_x][new_y] != nullptr) {
        game_object* other = objects_map[new_x][new_y];
        print_message(go.name +
        " can't go that way: the path is blocked by " + other->name);
        return 2;
    }
    if (level_terrain[new_x][new_y] != 0) {
        game_object* other = objects_map[new_x][new_y];
        print_message(go.name +
        " can't go that way: the path is blocked");
        return 2;
    }
    objects_map[go.x][go.y] = nullptr;
    objects_map[new_x][new_y] = &go;
    go.x = new_x;
    go.y = new_y;
    return 0;
}

int main() {
    srand(time(NULL));
    initscr();              // start ncurses
    start_color();          // start color mode
    curs_set(0);            // don't display the cursor
    noecho();               // don't echo input characters to the terminal
    cbreak();               // don't buffer characters before carriage return
    keypad(stdscr,true);    // you must add this line or arrow keys won't work
	
    message_log = newwin(6, VIEW_WIDTH, VIEW_HEIGHT, 0);
    scrollok(message_log, true);  // enables terminal-esque scrolling text

    for (int x = 0; x < LEVEL_WIDTH; x++) {
        for (int y = 0; y < LEVEL_HEIGHT; y++) {
            objects_map[x][y] = nullptr;
        }
    }

    fill_terrain_with_noise(level_terrain,'#',30);
    char mask_1[9] = {1,1,2,2,2,1,1,1,1};
    char mask_2[9] = {0,0,0,2,2,1,1,1,1};
    char mask_3[9] = {0,0,0,0,2,2,2,1,1};
    marching_squares(level_terrain, '#', 1, mask_1);
    marching_squares(level_terrain, '#', 2, mask_2);
    connect_rooms(level_terrain);
    marching_squares(level_terrain, '#', 4, mask_3);

    vector<array<int,2>> spawnpoints = random_item_placement(level_terrain, 2);

    // player goes at first spawnpoint
    game_object player = {
        spawnpoints[0][0],
        spawnpoints[0][1],
        '@',
        100,
        100,
        "you"
    };

    place_game_object(player);

    while (true) {
        draw_level(player.x, player.y, '#');
        bool quit_game = false;
        bool valid_action = false;
        while (!valid_action) {
            int input_key = getch();
            switch (input_key) {
                case KEY_UP:
                    valid_action = !move_game_object(player,player.x,player.y-1);
                    break;
                case KEY_DOWN:
                    valid_action = !move_game_object(player,player.x,player.y+1);
                    break;
                case KEY_LEFT:
                    valid_action = !move_game_object(player,player.x-1,player.y);
                    break;
                case KEY_RIGHT:
                    valid_action = !move_game_object(player,player.x+1,player.y);
                    break;
                case 'Q':
                    quit_game = true;
                    break;
            }
            if (quit_game) {
                break;
            }
        }
    }

    endwin();
}