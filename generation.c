#include "generation.h"
#include "graphics.h"
#include "utils.h"

void createRooms(int section) {
   int sec_X = 0;
   int sec_Z = 0;

   switch (section)
   {
      case 1:
         sec_X = (WORLDX / 3);
         sec_Z = (WORLDZ / 3);
         break;
      case 2:
         sec_X = 2 * (WORLDX / 3);
         sec_Z = (WORLDZ / 3);
         break;
      case 3:
         sec_X = 3 * (WORLDX / 3);
         sec_Z = (WORLDZ / 3);
         break;
      case 4:
         sec_X = (WORLDX / 3);
         sec_Z = 2 * (WORLDZ / 3);
         break;
      case 5:
         sec_X = 2 * (WORLDX / 3);
         sec_Z = 2 * (WORLDZ / 3);
         break;
      case 6:
         sec_X = 3 * (WORLDX / 3);
         sec_Z = 2 * (WORLDZ / 3);
         break;
      case 7:
         sec_X = (WORLDX / 3);
         sec_Z = 3 * (WORLDZ / 3);
         break;
      case 8:
         sec_X = 2 * (WORLDX / 3);
         sec_Z = 3 * (WORLDZ / 3);
         break;
      case 9:
         sec_X = 3 * (WORLDX / 3);
         sec_Z = 3 * (WORLDZ / 3);
         break;
      default:
         return;
         break;
   }

   // for(int i = sec_X - (WORLDX / 3); i <= sec_X; i++) {
   //    for(int j = sec_Z - (WORLDZ / 3); j <= sec_Z; j++) {
   //       world[i][30][j] = section;
   //    }
   // }
   
   int room_X = getRandom(5, (WORLDX / 3) - 6);
   int room_Z = getRandom(5, (WORLDZ / 3) - 6);
   int corner_X = getRandom(sec_X - (WORLDX / 3) + 2, sec_X - 2 - room_X);
   int corner_Z = getRandom(sec_Z - (WORLDZ / 3) + 2, sec_Z - 2 - room_Z);

   for(int i = corner_X; i <= corner_X + room_X; i++) {
      world[i][31][corner_Z] = 6;
      world[i][31][corner_Z + room_Z] = 6;
   }
   for(int j = corner_Z; j <= corner_Z + room_Z; j++) {
      world[corner_X][31][j] = 6;
      world[corner_X + room_X][31][j] = 6;
   }

   // printf("Section %d\n", section);
   // printf("Section spot: (%d, %d)\n", sec_X, sec_Z);
   // printf("Room size: %d x %d\n", room_X, room_Z);
   // printf("Corner coords: (%d, %d)\n\n", corner_X, corner_Z);
}