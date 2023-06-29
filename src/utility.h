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

#endif