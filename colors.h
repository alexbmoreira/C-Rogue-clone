#include "graphics.h"

#define CLR_U_STAIR 9
#define CLR_BLACK 10
#define CLR_D_STAIR 11
#define CLR_DG_WALL 12
#define CLR_DG_FLOOR 13
#define CLR_GRASS 14
#define CLR_DIRT 15
#define CLR_SNOW 16
#define CLR_CLOUDS 17

#ifdef DEFINE_MAP
float MAP_PLAYER[4] = {1.0, 0.0, 0.0, 1.0};
float MAP_MOB[4] = {0.0, 0.0, 0.0, 0.5};
float MAP_U_STAIR[4] = {1.0, 1.0, 1.0, 1.0};
float MAP_D_STAIR[4] = {0.5, 0.5, 0.5, 1.0};
float MAP_DG_FLOOR[4] = {0.28, 0.3, 0.36, 0.5};
float MAP_DG_WALL[4] = {0.28, 0.34, 0.44, 0.5};
float MAP_BORDER[4] = {1.0, 0.65, 0.0, 0.5};
#else
extern float MAP_PLAYER[4];
extern float MAP_MOB[4];
extern float MAP_U_STAIR[4];
extern float MAP_D_STAIR[4];
extern float MAP_DG_FLOOR[4];
extern float MAP_DG_WALL[4];
extern float MAP_BORDER[4];
#endif

#ifdef DEFINE_BLOCK
float BLOCK_WHITE[8] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
float BLOCK_BLACK[8] = {0.2, 0.2, 0.2, 1.0, 0.2, 0.2, 0.2, 1.0};
float BLOCK_GREY[8] = {0.5, 0.5, 0.5, 1.0, 0.25, 0.25, 0.25, 1.0};
float BLOCK_DUNGEONWALLS[8] = {0.28, 0.34, 0.44, 1.0, 0.14, 0.17, 0.22, 1.0};
float BLOCK_DUNGEONFLOORS[8] = {0.28, 0.3, 0.36, 1.0, 0.14, 0.15, 0.18, 1.0};
float BLOCK_GRASS[8] = {0.44, 0.72, 0.34, 1.0, 0.22, 0.36, 0.17, 1.0};
float BLOCK_DIRT[8] = {0.5, 0.36, 0.14, 1.0, 0.25, 0.23, 0.07, 1.0};
float BLOCK_SNOW[8] = {0.80, 0.76, 0.72, 1, 0.65, 0.62, 0.59, 1};
float BLOCK_CLOUDS[8] = {0.90, 0.90, 0.90, 0.5, 0.45, 0.45, 0.45, 0.5};
#else
extern float BLOCK_WHITE[8];
extern float BLOCK_BLACK[8];
extern float BLOCK_GREY[8];
extern float BLOCK_DUNGEONWALLS[8];
extern float BLOCK_DUNGEONFLOORS[8];
extern float BLOCK_GRASS[8];
extern float BLOCK_DIRT[8];
extern float BLOCK_SNOW[8];
extern float BLOCK_CLOUDS[8];
#endif