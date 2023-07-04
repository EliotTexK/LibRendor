#include <random>
#include <ctime>
#include <fstream>
#include "handle_map.h"
#include "handle_UI.h"
#include "timeline.h"
#include "events.h"

int main(int argc, char *argv[]) {
    int seed;
    if (argc >= 2) {
        // read seed from file if provided as cli arg
        std::ifstream seed_file;
        seed_file.open("seed.txt", std::ios::in);
        std::string line;
        std::getline(seed_file, line);
        seed = std::stoi(line);
    } else {
        // if no args are provided, generate a random one
        // and output it to a file
        seed = time(NULL);
        std::ofstream seed_file;
        seed_file.open("seed.txt", std::ios::out);
        seed_file << seed << std::endl;
        seed_file.close();
    }
    srand(seed);

    timeline::init();
    game_obj player = game_obj('@', LEVEL_WIDTH/2, LEVEL_HEIGHT/2);
    player.add_component(new components::player());
    player.add_component(new components::combat(100,12));
    player.add_component(new components::stamina(100, 1, 1));
    handle_map::init(player);
    init_UI();

    while (!timeline::quit_game) {
        timeline::execute_top();
    }

    handle_map::rm_all_objs();
    timeline::end();
    end_UI();
}