#include "generation.h"
#include "graphics.h"
#include "utils.h"
#include "colors.h"

char maze[WORLDX][WORLDZ];
int d_room;

extern void setViewPosition(float, float, float);
extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);
extern void setOldViewPosition(float, float, float);

void clearCorridorsArray() {
    for(int c = 1; c < NUM_ROOMS * 10; c++) {
        corridors[c].start_x = 0;
        corridors[c].start_z = 0;
        corridors[c].end_x = 0;
        corridors[c].end_z = 0;
        corridors[c].corridor_id = 0;
        corridors[c].visited = 0;
    }
}

void fillRect(int start_x, int end_x, int start_z, int end_z, char tile) {
    for (int i = start_x; i < end_x; i++) {
        for (int j = start_z; j < end_z; j++) {
            maze[i][j] = tile;
        }
    }
}

void roomCorridors(int door_x, int door_z, int direction, int end) {

    corridor corr;
    corr.visited = 0;

    if(direction == 0) { // Left
        int distance = end;
        for(int j = door_z - 1; j >= distance; j--) {
            maze[door_x][j] = '.';
        }
        corr.start_x = door_x;
        corr.start_z = distance;
        corr.end_x = door_x;
        corr.end_z = door_z - 1;
    }
    else if(direction == 1) { // Right
        int distance = end;
        for(int j = door_z + 1; j <= distance; j++) {
            maze[door_x][j] = '.';
        }
        corr.start_x = door_x;
        corr.start_z = door_z + 1;
        corr.end_x = door_x;
        corr.end_z = distance;
    }
    else if(direction == 2) { // Up
        int distance = end;
        for(int i = door_x - 1; i >= distance; i--) {
            maze[i][door_z] = '.';
        }
        corr.start_x = distance;
        corr.start_z = door_z;
        corr.end_x = door_x - 1;
        corr.end_z = door_z;
    }
    else if(direction == 3) { // Down
        int distance = end;
        for(int i = door_x + 1; i <= distance; i++) {
            maze[i][door_z] = '.';
        }
        corr.start_x = door_x + 1;
        corr.start_z = door_z;
        corr.end_x = distance;
        corr.end_z = door_z;
    }

    for(int c = 1; c < NUM_ROOMS * 10; c++) {
        if(corridors[c].start_x == corr.start_x && corridors[c].start_z == corr.start_z && corridors[c].end_x == corr.end_x && corridors[c].end_z == corr.end_z) break;
        if(corridors[c].corridor_id == 0) {
            corr.corridor_id = c;
            corridors[c] = corr;
            break;
        }
    }
}

void makeDoors(int room_x, int corner_x, int room_z, int corner_z, int section, int doors[]) {

    /*
    doors[0] => left door
    doors[1] => right door
    doors[2] => top door
    doors[3] => bottom door
    */

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

    if(section != 3 && section != 6 && section != 9) {
        maze[corner_x + room_x][doors[3]] = 'D';
        roomCorridors(corner_x + room_x, doors[3], 3, sec_X);
    }
    if(section != 1 && section != 4 && section != 7) {
        maze[corner_x][doors[2]] = 'D';
        roomCorridors(corner_x, doors[2], 2, sec_X - (WORLDX / 3));
    }
    if(section != 7 && section != 8 && section != 9) {
        maze[doors[1]][corner_z + room_z] = 'D';
        roomCorridors(doors[1], corner_z + room_z, 1, sec_Z);
    }
    if(section != 1 && section != 2 && section != 3) {
        maze[doors[0]][corner_z] = 'D';
        roomCorridors(doors[0], corner_z, 0, sec_Z - (WORLDZ / 3));
    }
}

