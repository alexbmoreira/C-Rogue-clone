#include <stdio.h>
#include <stdlib.h>

#define NUM_MOBS 20

typedef struct mob
{
    int mesh_id;
    int mesh_number;

    float x, y, z;
} mob;

mob mobs[NUM_MOBS];

void createMob(int id, int mesh_number, float x, float y, float z);
void setMob(mob m);
void freeMob(mob m);
void drawMob(mob m);
void hideMob(mob m);
