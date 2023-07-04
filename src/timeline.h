#ifndef TIMELINE_H
#define TIMELINE_H

#include "game_obj.h"
#include <queue>
#include <vector>
#include <stdexcept>

// Base class for implementing game logic. Events are stored on
// a timeline (priority queue) to allow for turn interleaving.
// ALWAYS ALLOCATE EVENTS ON THE HEAP!!!
struct event {
    int time = 0;
    long global_time = 0;
    event() {}
    event(int local_time) : time(local_time) {}
    // use the base class for events that don't do anything
    virtual void execute() {};
    virtual ~event() {};
};

struct compare_events {
    bool operator() (const event* ev1, const event* ev2) const {
        return ev1->global_time >= ev2->global_time;
    }
};

// The timeline uses a priority queue, sorting by the event's time.
// When events are added, the current global time is added to theirs.
// When events are popped off the top, we add their time to global.
struct timeline {
    static bool quit_game; // had to put it somewhere
    static int global_time;
    static std::priority_queue<event*,std::vector<event*>,compare_events> events;
    static void init();
    // ties are broken based on order inserted
    static void insert_event(event* ev);
    static void execute_top();
    static void end();
};

#endif