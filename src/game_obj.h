#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <vector>
#include "utility.h"
#include "components.h"

// Underlying data structure managed by game objects.
// Don't use this for implementing event logic.
struct game_obj_data {
    int display_char;
    int x;
    int y;
    std::string name = "doyle";
    component* components[COMPONENTS_COUNT];
    game_obj_data();
    ~game_obj_data();
};

// Reference counter for game objects.
// Don't use this for implementing event logic.
// Do use this for implementing data structures
// (maps, inventories, etc.), but make sure you
// decrement and increment references properly.
class game_obj_rc {
    int refs;
    public:
    game_obj_data* data;
    // refs = 1 with default constructor, and
    // allocates a game_obj_data on the heap
    game_obj_rc();
    game_obj_rc(int display);
    // this will delete the reference counter
    // when its reference count reaches zero
    void dec_refs();
    void inc_refs();
    private:
    ~game_obj_rc();
};

// All game objects are reference counted. This makes
// it safe to check for deletion.
// DO NOT ALLOCATE THESE ON THE HEAP
class game_obj {
    game_obj_rc* shared_rc;
    public:
    // increments the ref count
    game_obj_rc* get_shared_rc();
    // will fail if the object already has a component
    // of the same type
    void add_component(component* cp);
    void rm_component(int id);
    // Will automatically attempt a cast, indexing
    // into the underlying component array using id,
    // so give each component a unique id. Will return
    // nullptr if the object doesn't have that component.
    template <typename T>
    T* get_component(int id);
    // getters and setters are safe
    // getters return -1 if the object doesn't exist
    void set_display_char(int ch);
    int get_display_char();
    void set_x(int x);
    void set_y(int y);
    int get_x();
    int get_y();
    void set_name(std::string name);
    std::string get_name(); // returns ERROR if doesnt exist
    // safe check for deletion
    bool exists();
    // deletes the underlying object from memory, but
    // allows you to safely check if it has been deleted
    void rm_from_game();
    // assignment increments the ref count
    game_obj& operator= (const game_obj& obj);
    // copying/pass-by-value increments the ref count
    game_obj(const game_obj& obj);    
    // deleting a game object decrements the ref count
    // when the ref count reaches zero, the object is deleted
    ~game_obj();
    // constructing a new game_object allocates a new
    // reference counter on the heap and sets its reference
    // count to 1
    game_obj(int display);
    game_obj(int display, int x, int y);
    // create game object based on ref count object (for data structures)
    game_obj(game_obj_rc*& rc);
};

#include "game_obj.hpp"

#endif