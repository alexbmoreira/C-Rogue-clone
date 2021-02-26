#include "animation.h"
#include "clouds.h"
#include "mobs.h"

void runAnimations() {
    // long int current_time = time(NULL);
    clock_t current_time = clock() / (CLOCKS_PER_SEC / 1000);

    // printf("time: %ld\n", current_time);
    // printf("clock time: %ld\n", uptime);

    if(current_time - last_cloud_anim >= CLOUD_ANIM_TIME) {
      for(int i = 0; i < NUM_CLOUDS - 1; i++) {
         cloud cl = getCloud(i);
         animateCloud(&cl);
      }
      last_cloud_anim = current_time;
    }

    if(current_time - last_mob_anim >= MOB_ANIM_TIME) {
      for(int i = 0; i < NUM_MOBS; i++) {
         moveMeshMob(&mobs[i]);
      }
      last_mob_anim = current_time;
    }
}