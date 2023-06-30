#include <random>
#include <ctime>
#include "handle_map.h"
#include "handle_UI.h"
#include "movement.h"

int main() {
    srand(time(NULL));

    init_UI();

    game_object player = game_object();
    player.display_char = '@';
    player.name = "doyle";

    stats* player_stats = new stats(100, 100, 100, 100, 15, 1);
    add_component(player, *player_stats);

    init_map(player);

    while (true) {
        draw_level(player.x, player.y, '#');
        bool quit_game = false;
        while (true) {
            int input_key = getch();
            bool finished_turn = true;
            switch (input_key) {
                case KEY_UP:
                    events::move_direction(player,directions::d_up);
                    break;
                case KEY_DOWN:
                    events::move_direction(player,directions::d_down);
                    break;
                case KEY_LEFT:
                    events::move_direction(player,directions::d_left);
                    break;
                case KEY_RIGHT:
                    events::move_direction(player,directions::d_right);
                    break;
                case 's':
                    events::start_sprinting(player);
                    finished_turn = false;
                    break;
                case 'S':
                    events::stop_sprinting(player);
                    finished_turn = false;
                    break;
                case 'Q':
                    quit_game = true;
                    break;
                default:
                    finished_turn = false;
            }
            if (finished_turn) break;
        } // end of input loop
        if (quit_game) {
            break;
        }
    } // end of game loop

    cleanup_map_data();
    end_UI();
}