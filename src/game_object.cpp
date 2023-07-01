#include "game_object.h"

game_object::game_object() {
    for (int i = 0; i < COMPONENTS_COUNT; i++) {
        components[i] = nullptr;
    }
}

game_object::~game_object() {
    for (int i = 0; i < COMPONENTS_COUNT; i++) {
        if (components[i]) {
            delete components[i];
        }
    }
}

char add_component(game_object& go, component& cp) {
    if (cp.id < 0 || cp.id >= COMPONENTS_COUNT) return 1;
    go.components[cp.id] = &cp;
    return 0;
}

component* remove_component(game_object& go, char id) {
    if (id < 0 || id >= COMPONENTS_COUNT) return nullptr;
    if (!go.components[id]) return nullptr;
    component* result = go.components[id];
    go.components[id] = nullptr;
    return result;
}