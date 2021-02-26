#include "graphics.h"
#include "generation.h"
#include "map.h"
#define DEFINE_MAP
#include "colors.h"
#include "mobs.h"


int MINIMAP = 2;
int MINIMAP_O = 2;
int FULLMAP = 5;
int FULLMAP_O = 5;

int FULLMAP_X = 262;
int FULLMAP_Z = 134;

	/* size of the window in pixels */
extern int screenWidth, screenHeight;

extern void draw2Dline(int, int, int, int, int);
extern void draw2Dbox(int, int, int, int);
extern void draw2Dtriangle(int, int, int, int, int, int);
extern void set2Dcolour(float []);

extern void setViewPosition(float, float, float);
extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);
extern void setOldViewPosition(float, float, float);
extern void setViewOrientation(float, float, float);
extern void getViewOrientation(float *, float *, float *);

extern char maze[WORLDX][WORLDZ];

void drawMinimap(int state) {

    MINIMAP = (screenWidth / 512 > 0) ? screenWidth / 512 : 1;
    MINIMAP_O = (screenWidth / 512 > 0) ? screenWidth / 512 : 1;

    drawViewpoint();
    if(state > 0) {
        drawDungeon();
    }
    else {
        drawWorld();
    }
}

void drawFullmap(int state) {

    FULLMAP = (screenWidth / 206 > 0) ? screenWidth / 206 : 1;
    FULLMAP_O = (screenWidth / 206 > 0) ? screenWidth / 206 : 1;

    FULLMAP_X = (screenWidth - (FULLMAP * WORLDX)) / 2;
    FULLMAP_Z = (screenHeight - (FULLMAP * WORLDZ)) / 2;

    drawViewpointLarge();
    drawMobsLarge();
    if(state > 0) {
        drawDungeonWithFog();
    }
    else {
        drawWorldLarge();
    }
}

void drawDungeon() {

    // printf("Screen height: %d\nScreen width: %d\n", screenHeight, screenWidth);

    // drawWalls();

    drawHallways();

    for(int r = 0; r < NUM_ROOMS; r++) {
        set2Dcolour(MAP_DG_FLOOR);
        int x = rooms[r].start_x * MINIMAP;
        int z = rooms[r].start_z * MINIMAP;
        int l = (rooms[r].start_x + rooms[r].size_x) * MINIMAP;
        int w = (rooms[r].start_z + rooms[r].size_z) * MINIMAP;
        draw2Dbox(x, z, l, w);
    }
}

void drawDungeonWithFog() {

    for(int r = 0; r < NUM_ROOMS; r++) {
        if(rooms[r].visited == 1) {
            if(rooms[r].stair_type >= 0) {
                set2Dcolour(rooms[r].stair_type == 1 ? MAP_U_STAIR : MAP_D_STAIR);
                int stair_x = rooms[r].stair_x * FULLMAP + FULLMAP_X;
                int stair_z = rooms[r].stair_z * FULLMAP + FULLMAP_Z;
                draw2Dbox(stair_x - FULLMAP_O, stair_z - FULLMAP_O, stair_x + FULLMAP_O, stair_z + FULLMAP_O);
            }

            // drawWallsLarge(r);
            
            int x = rooms[r].start_x * FULLMAP + FULLMAP_X;
            int z = rooms[r].start_z * FULLMAP + FULLMAP_Z;
            int l = (rooms[r].start_x + rooms[r].size_x) * FULLMAP + FULLMAP_X;
            int w = (rooms[r].start_z + rooms[r].size_z) * FULLMAP + FULLMAP_Z;

            drawHallwaysLarge();

            set2Dcolour(MAP_DG_FLOOR);
            draw2Dbox(x, z, l, w);
        }
    }
}

void drawWalls() {
    set2Dcolour(MAP_DG_WALL);
    
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDZ; j++) {
            if(world[i][31][j] == CLR_DG_WALL) {
                int x = i * MINIMAP;
                int z = j * MINIMAP;
                if(world[i + 1][31][j] == CLR_DG_WALL) {
                    draw2Dline(x, z, x + MINIMAP, z, MINIMAP);
                }
                if(world[i][31][j + 1] == CLR_DG_WALL) {
                    draw2Dline(x, z, x, z + MINIMAP, MINIMAP);
                }
            }
        }
    }
}

