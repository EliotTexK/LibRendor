#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <vector>
#include "utility.h"

using namespace std;

const char COMPONENTS_COUNT = 4;

// ALWAYS DYNAMICALLY ALLOCATE COMPONENTS!!! game objects\
// will deallocate their components when destructed
struct component {
    // for processing AI/player choice: figure out what actions
    // (functions) can be performed because of this component
    virtual vector<int> get_actions() = 0;
    char id;
    component(char _id) : id(_id) {};
    virtual ~component() {};
};

struct stats : public component {
    stats(int _max_hp, int _hp, int _stamina, int _max_stamina,
        int _strength, int _move_speed) : component(0), 
        max_hp(_max_hp), hp(_hp), stamina(_stamina),
        max_stamina(_max_stamina), strength(_strength),
        move_speed(_move_speed), is_sprinting(0) {};
    vector<int> get_actions();
    int max_hp;
    int hp;
    int stamina;
    int max_stamina;
    int strength;
    int move_speed;
    bool is_sprinting;
};

struct game_object {
    int x;
    int y;
    char display_char;
    string name;
    int facing_x;
    int facing_y;
    component* components[COMPONENTS_COUNT];
    game_object();
    ~game_object();
};

char add_component(game_object& go, component& cp);

component* remove_component(game_object& go, char id);

#endif