#include "graphics.h"

typedef struct worldState {
    int state_id;
    GLubyte world[WORLDX][WORLDY][WORLDZ];
} worldState;