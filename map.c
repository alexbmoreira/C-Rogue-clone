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
float MAP_DG_WALL[4] = {0.28, 0.34, 0.44, 1.0};

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

void drawDungeon() {

    drawWalls();

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
                int stair_x = rooms[r].stair_x * FULLMAP;
                int stair_z = rooms[r].stair_z * FULLMAP;
                draw2Dbox(stair_x - FULLMAP_O, stair_z - FULLMAP_O, stair_x + FULLMAP_O, stair_z + FULLMAP_O);
            }

            drawWallsLarge(r);
            
            int x = rooms[r].start_x * FULLMAP;
            int z = rooms[r].start_z * FULLMAP;
            int l = (rooms[r].start_x + rooms[r].size_x) * FULLMAP;
            int w = (rooms[r].start_z + rooms[r].size_z) * FULLMAP;

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
    int x = rooms[r].start_x * FULLMAP;
    int z = rooms[r].start_z * FULLMAP;
    int l = (rooms[r].start_x + rooms[r].size_x) * FULLMAP;
    int w = (rooms[r].start_z + rooms[r].size_z) * FULLMAP;

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
    set2Dcolour(MAP_DG_FLOOR);
    for(int c = 0; c < NUM_ROOMS * 10; c++) {
        // if(corridors[c].visited == 1) {
            int x = corridors[c].start_x * FULLMAP;
            int z = corridors[c].start_z * FULLMAP;
            int e_x = corridors[c].end_x * FULLMAP;
            int e_z = corridors[c].end_z * FULLMAP;
            // if(corridors[c].corridor_id != 0) printf("corridor %d at %d goes from (%d, %d) to (%d, %d)\n", corridors[c].corridor_id, c, x, z, e_x, e_z);
            if(corridors[c].corridor_id != 0) draw2Dbox(x - FULLMAP, z - FULLMAP, e_x + FULLMAP, e_z + FULLMAP);
        // }
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