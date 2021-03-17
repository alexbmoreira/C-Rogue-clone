#include "mobs.h"
#include "graphics.h"
#include "utils.h"
#include "generation.h"

extern void setMeshID(int, int, float, float, float);
extern void unsetMeshID(int);
extern void setTranslateMesh(int, float, float, float);
extern void setRotateMesh(int, float, float, float);
extern void setScaleMesh(int, float);

extern void drawMesh(int id);
extern void hideMesh(int id);

extern int player_turn;

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
            scaleMeshMob(m, 0.25);
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
    
    new_mob.target_x = new_mob.x;
    new_mob.target_y = new_mob.y;
    new_mob.target_z = new_mob.z;

    scaleByMeshNum(&new_mob);

    mobs[id] = new_mob;

    setMeshMob(new_mob);
    drawMeshMob(new_mob);
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
    if(m->target_x == 1 && world[(int)m->x + 1][(int)m->y][(int)m->z] != 0) {
        m->target_x = -1;
    }
    else if(m->target_x == -1 && world[(int)m->x - 1][(int)m->y][(int)m->z] != 0) {
        m->target_x = 1;
    }

    if(m->target_y == 1 && world[(int)m->x][(int)m->y + 1][(int)m->z] != 0) {
        m->target_y = -1;
    }
    else if(m->target_y == -1 && world[(int)m->x][(int)m->y - 1][(int)m->z] != 0) {
        m->target_y = 1;
    }

    if(m->target_z == 1 && world[(int)m->x][(int)m->y][(int)m->z + 1] != 0) {
        m->target_z = -1;
    }
    else if(m->target_z == -1 && world[(int)m->x][(int)m->y][(int)m->z - 1] != 0) {
        m->target_z = 1;
    }
}

void moveMeshMob(mob *m) {
    if(m->mob_type == 1) return;

    float player_x, player_y, player_z;
    getViewPosition(&player_x, &player_y, &player_z);
    player_x *= -1;
    player_y *= -1;
    player_z *= -1;
    
    int trans_x = 0, trans_z = 0;
    if((int)m->target_x > (int)m->x && world[(int)m->x + 1][(int)m->y][(int)m->z] == 0) {
        trans_x = 1;
    }
    else if((int)m->target_x < (int)m->x && world[(int)m->x - 1][(int)m->y][(int)m->z] == 0) {
        trans_x = -1;
    }
    if((int)m->target_z > (int)m->z) {
        if(trans_x > 0 && world[(int)m->x + 1][(int)m->y][(int)m->z + 1] == 0) trans_z = 1;
        else if(trans_x < 0 && world[(int)m->x - 1][(int)m->y][(int)m->z + 1] == 0) trans_z = 1;
        else if(trans_x ==  0 && world[(int)m->x][(int)m->y][(int)m->z + 1] == 0) trans_z = 1;
    }
    else if((int)m->target_z < (int)m->z) {
        if(trans_x > 0 && world[(int)m->x + 1][(int)m->y][(int)m->z - 1] == 0) trans_z = -1;
        else if(trans_x < 0 && world[(int)m->x - 1][(int)m->y][(int)m->z - 1] == 0) trans_z = -1;
        else if(trans_x ==  0 && world[(int)m->x][(int)m->y][(int)m->z - 1] == 0) trans_z = -1;
    }

    if((int)m->x + trans_x == (int)player_x && (int)m->z + trans_z == (int)player_z) {
        m->mob_state = MOB_ADJACENT;
        attackPlayer(m);
        return;
    }

    if(trans_x == 0 && trans_z == 0) {
        pickRandomTarget(m, 0);
    }

    translateMeshMob(m, m->x + trans_x, m->y, m->z + trans_z);
    drawMeshMob(*m);
}

void attackMob(mob *m) {
    int hit_chance = getRandom(0, 1);

    if(hit_chance == 1) {
        m->active = 0;
        printf("Mob has been hit\n");
    }
    else {
        printf("The player missed the mob\n");
    }
}

void attackPlayer(mob *m) {
    int hit_chance = getRandom(0, 1);

    if(hit_chance == 1) {
        printf("Player has been hit\n");
    }
    else {
        printf("The mob missed the player\n");
    }
}

void mobActivites() {
    if(player_turn == 1) return;

    float player_x, player_y, player_z;
    getViewPosition(&player_x, &player_y, &player_z);
    player_x *= -1;
    player_y *= -1;
    player_z *= -1;

    for(int i = 0; i < NUM_MOBS; i++) {
        if(mobs[i].active) {
            printf("Mob %d ", mobs[i].mesh_id);
            if(mobs[i].mob_state == MOB_ADJACENT) {
                attackPlayer(&mobs[i]);
                printf("attacked the player\n");
            }
            else if(mobs[i].mob_state == MOB_PLAYER_IN_VIEW) {
                mobs[i].target_x = player_x;
                mobs[i].target_z = player_z;
                moveMeshMob(&mobs[i]);
                printf("sees the player\n");
            }
            else if(mobs[i].mob_state == MOB_RANDOM_SEARCH) {
                if(((int)mobs[i].target_x == (int)player_x && (int)mobs[i].target_z == (int)player_z)|| ((int)mobs[i].target_x == (int)mobs[i].x && (int)mobs[i].target_z == (int)mobs[i].z)) pickRandomTarget(&mobs[i], 1);
                moveMeshMob(&mobs[i]);
                printf("is doing a random search\n");
            }
            else if(mobs[i].mob_state == MOB_WAITING) {
                if(mobs[i].mob_type == 1) {
                    mobs[i].target_x = mobs[i].x;
                    mobs[i].target_z = mobs[i].z;
                    printf("is waiting for the player by staying planted\n");
                }
                else if(mobs[i].mob_type == 3) {
                    if(((int)mobs[i].target_x == (int)player_x && (int)mobs[i].target_z == (int)player_z)|| ((int)mobs[i].target_x == (int)mobs[i].x && (int)mobs[i].target_z == (int)mobs[i].z)) pickRandomTarget(&mobs[i], 1);
                    moveMeshMob(&mobs[i]);
                    printf("is waiting for the player by wandering around to (%d, %d)\n", mobs[i].target_x, mobs[i].target_z);
                }
            }
        }
        drawMeshMob(mobs[i]);
    }

    player_turn = 1;
}

void pickRandomTarget(mob *m, int stay_in_room) {
    if(stay_in_room == 1) {
        int r = m->mesh_id;
        m->target_x = getRandom(rooms[r].start_x + 1, rooms[r].start_x + rooms[r].size_x - 1);
        m->target_z = getRandom(rooms[r].start_z + 1, rooms[r].start_z + rooms[r].size_z - 1);
    }
    else {
        int r = getRandom(0, NUM_ROOMS - 1);
        m->target_x = getRandom(rooms[r].start_x + 1, rooms[r].start_x + rooms[r].size_x - 2);
        m->target_z = getRandom(rooms[r].start_z + 1, rooms[r].start_z + rooms[r].size_z - 2);
    }
}