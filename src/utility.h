#ifndef UTILITY_H
#define UTILITY_H

const int LEVEL_WIDTH = 100;
const int LEVEL_HEIGHT = 30;

const int VIEW_WIDTH = 80;
const int VIEW_HEIGHT = 20;

// INLINE
inline bool is_in_level_bounds(int x, int y) {
    return (x >= 0 && x < LEVEL_WIDTH && y >= 0 && y < LEVEL_HEIGHT);
}

enum comp_ids {
    c_stats
};

enum action_ids {
    a_move_direction,
    a_start_running,
    a_stop_running
};

enum directions {
    d_up,
    d_up_right,
    d_right,
    d_down_right,
    d_down,
    d_down_left,
    d_left,
    d_up_left
};

const char direction_components[8][2] = {
    {0,-1},
    {1,-1},
    {1,0},
    {1,1},
    {0,1},
    {-1,1},
    {-1,0},
    {-1,-1}
};

#endif