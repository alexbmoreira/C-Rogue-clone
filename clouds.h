#include "graphics.h"
#include "utils.h"

#define NUM_CLOUDS 10

typedef struct cloud {
    int cloud_id;
    float x, y, z;
} cloud;

cloud clouds[NUM_CLOUDS];

void makeCloud(int cloud_id);

cloud getCloud(int cloud_id);

void drawCloud(int cloud_id);

void animateCloud(cloud cl);