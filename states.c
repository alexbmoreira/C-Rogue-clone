#include "states.h"

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

    setStateViewPoint(state);
    setStateRooms(state);
}

void setStateViewPoint(worldState *state) {
    float x, y, z;
    getOldViewPosition(&x, &y, &z);

    int int_x = (int)x*(-1);
    int int_y_head = (int)y*(-1);
    int int_y = ((int)y + 1)*(-1);
    int int_z = (int)z*(-1);

    state->vp_x = x;
    state->vp_y = y;
    state->vp_z = z;

    if(world[int_x + 1][int_y][int_z] == 0 && world[int_x + 1][int_y_head][int_z] == 0) {
        state->vp_x = x - 1;
    }
    else if(world[int_x - 1][int_y][int_z] == 0 && world[int_x - 1][int_y_head][int_z] == 0) {
        state->vp_x = x + 1;
    }
    if(world[int_x][int_y][int_z + 1] == 0 && world[int_x][int_y_head][int_z + 1] == 0) {
        state->vp_z = z - 1;
    }
    else if(world[int_x][int_y][int_z - 1] == 0 && world[int_x][int_y_head][int_z - 1] == 0) {
        state->vp_z = z + 1;
    }
}

void setStateRooms(worldState *state) {
    for(int i = 0; i < NUM_ROOMS; i++) {
        state->rooms[i] = rooms[i];
    }
}

void updateState(int state_id) {
    copyWorld(&states[state_id]);
}

void stateToWorld(worldState state) {
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDY; j++) {
            for(int k = 0; k < WORLDZ; k++) {
                world[i][j][k] = state.world[i][j][k];
            }
        }
    }
    setViewPosition(state.vp_x, state.vp_y, state.vp_z);
    setOldViewPosition(state.vp_x, state.vp_y, state.vp_z);

    for(int i = 0; i < NUM_ROOMS; i++) {
        rooms[i] = state.rooms[i];
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


    fprintf(f, "Player spawn:\n");    
    fprintf(f, "(%f, %f, %f)\n", states[state_id].vp_x, states[state_id].vp_y, states[state_id].vp_z);    
}