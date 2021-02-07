#include "states.h"

void addState(int state_id, worldState state) {
    states[state_id] = state;
}

worldState getState(int state_id) {
    return states[state_id];
}