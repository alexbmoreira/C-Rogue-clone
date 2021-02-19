#include "graphics.h"
#include "generation.h"

typedef struct worldState
{
    int active;
    int state_id;
    GLubyte world[WORLDX][WORLDY][WORLDZ];
    room rooms[NUM_ROOMS];
    corridor corridors[NUM_ROOMS * 10];
    char maze[WORLDX][WORLDZ];
    float vp_x, vp_y, vp_z;
} worldState;

worldState states[100];

void addState(worldState state);

worldState getState(int state_id);

void copyWorld(worldState *state);
void setStateViewPoint(worldState *state);
void setStateRooms(worldState *state);
void setStateMaze(worldState *state);

void updateState(int state_id);

void stateToWorld(worldState state);

void clearWorld();

void printSlice(int x, int state_id);