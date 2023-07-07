#ifndef HANDLE_MAP_H
#define HANDLE_MAP_H

#include <set>
#include <stdexcept>
#include "cave_gen.h"
#include "utility.h"
#include "game_obj.h"

struct timeline;

// TIMELINE MUST BE INITIALIZED FIRST

// stores objects on the map for access in the game
// uses an array of game_obj_rc* while incrementing and decrementing
// the reference count when necessary
struct handle_map {
    // you can access this, but it won't automatically increment
    // and decrement reference counts, so not advised for game logic
    static game_obj_rc* objs_map[LEVEL_WIDTH][LEVEL_HEIGHT];
    static void init(game_obj& player);
    static void place_game_obj(game_obj& obj); // sets the object's internal coordinates
    static void move_game_obj(game_obj& obj, const int& new_x, const int& new_y);
    static void rm_game_obj(int x, int y);
    static game_obj get_game_obj(int x, int y);
    static void rm_all_objs();
};

#endif