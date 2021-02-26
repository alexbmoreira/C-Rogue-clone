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

    new_mob.move_x = 1;
    new_mob.move_y = 0;
    new_mob.move_z = 0;
    
    mobs[id] = new_mob;
    setMeshMob(new_mob);
}

void setMeshMob(mob m) {
    if(m.x > 0 && m.y > 0 && m.z >0) {
        setMeshID(m.mesh_id, m.mesh_number, m.x, m.y, m.z);
    }
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

void translateMeshMob(mob *m, float x, float y, float z) {
    if(m->x == 0 && m->y == 0 && m->z == 0) return;

    m->x = x;
    m->y = y;
    m->z = z;

    setTranslateMesh(m->mesh_id, m->x, m->y, m->z);
    drawMeshMob(*m);
}

void checkMeshMobMovement(mob *m) {
    if(world[(int)m->x + 1][(int)m->y][(int)m->z] != 0) {
        m->move_x = -1;
    }
    else if(world[(int)m->x - 1][(int)m->y][(int)m->z] != 0) {
        m->move_x = 1;
    }
}

void moveMeshMob(mob *m) {
    checkMeshMobMovement(m);

    if(m->move_x > 0) {
        translateMeshMob(m, m->x + MOB_MOVEMENT, m->y, m->z);
    }
    else if(m->move_x < 0) {
        translateMeshMob(m, m->x - MOB_MOVEMENT, m->y, m->z);
    }
}