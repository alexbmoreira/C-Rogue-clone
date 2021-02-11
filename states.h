#include "graphics.h"

typedef struct worldState {
    int active;
    int state_id;
    GLubyte world[WORLDX][WORLDY][WORLDZ];
    float vp_x, vp_y, vp_z;
} worldState;

worldState states[100];

void addState(worldState state);

worldState getState(int state_id);

void copyWorld(worldState *state);

void setStateViewPoint(worldState *state);

void updateState(int state_id);

void stateToWorld(worldState state);

void clearWorld();

void printSlice(int x, int state_id);