#include "animation.h"
#include "clouds.h"

void runAnimations() {
    long int current_time = time(NULL);

    if(current_time - last_cloud_anim >= CLOUD_ANIM_TIME) {
      for(int i = 0; i < NUM_CLOUDS - 1; i++) {
         cloud cl = getCloud(i);
         animateCloud(&cl);
      }
      last_cloud_anim = current_time;
    }
}