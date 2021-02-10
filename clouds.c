#include "clouds.h"

void makeCloud(int cloud_id) {
    cloud cl;
    cl.cloud_id = cloud_id;

    cl.x = getRandom(20, WORLDX - 20);
    cl.y = getRandom(45, WORLDY - 1);
    cl.z = getRandom(20, WORLDZ - 20);

    clouds[cloud_id] = cl;

    drawCloud(cloud_id);
}

cloud getCloud(int cloud_id) {
    return clouds[cloud_id];
}

void drawCloud(int cloud_id) {
    cloud cl = getCloud(cloud_id);

    world[(int)cl.x - 2][(int)cl.y][(int)cl.z] = 8;

    world[(int)cl.x - 1][(int)cl.y][(int)cl.z - 1] = 8;
    world[(int)cl.x - 1][(int)cl.y][(int)cl.z] = 8;
    world[(int)cl.x - 1][(int)cl.y][(int)cl.z + 1] = 8;
    world[(int)cl.x - 1][(int)cl.y][(int)cl.z + 2] = 8;

    world[(int)cl.x][(int)cl.y][(int)cl.z - 2] = 8;
    world[(int)cl.x][(int)cl.y][(int)cl.z - 1] = 8;
    world[(int)cl.x][(int)cl.y][(int)cl.z] = 8;
    world[(int)cl.x][(int)cl.y][(int)cl.z + 1] = 8;
    world[(int)cl.x][(int)cl.y][(int)cl.z + 2] = 8;
    world[(int)cl.x][(int)cl.y][(int)cl.z + 3] = 8;
    
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z - 2] = 8;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z - 1] = 8;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z] = 8;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z + 1] = 8;
    world[(int)cl.x + 1][(int)cl.y][(int)cl.z + 2] = 8;
    
    world[(int)cl.x + 2][(int)cl.y][(int)cl.z - 1] = 8;
    world[(int)cl.x + 2][(int)cl.y][(int)cl.z] = 8;
}

void animateCloud(cloud cl) {
    cl.x += 0.2;

    if((int)cl.x + 2 >= WORLDX - 1) {
        cl.x = 3;
    }

    drawCloud(cl.cloud_id);
}