#include "graphics.h"

typedef struct worldState {
    int state_id;
    GLubyte world[WORLDX][WORLDY][WORLDZ];
} worldState;

worldState states[100];

void addState(int state_id);
worldState getState(int state_id);