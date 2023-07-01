#include "events.h"

bool check_if_can_move(int new_x, int new_y) {
    return (is_in_level_bounds(new_x, new_y) &&
        objects_map[new_x][new_y] == nullptr);
}

bool events::try_move_direction(game_object& obj, char direction) {
    int effective_movespeed = 1;
    stamina* _stamina = (stamina*) obj.components[comp_ids::c_stamina];
    if (_stamina) {
        effective_movespeed = _stamina->move_speed;
        if (_stamina->is_sprinting) {
            if (_stamina->cur_stamina > 0) {
                _stamina->cur_stamina -= 4;
                effective_movespeed *= 2;
            } else {
                _stamina->is_sprinting = false;
                print_message(obj.name +
                " stops sprinting because they're out of stamina");
            }
        }
    }
    bool valid_move = true;
    int new_x = obj.x;
    int new_y = obj.y;
    for (int i = 0; i < effective_movespeed; i++) {
        new_x += direction_to_components[direction][0];
        new_y += direction_to_components[direction][1];
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

bool events::follow_object(game_object& obj, game_object& target) {
    int x_diff = target.x - obj.x;
    int y_diff = target.y - obj.y;
    int x_move = (x_diff == 0)? 0 : x_diff/abs(x_diff);
    int y_move = (y_diff == 0)? 0 : y_diff/abs(y_diff);
    int dir = components_to_direction(x_move,y_move);
    return try_move_direction(obj,dir);
}

bool events::start_sprinting(game_object& obj) {
    stamina* _stamina = (stamina*) obj.components[comp_ids::c_stamina];
    if (_stamina) {
        _stamina->is_sprinting = _stamina->cur_stamina > 0;
    }
    print_message(obj.name + " starts sprinting");
    return false;
}

bool events::stop_sprinting(game_object& obj) {
    stamina* _stamina = (stamina*) obj.components[comp_ids::c_stamina];
    if (_stamina) {
        _stamina->is_sprinting = false;
    }
    print_message(obj.name + " stops sprinting");
    return false;
}