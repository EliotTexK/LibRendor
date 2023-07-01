#ifndef UTILITY_H
#define UTILITY_H

#include <unordered_map>
#include <array>
#include <map>

const int LEVEL_WIDTH = 100;
const int LEVEL_HEIGHT = 30;

const int VIEW_WIDTH = 80;
const int VIEW_HEIGHT = 20;

// INLINE
inline bool is_in_level_bounds(int x, int y) {
    return (x >= 0 && x < LEVEL_WIDTH && y >= 0 && y < LEVEL_HEIGHT);
}

enum directions {
    NW,
    W,
    SW,
    N,
    X,
    S,
    NE,
    E,
    SE
};

const char direction_to_components[9][2] = {
    {-1,-1},
    {-1,0},
    {-1,1},
    {0,-1},
    {0,0},
    {0,1},
    {1,-1},
    {1,0},
    {1,1}
};

inline char components_to_direction(int x, int y) {
    return (x+1) * 3 + (y+1);
}

#endif