#include "states.h"

extern char maze[WORLDX][WORLDZ];

extern void setViewPosition(float, float, float);
extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);
extern void setOldViewPosition(float, float, float);

void addState(worldState state) {
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
    setStateMaze(state);
    setStateMobs(state);
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
    for(int i = 0; i < NUM_ROOMS * 10; i++) {
        state->corridors[i] = corridors[i];
    }
}

void setStateMaze(worldState *state) {
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDZ; j++) {
            state->maze[i][j] = maze[i][j];
        }
    }
}

void setStateMobs(worldState *state) {
    for(int i = 0; i < NUM_MOBS; i++) {
        state->mobs[i] = mobs[i];
        freeMeshMob(state->mobs[i]);
    }
}

void updateState(int state_id) {
    copyWorld(&states[state_id]);
}

void stateToWorld(worldState state) {
    printState(state.state_id);

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
    for(int i = 0; i < NUM_ROOMS * 10; i++) {
        corridors[i] = state.corridors[i];
    }
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDZ; j++) {
            maze[i][j] = state.maze[i][j];
        }
    }
    for(int i = 0; i < NUM_MOBS; i++) {
        mobs[i] = state.mobs[i];
        setMeshMob(state.mobs[i]);
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

void printState(int state_id) {
    FILE *f = fopen("world.log", "a");
    fprintf(f, "======================\n");
    fprintf(f, "State %d:\n------------\n", state_id);   

    fprintf(f, "Mobs:\n");
    fprintf(f, "|ID\t|Num\t|x\t\t|y\t\t|z\t\t|\n");
    for(int i = 0; i < NUM_MOBS; i++) {
        fprintf(f, "|%d\t|%d\t\t|%0.2f\t|%0.2f\t|%0.2f\t|\n", states[state_id].mobs[i].mesh_id, states[state_id].mobs[i].mesh_number, states[state_id].mobs[i].x, states[state_id].mobs[i].y, states[state_id].mobs[i].z);
    }
    fprintf(f, "\n\n");   

    fprintf(f, "Player spawn:\n");
    fprintf(f, "(%f, %f, %f)\n", states[state_id].vp_x, states[state_id].vp_y, states[state_id].vp_z);

    fprintf(f, "======================\n\n");
}