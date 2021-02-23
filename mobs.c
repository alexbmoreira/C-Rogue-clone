#include "mobs.h"
#include "graphics.h"

extern void setMeshID(int, int, float, float, float);
extern void unsetMeshID(int);
extern void setTranslateMesh(int, float, float, float);
extern void setRotateMesh(int, float, float, float);
extern void setScaleMesh(int, float);

extern void drawMesh(int id);
extern void hideMesh(int id);

void createMob(int id, int mesh_number, float x, float y, float z) {
    mob new_mob;
    new_mob.mesh_id = id;
    new_mob.mesh_number = mesh_number;
    new_mob.x = x;
    new_mob.y = y;
    new_mob.z = z;
    
    mobs[id] = new_mob;
    setMob(new_mob);
}

void setMob(mob m) {
    setMeshID(m.mesh_id, m.mesh_number, m.x, m.y, m.z);
}

void freeMob(mob m) {
    unsetMeshID(m.mesh_id);
}

void drawMob(mob m) {
    drawMesh(m.mesh_id);
}

void hideMob(mob m) {
    hideMesh(m.mesh_id);
}