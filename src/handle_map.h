#ifndef HANDLE_MAP_H
#define HANDLE_MAP_H

#include <set>
#include <stdexcept>
#include "cave_gen.h"
#include "utility.h"
#include "game_object.h"

using namespace std;

inline char level_terrain[LEVEL_WIDTH][LEVEL_HEIGHT];
inline game_object* objects_map[LEVEL_WIDTH][LEVEL_HEIGHT];
inline set<game_object*> monsters;

void init_map(game_object& player);

void place_game_object(game_object& go, int x, int y);

void move_game_object(game_object& go, int new_x, int new_y);

void cleanup_map_data();

#endif