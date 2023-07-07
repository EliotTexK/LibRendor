#include "handle_map.h"
#include "timeline.h"
#include "events.h"

game_obj_rc* handle_map::objs_map[LEVEL_WIDTH][LEVEL_HEIGHT];

void handle_map::init(game_obj& player) {
    char level_mask[LEVEL_WIDTH][LEVEL_HEIGHT];
    fill_terrain_with_noise(level_mask,'1',40);
    char rule_1[9] = {0,0,2,2,2,1,1,1,1};
    char rule_2[9] = {0,0,0,0,2,2,2,2,2};
    char rule_3[9] = {0,0,0,0,2,2,2,1,1};
    marching_squares(level_mask,1,3,rule_1);
    connect_rooms(level_mask);
    marching_squares(level_mask,1,2,rule_2);
    marching_squares(level_mask,1,2,rule_3);
    for (int x = 0; x < LEVEL_WIDTH; x++) {
        for (int y = 0; y < LEVEL_HEIGHT; y++) {
            if (level_mask[x][y]) objs_map[x][y] = new game_obj_rc('#');
            else objs_map[x][y] = nullptr;
        }
    }
    std::vector<std::array<int,2>> spawnpoints = random_item_placement(level_mask,2);
    player.set_x(spawnpoints[0][0]);
    player.set_y(spawnpoints[0][1]);
    place_game_obj(player);
    for (int i = 1; i < spawnpoints.size(); i++) {
        game_obj test_enemy = game_obj('g',spawnpoints[i][0],spawnpoints[i][1]);
        test_enemy.set_name("goblin");
        place_game_obj(test_enemy);
    }
}

void handle_map::place_game_obj(game_obj& obj) {
    if (!obj.exists()) return;
    int x = obj.get_x();
    int y = obj.get_y();
    if (!objs_map[x][y]) {
        // this increments the ref count
        objs_map[x][y] = obj.get_shared_rc();
        timeline::insert_event(new events::init(obj));
    }
}

void handle_map::move_game_obj(game_obj& obj, const int& new_x, const int& new_y) {
    int x = obj.get_x();
    int y = obj.get_y();
    if (!objs_map[x][y]) return;
    game_obj_rc* replace = objs_map[new_x][new_y];
    if (replace) {
        // if the object has been deleted, overwrite and
        // decrement its references
        if (!replace->data) {
            replace->dec_refs();
        } else {
            // if it hasn't been deleted, then we can't
            // overwrite it
            return;
        }
    }
    objs_map[new_x][new_y] = objs_map[x][y];
    objs_map[x][y] = nullptr;
    obj.set_x(new_x);
    obj.set_y(new_y);
}

void handle_map::rm_game_obj(int x, int y) {
    if (objs_map[x][y]) {
        objs_map[x][y]->dec_refs();
        objs_map[x][y] = nullptr;
    }
}

game_obj handle_map::get_game_obj(int x, int y) {
    // constructor increments rc
    return game_obj(objs_map[x][y]);
}

void handle_map::rm_all_objs() {
    for (int x = 0; x < LEVEL_WIDTH; x++) {
        for (int y = 0; y < LEVEL_HEIGHT; y++) {
            rm_game_obj(x,y);
        }
    }
}