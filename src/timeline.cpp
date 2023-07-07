#include "timeline.h"

bool timeline::quit_game = false;
unsigned long timeline::global_time = 0;
std::priority_queue<event*,std::vector<event*>,compare_events> timeline::events;


void timeline::init() {
    events = std::priority_queue<event*,std::vector<event*>,compare_events>();
}

void timeline::insert_event(event* ev) {
    ev->global_time = ev->time + global_time;
    events.push(ev);
}

void timeline::execute_top() {
    if (events.empty()) return;
    event* ev = events.top();      // get the last element
    events.pop();                  // remove from p-queue
    ev->execute();                 // execute
    global_time = ev->global_time; // set global time
    delete ev;                     // deallocate
}

void timeline::end() {
    while (!events.empty()) {
        delete events.top();
        events.pop();
    }
}