#include "utils.h"
#include "generation.h"
#include "mobs.h"
#include "graphics.h"

extern void setViewPosition(float, float, float);
extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);
extern void setOldViewPosition(float, float, float);

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

void playerTurnElapsed() {
   float curr_x, curr_y, curr_z;
   float next_x, next_y, next_z;

   getOldViewPosition(&curr_x, &curr_y, &curr_z);
   getViewPosition(&next_x, &next_y, &next_z);

   int int_curr_x = (int)curr_x * (-1);
   int int_curr_y = (int)curr_y * (-1);
   int int_curr_z = (int)curr_z * (-1);

   int int_next_x = (int)next_x * (-1);
   int int_next_y = (int)next_y * (-1);
   int int_next_z = (int)next_z * (-1);

   if(int_next_x != int_curr_x || int_next_y != int_curr_y || int_next_z != int_curr_z) {
      printf("Turn elapsed; execute other turns here\n");
   }
}

void checkMobCollision() {
   float curr_x, curr_y, curr_z;
   float next_x, next_y, next_z;

   getOldViewPosition(&curr_x, &curr_y, &curr_z);
   getViewPosition(&next_x, &next_y, &next_z);

   int int_curr_x = (int)curr_x * (-1);
   int int_curr_y = (int)curr_y * (-1);
   int int_curr_z = (int)curr_z * (-1);

   int int_next_x = (int)next_x * (-1);
   int int_next_y = (int)next_y * (-1);
   int int_next_z = (int)next_z * (-1);

   int collision = 0;

   for(int i = 0; i < NUM_MOBS; i++) {
      if(mobs[i].active == 1){
         float goto_x = next_x;
         float goto_y = next_y;
         float goto_z = next_z;
         if(int_next_x == (int)mobs[i].x && int_next_z == (int)mobs[i].z) {
            goto_x = curr_x;
            goto_z = curr_z;
            collision = 1;
         }
         setViewPosition(goto_x, goto_y, goto_z);

         if(collision == 1) break;
      }
   }
}