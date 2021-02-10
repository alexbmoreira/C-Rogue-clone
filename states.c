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

void printSlice(int x, int state_id) {
    FILE *f = fopen("world.log", "w");

    for(int j = WORLDY - 1; j >= 0; j--) {
        for(int k = 0; k < WORLDZ; k++) {
            fprintf(f, "%d", (state_id >= 0) ? states[state_id].world[x][j][k] : world[x][j][k]);
        }
        fprintf(f, "\n");
    }
}