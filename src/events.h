#ifndef EVENTS_H
#define EVENTS_H

#include "timeline.h"
#include "utility.h"
#include "handle_map.h"
#include <algorithm>
#include <ncurses.h>
#include <string>

// forward declarations necessary for obvious reasons
void draw_level(int center_x, int center_y, char outside_tile);
void print_message(std::string message);
struct handle_map;

namespace events
{

const int BASE_MOVE_TIME = 20;

// call this when objects are placed into the level
// starts recurring events (stat regen, AI updates, etc.)
struct init : public event {
    game_obj obj;
    init(game_obj obj) : event(0), obj(obj) {}
    void execute();
};

// decreases stamina by 15 every turn
struct move : public event {
    game_obj obj;
    int x;
    int y;
    move(game_obj obj, int x, int y);
    void execute();
};

// can only begin sprinting if stamina > 50% of max
struct begin_sprinting : public event {
    game_obj obj;
    begin_sprinting(game_obj obj) : event(2), obj(obj) {}
    void execute();
};

struct stop_sprinting : public event {
    game_obj obj;
    stop_sprinting(game_obj obj) : event(2), obj(obj) {}
    void execute();
};

// update AI, or it's the player's turn
struct update : public event {
    game_obj obj;
    update(game_obj obj, unsigned int time)
        : event(time), obj(obj) {}
    // if an object has both player AI and enemy AI components,
    // only player AI will be processed
    void execute();
    void update_player();
    void update_enemy_AI();
};

// Restored every 5 time units.
// Amount determined by components::stamina::recharge_speed
struct restore_stamina : public event {
    game_obj obj;
    restore_stamina(game_obj obj)
        : event(5), obj(obj) {}
    void execute();
};

}

#endif