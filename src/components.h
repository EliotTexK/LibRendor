#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <string>
#include "utility.h"

const char COMPONENTS_COUNT = 20;

// these should go in the same order as the ids
enum comp_ids {
    c_player,
    c_terrain,
    c_enemy_AI,
    c_combat,
    c_stamina
};

enum action_ids {

};

// ALWAYS HEAP ALLOCATE COMPONENTS!!! game objects
// will deallocate their components when destructed
struct component {
    // for processing AI/player choice: figure out what actions
    // (functions) can be performed because of this component
    virtual std::vector<int> get_actions() = 0;
    char id;
    component(char _id) : id(_id) {};
    virtual ~component() {};
};

namespace components {

// signifies player control of an object
struct player : public component {
    player() : component(0) {}
    std::vector<int> get_actions() {return {};}
};

// signifies that an object is part of level terrain
struct terrain : public component {
    terrain() : component(1) {};
    std::vector<int> get_actions() {return {};}
};

// update events should treat the object as an enemy AI
struct enemy_AI : public component {
    enemy_AI() : component(2) {};
    std::vector<int> get_actions() {return {};}
};

// has combat abilities
struct combat : public component {
    combat(int _max_health, int _attack_power) : component(3),
        cur_health(_max_health), max_health(_max_health),
        attack_power(_attack_power) {};
        std::vector<int> get_actions() {return {};}
        int cur_health;
        int max_health;
        int attack_power;
};

// has stamina, which will hinder abilities when it runs out
struct stamina : public component {
    stamina(int _max_stamina, int _recharge_speed, float _move_speed)
        : component(4), cur_stamina(_max_stamina),
        recharge_speed(_recharge_speed), max_stamina(_max_stamina),
        move_speed(_move_speed), is_sprinting(0) {};
    std::vector<int> get_actions() {return {};}
    int cur_stamina;
    int max_stamina;
    int recharge_speed;
    // inversely proportional to the time it takes to move
    float move_speed;
    bool is_sprinting;
};

}

#endif