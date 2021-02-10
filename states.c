#include "states.h"

void addState(worldState state) {
    copyWorld(state);
    states[state.state_id] = state;
}

worldState getState(int state_id) {
    return states[state_id];
}

void copyWorld(worldState state) {
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDY; j++) {
            for(int k = 0; k < WORLDZ; k++) {
                state.world[i][j][k] = world[i][j][k];
            }
        }
    }
}

void updateState(int state_id) {
    copyWorld(states[state_id]);
}

void stateToWorld(worldState state) {
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDY; j++) {
            for(int k = 0; k < WORLDZ; k++) {
                world[i][j][k] = state.world[i][j][k];
            }
        }
    }
}

void clearWorld() {
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDY; j++) {
            for(int k = 0; k < WORLDZ; k++) {
                world[i][j][k] = 0;
            }
        }
    }
}