void drawWallsLarge(int r) {
    int x = rooms[r].start_x * FULLMAP + FULLMAP_X;
    int z = rooms[r].start_z * FULLMAP + FULLMAP_Z;
    int l = (rooms[r].start_x + rooms[r].size_x) * FULLMAP + FULLMAP_X;
    int w = (rooms[r].start_z + rooms[r].size_z) * FULLMAP + FULLMAP_Z;

    int door_1 = 0, door_2 = 0, door_3 = 0, door_4 = 0;

    set2Dcolour(MAP_DG_WALL);
    for(int i = x / FULLMAP; i < l / FULLMAP; i++) {
        if(maze[i][z / FULLMAP] == 'D') {
            draw2Dline(x, z, (i * FULLMAP) - FULLMAP, z, FULLMAP);
            draw2Dline((i * FULLMAP) + FULLMAP, z, l, z, FULLMAP);
            door_1 = 1;
        }
        if(maze[i][w / FULLMAP] == 'D') {
            draw2Dline(x, w, (i * FULLMAP) - FULLMAP, w, FULLMAP);
            draw2Dline((i * FULLMAP) + FULLMAP, w, l, w, FULLMAP);
            door_2 = 1;
        }
    }
    for(int j = z / FULLMAP; j < w / FULLMAP; j++) {
        if(maze[x / FULLMAP][j] == 'D') {
            draw2Dline(x, z, x, (j * FULLMAP) - FULLMAP, FULLMAP);
            draw2Dline(x, (j * FULLMAP) + FULLMAP, x, w, FULLMAP);
            door_3 = 1;
        }
        if(maze[l / FULLMAP][j] == 'D') {
            draw2Dline(l, z, l, (j * FULLMAP) - FULLMAP, FULLMAP);
            draw2Dline(l, (j * FULLMAP) + FULLMAP, l, w, FULLMAP);
            door_4 = 1;
        }
    }

    if(door_1 == 0) draw2Dline(x, z, l, z, FULLMAP);
    if(door_2 == 0) draw2Dline(x, w, l, w, FULLMAP);
    if(door_3 == 0) draw2Dline(x, z, x, w, FULLMAP);
    if(door_4 == 0) draw2Dline(l, z, l, w, FULLMAP);
}

void drawHallways() {
    set2Dcolour(MAP_DG_FLOOR);
    for(int c = 0; c < NUM_ROOMS * 10; c++) {
        int x = corridors[c].start_x * MINIMAP;
        int z = corridors[c].start_z * MINIMAP;
        int e_x = corridors[c].end_x * MINIMAP;
        int e_z = corridors[c].end_z * MINIMAP;
        if(corridors[c].corridor_id != 0) draw2Dbox(x - MINIMAP, z - MINIMAP, e_x + MINIMAP, e_z + MINIMAP);
    }
}

void drawHallwaysLarge() {
    for(int c = 0; c < NUM_ROOMS * 10; c++) {
        if(corridors[c].visited == 1) {
            int x = corridors[c].start_x * FULLMAP + FULLMAP_X;
            int z = corridors[c].start_z * FULLMAP + FULLMAP_Z;
            int e_x = corridors[c].end_x * FULLMAP + FULLMAP_X;
            int e_z = corridors[c].end_z * FULLMAP + FULLMAP_Z;
            if(corridors[c].corridor_id != 0) {
                // set2Dcolour(MAP_DG_WALL);
                // if(x == e_x) {
                //     draw2Dline(x - FULLMAP, z - FULLMAP, e_x - FULLMAP, e_z - FULLMAP, FULLMAP);
                //     draw2Dline(x + FULLMAP, z - FULLMAP, e_x + FULLMAP, e_z - FULLMAP, FULLMAP);
                // }
                // else if (z == e_z) {
                //     draw2Dline(x - FULLMAP, z - FULLMAP, e_x - FULLMAP, e_z - FULLMAP, FULLMAP);
                //     draw2Dline(x - FULLMAP, z + FULLMAP, e_x - FULLMAP, e_z + FULLMAP, FULLMAP);
                // }
                set2Dcolour(MAP_DG_FLOOR);
                draw2Dbox(x - FULLMAP, z - FULLMAP, e_x + FULLMAP, e_z + FULLMAP);
            }
        }
    }
}

void drawWorld() {
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDZ; j++) {
            if(world[i][0][j] == CLR_D_STAIR) {
                int x = i * MINIMAP;
                int z = j * MINIMAP;
                set2Dcolour(MAP_D_STAIR);
                draw2Dbox(x - MINIMAP_O, z - MINIMAP_O, x + MINIMAP_O, z + MINIMAP_O);
            }
        }
    }
    draw2Dline(0, 0, WORLDX * MINIMAP, 0, MINIMAP);
    draw2Dline(WORLDX * MINIMAP, 0, WORLDX * MINIMAP, WORLDZ * MINIMAP, MINIMAP);
    draw2Dline(WORLDX * MINIMAP, WORLDZ * MINIMAP, 0, WORLDZ * MINIMAP, MINIMAP);
    draw2Dline(0, WORLDZ * MINIMAP, 0, 0, MINIMAP);
}

