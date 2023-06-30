#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "handle_map.h"
#include "handle_UI.h"
#include <algorithm>

namespace events
{

bool check_if_can_move(int x, int y);

// return false if can't move
// TODO: get rid of moving multiple tiles at once in
// favor of using turn interleaving to deal with movespeed
bool move_direction(game_object& obj, char direction);

void start_sprinting(game_object& obj);

void stop_sprinting(game_object& obj);

}

#endif