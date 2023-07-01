#include <random>
#include <ctime>
#include "handle_map.h"
#include "handle_UI.h"
#include "events.h"

// return true -> quit game
bool player_turn(game_object& player) {
    while (true) {
        int input_key = getch();
        bool finished_turn = true;
        switch (input_key) {
            case KEY_UP:
                finished_turn =
                events::try_move_direction(player,directions::N);
                break;
            case KEY_DOWN:
                finished_turn =
                events::try_move_direction(player,directions::S);
                break;
            case KEY_LEFT:
                finished_turn =
                events::try_move_direction(player,directions::W);
                break;
            case KEY_RIGHT:
                finished_turn =
                events::try_move_direction(player,directions::E);
                break;
            case 's':
                finished_turn =
                events::start_sprinting(player);
                break;
            case 'S':
                finished_turn =
                events::stop_sprinting(player);
                break;
            case 'Q':
                return true;
                break;
            default:
                finished_turn = false;
        }
        if (finished_turn) break;
    } // end of input loop
    return false;
}

int main() {
    srand(time(NULL));

    init_UI();

    game_object player = game_object();
    player.display_char = '@';
    player.name = "doyle";

    stamina* player_stats = new stamina(100,1);
    add_component(player, *player_stats);
    combat* player_combat = new combat(100,12);
    add_component(player, *player_combat);

    init_map(player);

    while (true) {
        draw_level(player.x, player.y, '#');
        if (player_turn(player)) break;
        for (game_object* mon : monsters) {
            events::follow_object(*mon,player);
        }
    }

    cleanup_map_data();
    end_UI();
}