void drawWorldLarge() {
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDZ; j++) {
            if(world[i][0][j] == CLR_D_STAIR) {
                int x = i * FULLMAP + FULLMAP_X;
                int z = j * FULLMAP + FULLMAP_Z;
                set2Dcolour(MAP_D_STAIR);
                draw2Dbox(x - FULLMAP_O, z - FULLMAP_O, x + FULLMAP_O, z + FULLMAP_O);
            }
        }
    }

    draw2Dline(0 + FULLMAP_X, 0 + FULLMAP_Z, (WORLDX * FULLMAP) + FULLMAP_X, 0 + FULLMAP_Z, FULLMAP);
    draw2Dline((WORLDX * FULLMAP) + FULLMAP_X, 0 + FULLMAP_Z, (WORLDX * FULLMAP) + FULLMAP_X, (WORLDZ * FULLMAP) + FULLMAP_Z, FULLMAP);
    draw2Dline((WORLDX * FULLMAP) + FULLMAP_X, (WORLDZ * FULLMAP) + FULLMAP_Z, 0 + FULLMAP_X, (WORLDZ * FULLMAP) + FULLMAP_Z, FULLMAP);
    draw2Dline(0 + FULLMAP_X, (WORLDZ * FULLMAP) + FULLMAP_Z, 0 + FULLMAP_X, 0 + FULLMAP_Z, FULLMAP);
}

void drawViewpoint() {
    float x, y, z;
    getViewPosition(&x, &y, &z);
    x *= (-1)*MINIMAP;
    z *= (-1)*MINIMAP;

    set2Dcolour(MAP_PLAYER);

    int offset = MINIMAP + (MINIMAP / 2);
    
    int x_1 = x - offset;
    int z_1 = z - offset;
    int x_2 = x + offset;
    int z_2 = z - offset;
    int x_3 = x;
    int z_3 = z + offset;
    
    draw2Dtriangle(x_1, z_1, x_2, z_2, x_3, z_3);
}

void drawViewpointLarge() {
    float x, y, z;
    getViewPosition(&x, &y, &z);
    x *= (-1)*FULLMAP;
    z *= (-1)*FULLMAP;

    set2Dcolour(MAP_PLAYER);

    int offset = FULLMAP + (FULLMAP / 2);
    
    int x_1 = x - offset + FULLMAP_X;
    int z_1 = z - offset + FULLMAP_Z;
    int x_2 = x + offset + FULLMAP_X;
    int z_2 = z - offset + FULLMAP_Z;
    int x_3 = x + FULLMAP_X;
    int z_3 = z + offset + FULLMAP_Z;
    
    draw2Dtriangle(x_1, z_1, x_2, z_2, x_3, z_3);
}

void drawMobsLarge() {
    set2Dcolour(MAP_PLAYER);
    for(int m = 0; m < NUM_MOBS; m++) {
        if(mobs[m].seen == 1) {
            int x = mobs[m].x * FULLMAP + FULLMAP_X;
            int z = mobs[m].z * FULLMAP + FULLMAP_Z;
            draw2Dcircle(x, z, FULLMAP_O);
            // draw2Dbox(x - FULLMAP_O, z - FULLMAP_O, x + FULLMAP_O, z + FULLMAP_O);
        }
    }
}

void draw2Dcircle(int x, int z, int r) {
    draw2Dtriangle(
        x, z,
        x + r, z,
        x + (r * 2/3), z + (r / 3)
    );
    draw2Dtriangle(
        x, z,
        x + (r * 2/3), z + (r / 3),
        x, z + r
    );
    draw2Dtriangle(
        x, z,
        x, z + r,
        x - (r / 3), z + (r * 2/3)
    );
    draw2Dtriangle(
        x, z,
        x - (r / 3), z + (r * 2/3),
        x - r, z
    );
    draw2Dtriangle(
        x, z,
        x - r, z,
        x - (r * 2/3), z - (r / 3)
    );
    draw2Dtriangle(
        x, z,
        x - (r * 2/3), z - (r / 3),
        x, z - r
    );
    draw2Dtriangle(
        x, z,
        x, z - r,
        x + (r / 3), z - (r * 2/3)
    );
    draw2Dtriangle(
        x, z,
        x + (r / 3), z - (r * 2/3),
        x + r, z
    );
}