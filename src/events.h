#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "handle_map.h"
#include "handle_UI.h"
#include <algorithm>

bool check_if_can_move(int x, int y);

namespace events
{

// tries to move multiple tiles if movespeed > 1
// return false if can't move
// TODO: get rid of moving multiple tiles at once in
// favor of using turn interleaving to deal with movespeed
bool try_move_direction(game_object& obj, char direction);

bool follow_object(game_object& obj, game_object& target);

bool start_sprinting(game_object& obj);

bool stop_sprinting(game_object& obj);

}

#endif