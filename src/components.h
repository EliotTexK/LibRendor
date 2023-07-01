#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <string>
#include "utility.h"

const char COMPONENTS_COUNT = 4;

enum comp_ids {
    c_stamina,
    c_combat
};

enum action_ids {
    a_move_direction,
    a_start_running,
    a_stop_running,
    a_attack_melee
};

// ALWAYS DYNAMICALLY ALLOCATE COMPONENTS!!! game objects
// will deallocate their components when destructed
struct component {
    // for processing AI/player choice: figure out what actions
    // (functions) can be performed because of this component
    virtual std::vector<int> get_actions() = 0;
    char id;
    component(char _id) : id(_id) {};
    virtual ~component() {};
};

struct stamina : public component {
    stamina(int _max_stamina, int _move_speed) : component(0),
        cur_stamina(_max_stamina), max_stamina(_max_stamina),
        move_speed(_move_speed), is_sprinting(0) {};
    std::vector<int> get_actions();
    int cur_stamina;
    int max_stamina;
    int move_speed;
    bool is_sprinting;
};

struct combat : public component {
    combat(int _max_health, int _attack_power) : component(1),
        cur_health(_max_health), max_health(_max_health),
        attack_power(_attack_power) {};
        std::vector<int> get_actions();
        int cur_health;
        int max_health;
        int attack_power;
};

struct terrain : public component {
    terrain() : component(2) {};
    std::vector<int> get_actions() {return {};}
};

#endif