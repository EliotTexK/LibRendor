#include "movement.h"

bool events::check_if_can_move(int new_x, int new_y) {
    return (is_in_level_bounds(new_x, new_y) &&
        level_terrain[new_x][new_y] == 0 &&
        objects_map[new_x][new_y] == nullptr);
}

bool events::move_direction(game_object& obj, char direction) {
    int effective_movespeed = 1;
    stats* _stats = (stats*) obj.components[comp_ids::c_stats];
    if (_stats) {
        effective_movespeed = _stats->move_speed;
        if (_stats->is_sprinting) {
            if (_stats->stamina > 0) {
                _stats->stamina -= 4;
                effective_movespeed *= 2;
            } else {
                _stats->is_sprinting = false;
                print_message(obj.name +
                " stops sprinting because they're out of stamina");
            }
        }
    }
    bool valid_move = true;
    int new_x = obj.x;
    int new_y = obj.y;
    for (int i = 0; i < effective_movespeed; i++) {
        new_x += direction_components[direction][0];
        new_y += direction_components[direction][1];
        if (!check_if_can_move(new_x, new_y)) {
            valid_move = false;
            break;
        }
    }
    if (valid_move) {
        move_game_object(
            obj,
            new_x,
            new_y
        );
        return true;
    } else {
        print_message(obj.name + " can't move that way");
        return false;
    }
}

void events::start_sprinting(game_object& obj) {
    stats* _stats = (stats*) obj.components[comp_ids::c_stats];
    if (_stats) {
        _stats->is_sprinting = _stats->stamina > 0;
    }
    print_message(obj.name + " starts sprinting");
}

void events::stop_sprinting(game_object& obj) {
    stats* _stats = (stats*) obj.components[comp_ids::c_stats];
    if (_stats) {
        _stats->is_sprinting = false;
    }
    print_message(obj.name + " stops sprinting");
}