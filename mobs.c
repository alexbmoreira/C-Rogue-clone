#include "mobs.h"
#include "graphics.h"
#include "utils.h"

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
        mobs[i].visible = 0;
    }
}

void scaleByMeshNum(mob *m) {
    switch(m->mesh_number) {
        case 0:
            scaleMeshMob(m, 1);
            break;
        case 1:
            scaleMeshMob(m, 0.5);
            break;
        case 2:
            scaleMeshMob(m, 0.3);
            break;
        case 3:
            scaleMeshMob(m, 0.25);
            break;
        default:
            break;
    }
}

void createMeshMob(int id, float x, float y, float z) {
    mob new_mob;
    new_mob.mesh_id = id;
    new_mob.visible = 1;
    new_mob.seen = 0;

    new_mob.active = 1;
    new_mob.mob_type = getRandom(1, 3);

    switch(new_mob.mob_type) {
        case 1:
            new_mob.mesh_number = 3;
            break;
        case 2:
            new_mob.mesh_number = 2;
            break;
        case 3:
            new_mob.mesh_number = 1;
            break;
        default:
            break;
    }

    new_mob.x = x;
    new_mob.y = y;
    new_mob.z = z;
    
    new_mob.move_x = 0;
    new_mob.move_y = 0;
    new_mob.move_z = 0;

    scaleByMeshNum(&new_mob);

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
    if(m.visible == 1 && m.active == 1) {
        setScaleMesh(m.mesh_id, m.scale);
        drawMesh(m.mesh_id);
        // printf("%d mesh #%d is visible\n", m.mesh_number, m.mesh_id);
    }
    else hideMeshMob(m);
}

void hideMeshMob(mob m) {
    if(m.visible == 0 || m.active == 0) {
        hideMesh(m.mesh_id);
        // printf("%d mesh #%d is not visible\n", m.mesh_number, m.mesh_id);
    }
}

void translateMeshMob(mob *m, float x, float y, float z) {
    if(m->x == 0 && m->y == 0 && m->z == 0) return;

    m->x = x;
    m->y = y;
    m->z = z;

    setTranslateMesh(m->mesh_id, m->x, m->y, m->z);
}

void scaleMeshMob(mob *m, float scale) {
    if(m->x == 0 && m->y == 0 && m->z == 0) return;

    m->scale = scale;

    setScaleMesh(m->mesh_id, m->scale);
}

void checkMeshMobMovement(mob *m) {
    if(m->move_x == 1 && world[(int)m->x + 1][(int)m->y][(int)m->z] != 0) {
        m->move_x = -1;
    }
    else if(m->move_x == -1 && world[(int)m->x - 1][(int)m->y][(int)m->z] != 0) {
        m->move_x = 1;
    }

    if(m->move_y == 1 && world[(int)m->x][(int)m->y + 1][(int)m->z] != 0) {
        m->move_y = -1;
    }
    else if(m->move_y == -1 && world[(int)m->x][(int)m->y - 1][(int)m->z] != 0) {
        m->move_y = 1;
    }

    if(m->move_z == 1 && world[(int)m->x][(int)m->y][(int)m->z + 1] != 0) {
        m->move_z = -1;
    }
    else if(m->move_z == -1 && world[(int)m->x][(int)m->y][(int)m->z - 1] != 0) {
        m->move_z = 1;
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

    if(m->move_y > 0) {
        translateMeshMob(m, m->x, m->y + MOB_MOVEMENT, m->z);
    }
    else if(m->move_y < 0) {
        translateMeshMob(m, m->x , m->y- MOB_MOVEMENT, m->z);
    }
    
    if(m->move_z > 0) {
        translateMeshMob(m, m->x, m->y, m->z + MOB_MOVEMENT);
    }
    else if(m->move_z < 0) {
        translateMeshMob(m, m->x, m->y, m->z - MOB_MOVEMENT);
    }

    drawMeshMob(*m);
}