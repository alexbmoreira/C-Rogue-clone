#include <stdio.h>
#include <stdlib.h>

#define NUM_MOBS 5

typedef struct mob
{
    int mesh_id;
    int mesh_number;

    float x, y, z;
} mob;

mob mobs[NUM_MOBS];

void initMeshMobs();

void createMeshMob(int id, int mesh_number, float x, float y, float z);
void setMeshMob(mob m);
void freeMeshMob(mob m);
void drawMeshMob(mob m);
void hideMeshMob(mob m);
