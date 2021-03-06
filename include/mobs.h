#include <stdio.h>
#include <stdlib.h>

#define NUM_MOBS 9
#define MOB_MOVEMENT 0.1

#define MOB_INACTIVE -1
#define MOB_WAITING 0
#define MOB_ADJACENT 1
#define MOB_PLAYER_IN_VIEW 2
#define MOB_RANDOM_SEARCH 3

extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);

typedef struct mob
{
    int mesh_id;
    int mesh_number;

    int mob_type; // 1 = plant, 2 = random, 3 = responsive
    int mob_state;

    int visible;
    int seen;
    int active;

    float scale;
    float x, y, z;
    int target_x, target_y, target_z;
} mob;

mob mobs[NUM_MOBS];

void initMeshMobs();

void createMeshMob(int id, float x, float y, float z);
void setMeshMob(mob m);
void freeMeshMob(mob m);
void drawMeshMob(mob m);
void hideMeshMob(mob m);

void translateMeshMob(mob *m, float x, float y, float z);
void scaleMeshMob(mob *m, float scale);

void moveMeshMob(mob *m);

void attackMob(mob *m);
void attackPlayer(mob *m);

void mobActivites();

void pickRandomTarget(mob *m, int stay_in_room);