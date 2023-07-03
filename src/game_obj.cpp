#include "game_obj.h"

game_obj_data::game_obj_data() {
    for (int i = 0; i < COMPONENTS_COUNT; i++) {
        components[i] = nullptr;
    }
    display_char = 0;
}

game_obj_data::~game_obj_data() {
    for (int i = 0; i < COMPONENTS_COUNT; i++) {
        if (components[i]) {
            delete components[i];
        }
    }
}

game_obj_rc::game_obj_rc() : refs(1) {
    data = new game_obj_data();
}

game_obj_rc::game_obj_rc(int display) : refs(1) {
    data = new game_obj_data();
    data->display_char = display;
}

void game_obj_rc::dec_refs() {
    refs--;
    if (refs <= 0) delete this;
}

void game_obj_rc::inc_refs() {
    refs++;
}

game_obj_rc::~game_obj_rc() {
    if (data) {
        delete data;
    }
}

game_obj_rc* game_obj::get_shared_rc() {
    shared_rc->inc_refs();
    return shared_rc;
}

void game_obj::add_component(component* cp) {
    if (shared_rc->data) {
        if (!shared_rc->data->components[cp->id]) {
            shared_rc->data->components[cp->id] = cp;
        }
    }
}

void game_obj::rm_component(int id) {
    if (shared_rc->data) {
        component* to_delete =
            shared_rc->data->components[id];
        if (to_delete) delete to_delete;
    }
}

void game_obj::set_display_char(int ch) {
    if (shared_rc->data) {
        shared_rc->data->display_char = ch;
    }
}

int game_obj::get_display_char() {
    if (shared_rc->data) {
        return shared_rc->data->display_char;
    } else {
        return -1;
    }
}

void game_obj::set_x(int x) {
    if (shared_rc->data) {
        shared_rc->data->x = x;
    }
}

void game_obj::set_y(int y) {
    if (shared_rc->data) {
        shared_rc->data->y = y;
    }
}

int game_obj::get_x() {
    if (shared_rc->data) {
        return shared_rc->data->x;
    } else return -1;
}

int game_obj::get_y() {
    if (shared_rc->data) {
        return shared_rc->data->y;
    } else return -1;
}

void game_obj::set_name(std::string name) {
    if (shared_rc->data) {
        shared_rc->data->name = name;
    }
}

std::string game_obj::get_name() {
    if (shared_rc->data) {
        return shared_rc->data->name;
    } else return "ERROR";
}

bool game_obj::exists() {
    return shared_rc->data;
}

void game_obj::rm_from_game() {
    delete shared_rc->data;
    shared_rc->data = nullptr;
}

game_obj& game_obj::operator= (const game_obj& obj) {
    // decrement refs of old ref counter
    if (shared_rc != obj.shared_rc) {
        shared_rc->dec_refs();
    }
    // they both get the same pointer
    shared_rc = obj.shared_rc;
    // and the reference count gets incremented
    shared_rc->inc_refs();
    return *this;
}

game_obj::game_obj(const game_obj& obj) {
    // copy the pointer
    shared_rc = obj.shared_rc;
    // and the reference count gets incremented
    shared_rc->inc_refs();
}

game_obj::~game_obj() {
    shared_rc->dec_refs();
}

game_obj::game_obj(int display) {
    // refs starts at 1 with default constructor
    shared_rc = new game_obj_rc();
    shared_rc->data->display_char = display;
}

game_obj::game_obj(int display, int x, int y) {
    // refs starts at 1 with default constructor
    shared_rc = new game_obj_rc();
    shared_rc->data->display_char = display;
    shared_rc->data->x = x;
    shared_rc->data->y = y;    
}

game_obj::game_obj(game_obj_rc*& rc) {
    shared_rc = rc;
    shared_rc->inc_refs();
}