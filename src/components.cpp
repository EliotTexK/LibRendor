#include "components.h"

std::vector<int> stamina::get_actions() {
    return {
        action_ids::a_move_direction,
        action_ids::a_start_running,
        action_ids::a_stop_running
    };
}

std::vector<int> combat::get_actions() {
    return {
        action_ids::a_attack_melee
    };
}