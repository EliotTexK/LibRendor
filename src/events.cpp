#include "events.h"

void events::init::execute() {
    components::stamina* stam =
    obj.get_component<components::stamina>(comp_ids::c_stamina);

    components::player* is_player =
    obj.get_component<components::player>(comp_ids::c_player);
    
    components::enemy_AI* is_enemy =
    obj.get_component<components::enemy_AI>(comp_ids::c_enemy_AI);

    if (stam) timeline::insert_event(new events::restore_stamina(obj));
    if (is_player || is_enemy) {
        timeline::insert_event(new events::update(obj,0));
    }
}

events::move::move(game_obj obj, int x, int y)
    : obj(obj), x(x), y(y) {
    components::stamina* stam =
    obj.get_component<components::stamina>(comp_ids::c_stamina);
    // by default, it takes objects BASE_MOVE_TIME time units to move
    time = BASE_MOVE_TIME;
    if (!stam) return;
    time /= stam->move_speed;
    if (stam->is_sprinting) {
        if (stam->cur_stamina > 0) {
            stam->cur_stamina -= 15;
            time /= 2;
        } else {
            stam->is_sprinting = false;
            print_message(obj.get_name() +
                " stops sprinting because they ran out of stamina"
            );
        }
    }
}

void events::move::execute() {
    handle_map::move_game_obj(obj, x, y);
}

void events::begin_sprinting::execute() {
    components::stamina* stam =
    obj.get_component<components::stamina>(comp_ids::c_stamina);
    if (!stam) return;
    if (!stam->is_sprinting) {
        if (stam->cur_stamina > stam->max_stamina/2) {
            stam->is_sprinting = true;
            print_message(obj.get_name() + " begins sprinting");
        } else {
            print_message(obj.get_name() + " is too tired to sprint!");
        }
    }
}

void events::stop_sprinting::execute() {
    components::stamina* stam =
    obj.get_component<components::stamina>(comp_ids::c_stamina);
    if (!stam) return;
    if (stam->is_sprinting) {
        stam->is_sprinting = false;
        print_message(obj.get_name() + " stops sprinting");
    }
}

void events::update::execute() {
    if (obj.get_component<components::player>(c_player)) update_player();
    else if (obj.get_component<components::player>(c_enemy_AI)) update_enemy_AI();
}

inline void events::update::update_player() {
    event* chosen;
    draw_level(obj.get_x(),obj.get_y(),'X');
    bool valid = false;
    while (!valid) {
        valid = true;
        int input = getch();
        switch (input) {
            case KEY_UP:
                chosen = new events::move(obj,obj.get_x(),obj.get_y()-1);
                break;
            case KEY_DOWN:
                chosen = new events::move(obj,obj.get_x(),obj.get_y()+1);
                break;
            case KEY_LEFT:
                chosen = new events::move(obj,obj.get_x()-1,obj.get_y());
                break;
            case KEY_RIGHT:
                chosen = new events::move(obj,obj.get_x()+1,obj.get_y());
                break;
            case 's':
                chosen = new events::begin_sprinting(obj);
                break;
            case 'S':
                chosen = new events::stop_sprinting(obj);
                break;
            case 'Q':
                chosen = new event(); // NOP
                timeline::quit_game = true;
                break;
            default:
                valid = false;
        }
    }
    timeline::insert_event(chosen);
    timeline::insert_event(new update(obj,chosen->time));
}

inline void events::update::update_enemy_AI() {

}

void events::restore_stamina::execute() {
    components::stamina* stam = 
    obj.get_component<components::stamina>(comp_ids::c_stamina);
    // recharge stamina until it reaches max
    if (stam->cur_stamina + stam->recharge_speed > stam->max_stamina) {
        stam->cur_stamina = stam->max_stamina;
    } else {
        stam->cur_stamina += stam->recharge_speed;
    }
    timeline::insert_event(new events::restore_stamina(obj));
}