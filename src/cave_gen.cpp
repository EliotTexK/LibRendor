#include "cave_gen.h"

void fill_terrain_with_noise(char (&level_terrain)[LEVEL_WIDTH][LEVEL_HEIGHT],
    char wall_tile, int percent) {
    for (int x = 0; x < LEVEL_WIDTH; x++) {
        for (int y = 0; y < LEVEL_HEIGHT; y++) {
            if (x == 0 || x == LEVEL_WIDTH-1 || y == 0 || y == LEVEL_HEIGHT-1) {
                level_terrain[x][y] = wall_tile;
            } else {
                level_terrain[x][y] = (rand() % 100 < percent) * wall_tile;
            }
        }
    }
}

void marching_squares(char (&level_terrain)[LEVEL_WIDTH][LEVEL_HEIGHT],
    char wall_tile, int iterations, char (&valid_neighbor_count)[9]) {
    for (int i = 0; i < iterations; i++) {
        for (int x = 1; x < LEVEL_WIDTH - 1; x++) {
            for (int y = 1; y < LEVEL_HEIGHT - 1; y++) {
                char wall_count = 0;
                // count neighboring squares to each square
                for (int x_neighbor = x - 1; x_neighbor <= x + 1;
                        x_neighbor++) {
                    for (int y_neighbor = y - 1; y_neighbor <= y + 1;
                            y_neighbor++) {
                            wall_count += (level_terrain[x_neighbor][y_neighbor]
                                && !(x_neighbor == x && y_neighbor == y));
                        }
                    }

                if (valid_neighbor_count[wall_count] == 1) {
                    level_terrain[x][y] = wall_tile;
                }
                if (valid_neighbor_count[wall_count] == 0) {
                    level_terrain[x][y] = 0;
                }
            }
        }
    }
}

// returns a list of room border cells
queue<array<int,2>> fill_room_get_borders(char (&rooms_mask)[LEVEL_WIDTH][LEVEL_HEIGHT],
    char (&level_terrain)[LEVEL_WIDTH][LEVEL_HEIGHT], int start_x, int start_y, int room_index) {
    queue<array<int,2>> result = queue<array<int,2>>();
    queue<array<int,2>> bfs = queue<array<int,2>>();
    bfs.push({start_x, start_y});
    while (!bfs.empty()) {
        array<int,2> top = bfs.front();
        bfs.pop();
        int x = top[0];
        int y = top[1];
        array<array<int,2>,4> to_push = {{
            {x,y-1},
            {x,y+1},
            {x+1,y},
            {x-1,y}
        }};
        for (array<int,2> i : to_push) {
            if (is_in_level_bounds(i[0],i[1]) && !rooms_mask[i[0]][i[1]]) {
                if (!level_terrain[i[0]][i[1]]) {
                    bfs.push(i);
                    rooms_mask[i[0]][i[1]] = room_index;
                } else {
                    result.push(i);
                }
            }
        }
    }
    return result;
}

void connect_rooms(char (&level_terrain)[LEVEL_WIDTH][LEVEL_HEIGHT]) {
    char rooms_mask[LEVEL_WIDTH][LEVEL_HEIGHT];
    char backtrack[LEVEL_WIDTH][LEVEL_HEIGHT];
    for (int x = 0; x < LEVEL_WIDTH; x++) {
        for (int y = 0; y < LEVEL_HEIGHT; y++) {
            rooms_mask[x][y] = 0;
            backtrack[x][y] = 4;
            // 0 - go down
            // 1 - go up
            // 2 - go left
            // 3 - go right
            // 4 - done;
        }
    }

    // identify separate rooms and room borders
    int total_rooms = 1;
    vector<queue<array<int,2>>> edges = vector<queue<array<int,2>>>();
    edges.push_back(queue<array<int,2>>()); // 0th room has no edges
    for (int x = 0; x < LEVEL_WIDTH; x++) {
        for (int y = 0; y < LEVEL_HEIGHT; y++) {
            if (!level_terrain[x][y] && !rooms_mask[x][y]) {
                queue<array<int,2>> room_edges = 
                fill_room_get_borders(rooms_mask, level_terrain, x, y, total_rooms);
                edges.push_back(room_edges);
                total_rooms += 1;
            }
        }
    }

    // use bfs + backtracking to connect rooms
    int connected_count = 1;
    vector<char> connected = vector<char>();
    for (int i = 0; i < total_rooms; i++) {
        connected.push_back(0);
    }

    int seed_room = rand() % (total_rooms - 1) + 1;
    connected[seed_room] = true;

    queue<array<int,2>> bfs = edges[seed_room];
    while (connected_count < total_rooms - 1 && !bfs.empty()) {
        array<int,2> top = bfs.front();
        bfs.pop();
        int x = top[0];
        int y = top[1];
        if (!is_in_level_bounds(x,y)) continue;
        rooms_mask[x][y] = seed_room;
        array<array<int,2>,4> to_push = {{
            {x,y-1},
            {x,y+1},
            {x+1,y},
            {x-1,y}
        }};
        for (int i = 0; i < 4; i++) {
            array<int,2> neighbor = to_push[i];
            int& neighbor_x = neighbor[0];
            int& neighbor_y = neighbor[1];
            if (is_in_level_bounds(neighbor_x,neighbor_y)) {
                int neighbor_room = rooms_mask[neighbor_x][neighbor_y];
                if (!neighbor_room) {
                    backtrack[neighbor_x][neighbor_y] = i;
                    rooms_mask[neighbor_x][neighbor_y] = seed_room;
                    bfs.push(neighbor);
                } else {
                    if (!connected[neighbor_room]) {
                        connected_count++;
                        connected[neighbor_room] = true;
                        queue<array<int,2>> new_edges = edges[neighbor_room];
                        while (!new_edges.empty()) {
                            bfs.push(new_edges.front());
                            new_edges.pop();
                        }
                        int traverse_x = x;
                        int traverse_y = y;
                        bool done = false;
                        while (!done) {
                            int rand_x = traverse_x + (rand() % 3) - 1;
                            int rand_y = traverse_y + (rand() % 3) - 1;
                            if (is_in_level_bounds(rand_x,rand_y)) {
                                level_terrain[rand_x][rand_y] = 0;
                            }
                            level_terrain[traverse_x][traverse_y] = 0;
                            switch (backtrack[traverse_x][traverse_y]) {
                            case 0:
                                traverse_y++;
                                break;
                            case 1:
                                traverse_y--;
                                break;
                            case 2:
                                traverse_x--;
                                break;
                            case 3:
                                traverse_x++;
                                break;
                            case 4:
                                done = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

vector<array<int,2>> random_item_placement(char (&level_terrain)[LEVEL_WIDTH][LEVEL_HEIGHT], char density_percent) {
    vector<array<int,2>> result;
    for (int x = 0; x < LEVEL_WIDTH; x++) {
        for (int y = 0; y < LEVEL_HEIGHT; y++) {
            if (!level_terrain[x][y]) {
                if ((rand() % 100) < density_percent) {
                    result.push_back({x,y});
                }
            }
        }
    }
    shuffle(result.begin(), result.end(), default_random_engine(rand()));
    return result;
}