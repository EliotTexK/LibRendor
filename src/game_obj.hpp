#include "game_obj.h"

template <typename T>
T* game_obj::get_component(int id) {
    if (shared_rc->data) {
        return (T*) shared_rc->data->components[id];
    } else return nullptr;
}