void makeRooms(int section) {
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
   
    int room_x = getRandom(5, (WORLDX / 3) - 6);
    int room_z = getRandom(5, (WORLDZ / 3) - 6);
    int corner_x = getRandom(sec_X - (WORLDX / 3) + 2, sec_X - 2 - room_x);
    int corner_z = getRandom(sec_Z - (WORLDZ / 3) + 2, sec_Z - 2 - room_z);

    int doors[4] = {
        getRandom(corner_x + 1, corner_x + room_x - 1),
        getRandom(corner_x + 1, corner_x + room_x - 1),
        getRandom(corner_z + 1, corner_z + room_z - 1),
        getRandom(corner_z + 1, corner_z + room_z - 1)
        };

    for(int i = corner_x; i <= corner_x + room_x; i++) {
        maze[i][corner_z] = 'W';
        maze[i][corner_z + room_z] = 'W';

        makeDoors(room_x, corner_x, room_z, corner_z, section, doors);
    }
    for(int j = corner_z; j <= corner_z + room_z; j++) {
        maze[corner_x][j] = 'W';
        maze[corner_x + room_x][j] = 'W';

        makeDoors(room_x, corner_x, room_z, corner_z, section, doors);
    }

    room new_room;
    new_room.stair_type = -1;

    if(section == 1) {
        maze[corner_x + (room_x / 2)][corner_z + (room_z / 2)] = 'S';
        maze[corner_x + 1][corner_z + 1] = 'u';
        new_room.stair_x = corner_x + 1;
        new_room.stair_z = corner_z + 1;
        new_room.stair_type = 1;
    }
    else if(section == d_room) {
        int x_placement = getRandom(room_x / 4, room_x * 3 /4);
        int z_placement = getRandom(room_z / 4, room_z * 3 /4);
        maze[corner_x + x_placement][corner_z + z_placement] = 'd';
        new_room.stair_x = corner_x + x_placement;
        new_room.stair_z = corner_z + z_placement;
        new_room.stair_type = 0;
    }

    new_room.start_x = corner_x;
    new_room.start_z = corner_z;
    new_room.size_x = room_x;
    new_room.size_z = room_z;
    new_room.visited = 0;
    rooms[section - 1] = new_room;
}

void perpCorridors(int x, int z) {
    int print_corr = 0;
    corridor corr;
    corr.visited = 0;
    for (int i = 0; i < WORLDX; i++) {
        if(maze[i][z] == '.' && !(maze[i][z - 1] == '.' && maze[i][z + 1] == '.')) {
            // print_corr = (print_corr == 0) ? 1 : 0;
            if(print_corr == 0) {
                print_corr = 1;
                corr.start_x = i;
                corr.start_z = z;
            }
            else {
                print_corr = 0;
                corr.end_x = i;
                corr.end_z = z;

                for(int c = 1; c < NUM_ROOMS * 10; c++) {
                    if(corridors[c].start_x == corr.start_x && corridors[c].start_z == corr.start_z && corridors[c].end_x == corr.end_x && corridors[c].end_z == corr.end_z) break;
                    if(corridors[c].corridor_id == 0) {
                        corr.corridor_id = c;
                        corridors[c] = corr;
                        break;
                    }
                }
            }
        }

        if(print_corr == 1) {
            maze[i][z] = '.';
        }
    }

    print_corr = 0;
    corr.visited = 0;
    for (int j = 0; j < WORLDZ; j++) {
        if(maze[x][j] == '.' && !(maze[x - 1][j] == '.' && maze[x + 1][j] == '.')) {
            if(print_corr == 0) {
                print_corr = 1;
                corr.start_x = x;
                corr.start_z = j;
            }
            else {
                print_corr = 0;
                corr.end_x = x;
                corr.end_z = j;

                for(int c = 1; c < NUM_ROOMS * 10; c++) {
                    if(corridors[c].start_x == corr.start_x && corridors[c].start_z == corr.start_z && corridors[c].end_x == corr.end_x && corridors[c].end_z == corr.end_z) break;
                    if(corridors[c].corridor_id == 0) {
                        corr.corridor_id = c;
                        corridors[c] = corr;
                        break;
                    }
                }
            }
        }

        if(print_corr == 1) {
            maze[x][j] = '.';
        }
    }
}

