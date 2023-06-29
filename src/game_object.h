#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>

using namespace std;

struct game_object {
    int x;
    int y;
    char display_char;
    int max_hp;
    int hp = max_hp;
    string name = "no maidens?";
};

#endif