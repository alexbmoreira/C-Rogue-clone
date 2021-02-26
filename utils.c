#include "utils.h"
#include "generation.h"
#include "mobs.h"
#include "graphics.h"


int getRandom(int min, int max) {
   int r = (rand() % (max + 1 - min)) + min;
   return r;
}


float roundFloat(float round_me) {
   round_me += 0.05;
   // float ten = 10;
   // float by_ten = round_me * 10;
   float rounded = roundf(round_me*10.0f)/10.0f;
   // float rounded = r_by_ten / ten;

   if(rounded <= 0.001 && rounded >= -0.001) {
      rounded += (rounded < 0) ? -0.1: 0.1;
   }

   return rounded;
}

void checkInRoom(int x, int z) {
   for(int i = 0; i < NUM_ROOMS; i++) {
      if(x > rooms[i].start_x && x < rooms[i].start_x + rooms[i].size_x && z > rooms[i].start_z && z < rooms[i].start_z + rooms[i].size_z) {
         rooms[i].visited = 1;
      }
   }
}

void checkInCorridor(int x, int z) {
   for(int i = 0; i < NUM_ROOMS * 10; i++) {
      if(x >= corridors[i].start_x && x <= corridors[i].end_x && z >= corridors[i].start_z && z <= corridors[i].end_z) {
         corridors[i].visited = 1;
      }
   }
}

void mobsInRoom() {
   for(int i = 0; i < NUM_ROOMS; i++) {
      for(int j = 0; j < NUM_MOBS; j++) {
         int x = (int)mobs[j].x;
         int z = (int)mobs[j].z;
         if(x > rooms[i].start_x && x < rooms[i].start_x + rooms[i].size_x && z > rooms[i].start_z && z < rooms[i].start_z + rooms[i].size_z && rooms[i].visited == 1) {
            mobs[j].seen = 1;
         }
      }
   }
}

void checkMobCloseness(int x, int z) {
   for(int i = 0; i < NUM_MOBS; i++) {
      if(abs((int)mobs[i].x - x) < 20) {
         mobs[i].visible = 1;
      }
      else {
         mobs[i].visible = 0;
      }
      if(abs((int)mobs[i].z - z) < 20) {
         mobs[i].visible = 1;
      }
      else {
         mobs[i].visible = 0;
      }
   }
}