void generateDungeon2D() {
    srand(time(NULL));

    fillRect(0, WORLDX, 0, WORLDZ, ' ');

    d_room = getRandom(2, 9);

    for(int i = 1; i < 10; i++) {
        makeRooms(i);
    }
    perpCorridors((WORLDX / 3), (WORLDZ / 3));
    perpCorridors(2 * (WORLDX / 3), 2 * (WORLDZ / 3));
}

void generateDungeon() {
    clearCorridorsArray();

    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDZ; j++) {
            world[i][30][j] = CLR_DG_FLOOR;
            world[i][34][j] = CLR_DG_FLOOR;
        }
    }

    generateDungeon2D();

    for (int i = 0; i < WORLDX; i++) {
        for (int j = 0; j < WORLDZ; j++) {
            if(maze[i][j] == 'W') { // Create a wall
                world[i][31][j] = CLR_DG_WALL;
                world[i][32][j] = CLR_DG_WALL;
                world[i][33][j] = CLR_DG_WALL;
            }
            else if(maze[i][j] == 'd') { // Create a staircase down
                world[i][30][j] = CLR_D_STAIR;
            }
            else if(maze[i][j] == 'u') { // Create a staircase back up
                world[i][30][j] = CLR_U_STAIR;
            }
            else if(maze[i][j] == 'S') { // Set character spawn
                setOldViewPosition(i*(-1), 32.5*(-1), j*(-1));
            }
            else if(maze[i][j] == '.') { // Create a corridor
                // Check horizontals
                if(maze[i + 1][j] == ' ') {
                    world[i + 1][31][j] = CLR_DG_WALL;
                    world[i + 1][32][j] = CLR_DG_WALL;
                    world[i + 1][33][j] = CLR_DG_WALL;
                }
                if(maze[i - 1][j] == ' ') {
                    world[i - 1][31][j] = CLR_DG_WALL;
                    world[i - 1][32][j] = CLR_DG_WALL;
                    world[i - 1][33][j] = CLR_DG_WALL;
                }
                if(maze[i][j + 1] == ' ') {
                    world[i][31][j + 1] = CLR_DG_WALL;
                    world[i][32][j + 1] = CLR_DG_WALL;
                    world[i][33][j + 1] = CLR_DG_WALL;
                }
                if(maze[i][j - 1] == ' ') {
                    world[i][31][j - 1] = CLR_DG_WALL;
                    world[i][32][j - 1] = CLR_DG_WALL;
                    world[i][33][j - 1] = CLR_DG_WALL;
                }

                // Check diagonals
                if(maze[i + 1][j + 1] == ' ') {
                    world[i + 1][31][j + 1] = CLR_DG_WALL;
                    world[i + 1][32][j + 1] = CLR_DG_WALL;
                    world[i + 1][33][j + 1] = CLR_DG_WALL;
                }
                if(maze[i + 1][j - 1] == ' ') {
                    world[i + 1][31][j - 1] = CLR_DG_WALL;
                    world[i + 1][32][j - 1] = CLR_DG_WALL;
                    world[i + 1][33][j - 1] = CLR_DG_WALL;
                }
                if(maze[i - 1][j + 1] == ' ') {
                    world[i - 1][31][j + 1] = CLR_DG_WALL;
                    world[i - 1][32][j + 1] = CLR_DG_WALL;
                    world[i - 1][33][j + 1] = CLR_DG_WALL;
                }
                if(maze[i - 1][j - 1] == ' ') {
                    world[i - 1][31][j - 1] = CLR_DG_WALL;
                    world[i - 1][32][j - 1] = CLR_DG_WALL;
                    world[i - 1][33][j - 1] = CLR_DG_WALL;
                }
            }
        }
    }
}

void printDungeon() {
    for(int i = 0; i < WORLDX; i++) {
        for(int j = 0; j < WORLDZ; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}