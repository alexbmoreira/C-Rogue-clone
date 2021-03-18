#include "utils.h"
#include "generation.h"
#include "mobs.h"
#include "graphics.h"

extern void setViewPosition(float, float, float);
extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);
extern void setOldViewPosition(float, float, float);

int player_turn = 1;

int mobIsAdjacent(int int_next_x, int int_next_z, mob m);

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
   for(int m = 0; m < NUM_MOBS; m++) {
      int x = (int)mobs[m].x;
      int z = (int)mobs[m].z;
      for(int r = 0; r < NUM_ROOMS; r++) {
         if(x > rooms[r].start_x && x < rooms[r].start_x + rooms[r].size_x && z > rooms[r].start_z && z < rooms[r].start_z + rooms[r].size_z && rooms[r].visited == 1) {
            mobs[m].seen = 1;
         }
      }
      for(int c = 0; c < NUM_ROOMS * 10; c++) {
         if(x >= corridors[c].start_x && x <= corridors[c].end_x && z >= corridors[c].start_z && z <= corridors[c].end_z && corridors[c].visited == 1) {
            mobs[m].seen = 1;
         }
      }
   }
}

void playerInMobView() {
   float x, y, z;
   getViewPosition(&x, &y, &z);

   x *= -1;
   y *= -1;
   z *= -1;

   // printf("(%0.2f, %0.2f, %0.2f)\n", x, y, z);
   
   for(int i = 0; i < NUM_MOBS; i++) {
      if(mobs[i].active == 1) {
         if(mobs[i].mob_type == 2 || mobs[i].mob_type == 3) {
            if(mobs[i].mob_state != MOB_PLAYER_IN_VIEW && mobs[i].mob_state != MOB_ADJACENT && mobs[i].mob_type != 2) {
               for(int j = 0; j < NUM_ROOMS; j++) {
                  int mob_x = (int)mobs[i].x;
                  int mob_z = (int)mobs[i].z;
                  if(mob_x > rooms[j].start_x && mob_x < rooms[j].start_x + rooms[j].size_x && mob_z > rooms[j].start_z && mob_z < rooms[j].start_z + rooms[j].size_z) {
                     if(x > rooms[j].start_x && x < rooms[j].start_x + rooms[j].size_x && z > rooms[j].start_z && z < rooms[j].start_z + rooms[j].size_z) {
                        mobs[i].mob_state = MOB_PLAYER_IN_VIEW;
                     }
                     else {
                        mobs[i].mob_state = MOB_WAITING;
                        if(mobs[i].mob_type == 2) mobs[i].mob_state = MOB_RANDOM_SEARCH;
                     }
                  }
               }
            }
            else {
               if(fabs((int)mobs[i].x - x) < 20 && fabs((int)mobs[i].z - z) < 20 && !mobIsAdjacent((int)x, (int)z, mobs[i])) {
                  mobs[i].mob_state = MOB_PLAYER_IN_VIEW;
               }
               else if((fabs((int)mobs[i].x - x) >= 20 || fabs((int)mobs[i].z - z) >= 20)) {
                  mobs[i].mob_state = MOB_WAITING;
                  if(mobs[i].mob_type == 2) mobs[i].mob_state = MOB_RANDOM_SEARCH;
               }
            }
         }
      }
   }
}

void checkMobCloseness(int x, int z) {
   for(int i = 0; i < NUM_MOBS; i++) {
      if(abs((int)mobs[i].x - x) < 30 && abs((int)mobs[i].z - z) < 30) {
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
      player_turn = 0;
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
      if(mobs[i].active == 1) {
         if(mobIsAdjacent(int_next_x, int_next_z, mobs[i])) {
            mobs[i].mob_state = MOB_ADJACENT;
         }
         else {
            float goto_x = next_x;
            float goto_y = next_y;
            float goto_z = next_z;

            if(int_next_x == (int)mobs[i].x && int_next_z == (int)mobs[i].z) {
               goto_x = curr_x;
               goto_z = curr_z;
               attackMob(&mobs[i]);
               collision = 1;
               player_turn = 0;
               mobs[i].mob_state = MOB_ADJACENT;
            }
            setViewPosition(goto_x, goto_y, goto_z);

            if(collision == 1) break;
         }
      }
   }
}

int mobIsAdjacent(int int_next_x, int int_next_z, mob m) {

   if(int_next_x == (int)m.x - 1 && int_next_z == (int)m.z) return 1;
   if(int_next_x == (int)m.x - 1 && int_next_z == (int)m.z - 1) return 1;
   if(int_next_x == (int)m.x - 1 && int_next_z == (int)m.z + 1) return 1;
   
   if(int_next_x == (int)m.x + 1 && int_next_z == (int)m.z) return 1;
   if(int_next_x == (int)m.x + 1 && int_next_z == (int)m.z - 1) return 1;
   if(int_next_x == (int)m.x + 1 && int_next_z == (int)m.z + 1) return 1;

   if(int_next_x == (int)m.x && int_next_z == (int)m.z - 1) return 1;
   if(int_next_x == (int)m.x && int_next_z == (int)m.z + 1) return 1;

   return 0;
}