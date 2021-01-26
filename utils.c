#include "utils.h"


int getRandom(int min, int max) {
   int r = (rand() % (max + 1 - min)) + min;
   return r;
}