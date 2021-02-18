#include "graphics.h"
#include "generation.h"
#include "map.h"

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
        int x = rooms[i].start_x * 2;
        int z = rooms[i].start_z * 2;
        int l = (rooms[i].start_x + rooms[i].size_x) * 2;
        int w = (rooms[i].start_z + rooms[i].size_z) * 2;
        draw2Dbox(x, z, l, w);
    }
}

void drawDungeonWithFog() {
    GLfloat black[] = {0.0, 0.0, 0.0, 0.5};
    set2Dcolour(black);

    for(int i = 0; i < NUM_ROOMS; i++) {
        if(rooms[i].visited == 1) {
            int x = rooms[i].start_x;
            int z = rooms[i].start_z;
            int l = rooms[i].start_x + rooms[i].size_x;
            int w = rooms[i].start_z + rooms[i].size_z;
            draw2Dbox(x, z, l, w);
        }
    }
}

void drawViewpoint() {
    float x, y, z;
    getViewPosition(&x, &y, &z);
    x *= -2;
    z *= -2;

    GLfloat green[] = {0.0, 1.0, 0.0, 0.5};
    set2Dcolour(green);
    
    int x_1 = x - 3;
    int z_1 = z - 3;
    int x_2 = x + 3;
    int z_2 = z - 3;
    int x_3 = x;
    int z_3 = z + 3;
    
    draw2Dtriangle(x_1, z_1, x_2, z_2, x_3, z_3);
}