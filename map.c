#include "graphics.h"
#include "generation.h"
#include "map.h"

#define MINIMAP 2
#define FULLMAP 5

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
    GLfloat black[] = {0.0, 0.0, 0.0, 0.5};
    set2Dcolour(black);

    for(int i = 0; i < NUM_ROOMS; i++) {
        int x = rooms[i].start_x * MINIMAP;
        int z = rooms[i].start_z * MINIMAP;
        int l = (rooms[i].start_x + rooms[i].size_x) * MINIMAP;
        int w = (rooms[i].start_z + rooms[i].size_z) * MINIMAP;
        draw2Dbox(x, z, l, w);
    }
}

void drawDungeonWithFog() {
    GLfloat black[] = {0.0, 0.0, 0.0, 0.5};
    set2Dcolour(black);

    for(int i = 0; i < NUM_ROOMS; i++) {
        if(rooms[i].visited == 1) {
            int x = rooms[i].start_x * FULLMAP;
            int z = rooms[i].start_z * FULLMAP;
            int l = (rooms[i].start_x + rooms[i].size_x) * FULLMAP;
            int w = (rooms[i].start_z + rooms[i].size_z) * FULLMAP;
            draw2Dbox(x, z, l, w);
        }
    }
}

void drawViewpoint() {
    float x, y, z;
    getViewPosition(&x, &y, &z);
    x *= (-1)*MINIMAP;
    z *= (-1)*MINIMAP;

    GLfloat green[] = {0.0, 1.0, 0.0, 0.5};
    set2Dcolour(green);

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

    GLfloat green[] = {0.0, 1.0, 0.0, 0.5};
    set2Dcolour(green);

    int offset = FULLMAP + (FULLMAP / 2);
    
    int x_1 = x - offset;
    int z_1 = z - offset;
    int x_2 = x + offset;
    int z_2 = z - offset;
    int x_3 = x;
    int z_3 = z + offset;
    
    draw2Dtriangle(x_1, z_1, x_2, z_2, x_3, z_3);
}