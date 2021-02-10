#include "graphics.h"

typedef struct worldState {
    int active;
    int state_id;
    GLubyte world[WORLDX][WORLDY][WORLDZ];
    float player_x, player_y, player_z;
} worldState;

worldState states[100];

void addState(worldState state);

worldState getState(int state_id);

void copyWorld(worldState *state);

void updateState(int state_id);

void stateToWorld(worldState state);

void clearWorld();

void printSlice(int x, int state_id);