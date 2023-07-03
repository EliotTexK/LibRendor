#ifndef CAVE_GEN_H
#define CAVE_GEN_H

#include <random>
#include <queue>
#include <array>
#include <vector>
#include <algorithm>
#include "utility.h"

// returns a list of room border cells
std::queue<std::array<int,2>> fill_room_get_borders(char (&rooms_mask)[LEVEL_WIDTH][LEVEL_HEIGHT],
    char (&level_terrain)[LEVEL_WIDTH][LEVEL_HEIGHT], int start_x, int start_y, int room_index);

void fill_terrain_with_noise(char (&level_terrain)[LEVEL_WIDTH][LEVEL_HEIGHT],
    char wall_tile, int percent);

void marching_squares(char (&level_terrain)[LEVEL_WIDTH][LEVEL_HEIGHT],
    char wall_tile, int level_smoothing_iterations, char (&cell_automata_rule)[9]);

void connect_rooms(char (&level_terrain)[LEVEL_WIDTH][LEVEL_HEIGHT]);

std::vector<std::array<int,2>> random_item_placement(char (&level_terrain)[LEVEL_WIDTH][LEVEL_HEIGHT],
    char density_percent);

#endif