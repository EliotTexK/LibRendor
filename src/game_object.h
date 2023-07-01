#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <vector>
#include "utility.h"
#include "components.h"

struct game_object {
    int x;
    int y;
    char display_char;
    std::string name;
    int facing_x;
    int facing_y;
    component* components[COMPONENTS_COUNT];
    game_object();
    ~game_object();
};

char add_component(game_object& go, component& cp);

component* remove_component(game_object& go, char id);

#endif