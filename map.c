#include "graphics.h"
#include "generation.h"
#include "map.h"
#include "colors.h"

#define MINIMAP 3
#define MINIMAP_O (MINIMAP / 2)
#define FULLMAP 5
#define FULLMAP_O (FULLMAP / 2)

float MAP_PLAYER[4] = {1.0, 0.0, 0.0, 0.5};
float MAP_U_STAIR[4] = {1.0, 1.0, 1.0, 1};
float MAP_BLACK[4] = {0.2, 0.2, 0.2, 0.5};
float MAP_D_STAIR[4] = {0.5, 0.5, 0.5, 1};
float MAP_DG_FLOOR[4] = {0.28, 0.3, 0.36, 0.5};

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

void drawDungeon() {

    for(int i = 0; i < NUM_ROOMS; i++) {
        set2Dcolour(MAP_DG_FLOOR);
        int x = rooms[i].start_x * MINIMAP;
        int z = rooms[i].start_z * MINIMAP;
        int l = (rooms[i].start_x + rooms[i].size_x) * MINIMAP;
        int w = (rooms[i].start_z + rooms[i].size_z) * MINIMAP;
        draw2Dbox(x, z, l, w);
    }
}

void drawDungeonWithFog() {

    for(int i = 0; i < NUM_ROOMS; i++) {
        if(rooms[i].visited == 1) {
            if(rooms[i].stair_type >= 0) {
                set2Dcolour(rooms[i].stair_type == 1 ? MAP_U_STAIR : MAP_D_STAIR);
                int stair_x = rooms[i].stair_x * FULLMAP;
                int stair_z = rooms[i].stair_z * FULLMAP;
                draw2Dbox(stair_x - FULLMAP_O, stair_z - FULLMAP_O, stair_x + FULLMAP_O, stair_z + FULLMAP_O);
            }

            set2Dcolour(MAP_DG_FLOOR);
            int x = rooms[i].start_x * FULLMAP;
            int z = rooms[i].start_z * FULLMAP;
            int l = (rooms[i].start_x + rooms[i].size_x) * FULLMAP;
            int w = (rooms[i].start_z + rooms[i].size_z) * FULLMAP;
            draw2Dbox(x, z, l, w);
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
}

void drawWorldLarge() {
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDZ; j++) {
            if(world[i][0][j] == CLR_D_STAIR) {
                int x = i * FULLMAP;
                int z = j * FULLMAP;
                set2Dcolour(MAP_D_STAIR);
                draw2Dbox(x - FULLMAP_O, z - FULLMAP_O, x + FULLMAP_O, z + FULLMAP_O);
            }
        }
    }
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
    
    int x_1 = x - offset;
    int z_1 = z - offset;
    int x_2 = x + offset;
    int z_2 = z - offset;
    int x_3 = x;
    int z_3 = z + offset;
    
    draw2Dtriangle(x_1, z_1, x_2, z_2, x_3, z_3);
}