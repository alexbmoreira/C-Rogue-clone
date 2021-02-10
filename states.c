#include "states.h"
#include "graphics.h"

extern void setViewPosition(float, float, float);
extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);
extern void setOldViewPosition(float, float, float);

void addState(worldState state) {
    copyWorld(&state);
    state.active = 1;
    states[state.state_id] = state;
}

worldState getState(int state_id) {
    return states[state_id];
}

void copyWorld(worldState *state) {
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDY; j++) {
            for(int k = 0; k < WORLDZ; k++) {
                state->world[i][j][k] = world[i][j][k];
            }
        }
    }

    float x, y, z;
    getOldViewPosition(&x, &y, &z);
    state->player_x = x;
    state->player_y = y;
    state->player_z = z;
}

void updateState(int state_id) {
    copyWorld(&states[state_id]);
    printSlice(50, state_id);
}

void stateToWorld(worldState state) {
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDY; j++) {
            for(int k = 0; k < WORLDZ; k++) {
                world[i][j][k] = state.world[i][j][k];
            }
        }
    }
    setViewPosition(state.player_x, state.player_y, state.player_z);
    setOldViewPosition(state.player_x, state.player_y, state.player_z);
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


    fprintf(f, "Player spawn:\n");    
    fprintf(f, "(%f, %f, %f)\n", states[state_id].player_x, states[state_id].player_y, states[state_id].player_z);    
}