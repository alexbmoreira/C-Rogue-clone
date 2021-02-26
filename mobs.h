#include <stdio.h>
#include <stdlib.h>

#define NUM_MOBS 9
#define MOB_MOVEMENT 0.1

typedef struct mob
{
    int mesh_id;
    int mesh_number;

    int seen;

    float scale;
    float x, y, z;
    int move_x, move_y, move_z;
} mob;

mob mobs[NUM_MOBS];

void initMeshMobs();

void createMeshMob(int id, int mesh_number, float x, float y, float z);
void setMeshMob(mob m);
void freeMeshMob(mob m);
void drawMeshMob(mob m);
void hideMeshMob(mob m);

void translateMeshMob(mob *m, float x, float y, float z);
void scaleMeshMob(mob *m, float scale);

void moveMeshMob(mob *m);