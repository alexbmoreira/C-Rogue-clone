#include "clouds.h"
#include "colors.h"

void makeCloud(int cloud_id) {
    cloud cl;
    cl.cloud_id = cloud_id;

    cl.x = getRandom(20, WORLDX - 20);
    cl.y = getRandom(45, WORLDY - 1);
    cl.z = getRandom(20, WORLDZ - 20);

    clouds[cloud_id] = cl;

    drawCloud(cl);
}

cloud getCloud(int cloud_id) {
    return clouds[cloud_id];
}

void drawCloud(cloud cl) {
    world[(int)cl.x - 2][(int)cl.y][(int)cl.z] = CLR_CLOUDS;

    world[(int)cl.x - 1][(int)cl.y][(int)cl.z - 1] = CLR_CLOUDS;
    world[(int)cl.x - 1][(int)cl.y][(int)cl.z] = CLR_CLOUDS;
    world[(int)cl.x - 1][(int)cl.y][(int)cl.z + 1] = CLR_CLOUDS;
    world[(int)cl.x - 1][(int)cl.y][(int)cl.z + 2] = CLR_CLOUDS;

    world[(int)cl.x][(int)cl.y][(int)cl.z - 2] = CLR_CLOUDS;
    world[(int)cl.x][(int)cl.y][(int)cl.z - 1] = CLR_CLOUDS;
    world[(int)cl.x][(int)cl.y][(int)cl.z] = CLR_CLOUDS;
    world[(int)cl.x][(int)cl.y][(int)cl.z + 1] = CLR_CLOUDS;
    world[(int)cl.x][(int)cl.y][(int)cl.z + 2] = CLR_CLOUDS;
    world[(int)cl.x][(int)cl.y][(int)cl.z + 3] = CLR_CLOUDS;
    
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z - 2] = CLR_CLOUDS;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z - 1] = CLR_CLOUDS;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z] = CLR_CLOUDS;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z + 1] = CLR_CLOUDS;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z + 2] = CLR_CLOUDS;
    
    world[(int)cl.x + 2][(int)cl.y][(int)cl.z - 1] = CLR_CLOUDS;
    world[(int)cl.x + 2][(int)cl.y][(int)cl.z] = CLR_CLOUDS;
}

void clearCloud(cloud cl) {
    world[(int)cl.x - 2][(int)cl.y][(int)cl.z] = 0;

    world[(int)cl.x - 1][(int)cl.y][(int)cl.z - 1] = 0;
    world[(int)cl.x - 1][(int)cl.y][(int)cl.z] = 0;
    world[(int)cl.x - 1][(int)cl.y][(int)cl.z + 1] = 0;
    world[(int)cl.x - 1][(int)cl.y][(int)cl.z + 2] = 0;

    world[(int)cl.x][(int)cl.y][(int)cl.z - 2] = 0;
    world[(int)cl.x][(int)cl.y][(int)cl.z - 1] = 0;
    world[(int)cl.x][(int)cl.y][(int)cl.z] = 0;
    world[(int)cl.x][(int)cl.y][(int)cl.z + 1] = 0;
    world[(int)cl.x][(int)cl.y][(int)cl.z + 2] = 0;
    world[(int)cl.x][(int)cl.y][(int)cl.z + 3] = 0;
    
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z - 2] = 0;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z - 1] = 0;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z] = 0;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z + 1] = 0;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z + 2] = 0;
    
    world[(int)cl.x + 2][(int)cl.y][(int)cl.z - 1] = 0;
    world[(int)cl.x + 2][(int)cl.y][(int)cl.z] = 0;
}

void animateCloud(cloud *cl) {
    clearCloud(*cl);

    float movement = getRandom(0, 8) / 100.0f;

    cl->x += movement;

    if((int)cl->x + 2 >= WORLDX - 1) {
        cl->x = 3;
    }

    clouds[cl->cloud_id] = *cl;
    drawCloud(*cl);
}