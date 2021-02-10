#include "graphics.h"
#include "utils.h"

typedef struct cloud {
    int cloud_id;
    float x, y, z;
} cloud;

cloud clouds[100];

void makeCloud(int cloud_id);

cloud getCloud(int cloud_id);

void drawCloud(int cloud_id);

void animateCloud(cloud cl);