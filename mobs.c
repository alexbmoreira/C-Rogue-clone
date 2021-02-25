#include "mobs.h"
#include "graphics.h"

extern void setMeshID(int, int, float, float, float);
extern void unsetMeshID(int);
extern void setTranslateMesh(int, float, float, float);
extern void setRotateMesh(int, float, float, float);
extern void setScaleMesh(int, float);

extern void drawMesh(int id);
extern void hideMesh(int id);

void initMeshMobs() {
    for(int i = 0; i < NUM_MOBS; i++) {
        mobs[i].mesh_id = i;
    }
}

void createMeshMob(int id, int mesh_number, float x, float y, float z) {
    mob new_mob;
    new_mob.mesh_id = id;
    new_mob.mesh_number = mesh_number;
    new_mob.x = x;
    new_mob.y = y;
    new_mob.z = z;
    
    mobs[id] = new_mob;
    printf("Mesh number: %d\n", new_mob.mesh_number);
    setMeshMob(new_mob);
}

void setMeshMob(mob m) {
    printf("Mesh number: %d\n", m.mesh_number);
    setMeshID(m.mesh_id, m.mesh_number, m.x, m.y, m.z);
}

void freeMeshMob(mob m) {
    unsetMeshID(m.mesh_id);
}

void drawMeshMob(mob m) {
    drawMesh(m.mesh_id);
}

void hideMeshMob(mob m) {
    hideMesh(m.mesh_id);
}