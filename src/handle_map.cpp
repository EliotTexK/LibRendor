#include "handle_map.h"

void construct_test_enemy(game_object& base) {
    base.display_char = 'g';
    base.name = "the goblin";

    stamina* _stats = new stamina(100,1);
    add_component(base, *_stats);
}

void init_map(game_object& player) {
    for (int x = 0; x < LEVEL_WIDTH; x++) {
        for (int y = 0; y < LEVEL_HEIGHT; y++) {
            objects_map[x][y] = nullptr;
        }
    }

    fill_terrain_with_noise(level_terrain,'#',30);
    char mask_1[9] = {1,1,2,2,2,1,1,1,1};
    char mask_2[9] = {0,0,0,2,2,1,1,1,1};
    char mask_3[9] = {0,0,0,0,2,2,2,2,1};
    marching_squares(level_terrain, '#', 1, mask_1);
    marching_squares(level_terrain, '#', 2, mask_2);
    connect_rooms(level_terrain);
    marching_squares(level_terrain, '#', 4, mask_3);

    vector<array<int,2>> spawnpoints = random_item_placement(level_terrain, 2);
    place_game_object(player, spawnpoints[0][0], spawnpoints[0][1]);

    for (int i = 1; i < spawnpoints.size(); i++) {
        game_object * test_enemy = new game_object();
        construct_test_enemy(*test_enemy);
        monsters.insert(test_enemy);
        place_game_object(*test_enemy,spawnpoints[i][0],
            spawnpoints[i][1]);
    }
}

void place_game_object(game_object& go, int x, int y) {
    if (!is_in_level_bounds(x,y)) {
        throw runtime_error("tryna place an object out of bounds: check that shit!");
    }
    objects_map[x][y] = &go;
    go.x = x;
    go.y = y;
}

void move_game_object(game_object& go, int new_x, int new_y) {
    if (!is_in_level_bounds(new_x,new_y)) {
        throw runtime_error("tryna move an object out of bounds: check that shit!");
    }
    objects_map[go.x][go.y] = nullptr;
    objects_map[new_x][new_y] = &go;
    go.x = new_x;
    go.y = new_y;
}

void cleanup_map_data() {
    for (game_object* mon : monsters) {
        delete mon;
    }
}