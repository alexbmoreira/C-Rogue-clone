#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define NUM_ROOMS 9

typedef struct room
{
    int start_x, start_z, size_x, size_z;
    int visited;

    int stair_x, stair_z;
    int stair_type;
} room;

typedef struct corridor
{
    int start_x, start_z, end_x, end_z;
    int visited;
} corridor;

room rooms[NUM_ROOMS];
corridor corridors[NUM_ROOMS * 10];

void fillRect(int start_x, int end_x, int start_z, int end_z, char tile);
void roomCorridors(int door_x, int door_z, int direction, int end, int section);
void makeDoors(int room_x, int corner_x, int room_z, int corner_z, int section, int doors[]);
void makeRooms(int section);
void perpCorridors(int x, int z);
void generateDungeon2D();
void generateDungeon();
void printDungeon();