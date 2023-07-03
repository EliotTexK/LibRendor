#include "timeline.h"

bool timeline::quit_game = false;
int timeline::global_time = 0;
std::priority_queue<event*,std::vector<event*>,compare_events> timeline::events;


void timeline::init() {
    events = std::priority_queue<event*,std::vector<event*>,compare_events>();
    // pass
}

void timeline::insert_event(event* ev) {
    ev->time += global_time;
    events.push(ev);
}

void timeline::execute_top() {
    if (events.empty()) return;
    event* ev = events.top();   // get the last element
    events.pop();               // remove from p-queue
    ev->execute();              // execute
    global_time = ev->time;     // set global time
    delete ev;                  // deallocate
}

void timeline::end() {
    while (!events.empty()) {
        delete events.top();
        events.pop();
    }
}