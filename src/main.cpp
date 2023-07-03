#include <random>
#include <ctime>
#include "handle_map.h"
#include "handle_UI.h"
#include "timeline.h"
#include "events.h"

int main() {
    srand(time(NULL));

    timeline::init();
    game_obj player = game_obj('@', LEVEL_WIDTH/2, LEVEL_HEIGHT/2);
    player.add_component(new components::player());
    player.add_component(new components::combat(100,12));
    player.add_component(new components::stamina(100, 5, 1));
    handle_map::init(player);
    init_UI();

    while (!timeline::quit_game) {
        timeline::execute_top();
    }

    handle_map::rm_all_objs();
    timeline::end();
    end_UI();
}