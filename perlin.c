#include "perlin.h"
#include "graphics.h"
#include "utils.h"
#include "clouds.h"
#include "colors.h"

/* 
    Code for generating 2D Perlin noise inspired by pseudocode found here:
    https://web.archive.org/web/20160530124230/http://freespace.virgin.net/hugo.elias/models/m_perlin.htm

    As well as the code found here:
    https://en.wikipedia.org/wiki/Perlin_noise#Implementation
*/

int a, b, c;

int numX = WORLDX,
    numY = WORLDZ,
    numOctaves = 5;
float persistence = 0.1;

float noise[WORLDX][WORLDZ];
float terrain[WORLDX][WORLDZ];

float Noise(int x, int y) {
    int n = x + y * 57;
    n = (n << 13) ^ n;

    int t = (n * (n * n * a + b) + c) & 0x7fffffff;
    return 1.0 - ((float)t / 1073741824.0);
}

float SmoothedNoise(int x, int y) {
    float corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
    float sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
    float center = Noise(x, y) / 4;
    
    return corners + sides + center;
}

float Interpolate(float a, float b, float x) {
    return (b - a) * x + a;
}

float InterpolatedNoise(float x, float y) {
    int integer_X = x;
    float fractional_X = x - integer_X;
    int integer_Y = y;
    float fractional_Y = y - integer_Y;

    float v1 = SmoothedNoise(integer_X, integer_Y);
    float v2 = SmoothedNoise(integer_X + 1, integer_Y);
    float v3 = SmoothedNoise(integer_X, integer_Y + 1);
    float v4 = SmoothedNoise(integer_X + 1, integer_Y + 1);
    float i1 = Interpolate(v1, v2, fractional_X);
    float i2 = Interpolate(v3, v4, fractional_X);

    return Interpolate(i1, i2, fractional_Y);
}

float ValueNoise_2D(float x, float y) {
    float total = 0;
    float frequency = pow(2, numOctaves);
    float amplitude = 1;

    for (int i = 0; i < numOctaves; i++) {
        frequency /= 2;
        amplitude *= persistence;
        total += InterpolatedNoise(x / frequency, y / frequency) * amplitude;
    }

    return total / frequency;
}

void generateNoise() {
    for (int i = 0; i < WORLDX; i++) {
        for (int j = 0; j < WORLDZ; j++) {
            noise[i][j] = ValueNoise_2D(i, j);
        }
    }
}

void generateTerrain() {
    a = getRandom(1000000, 9999999);
    b = getRandom(1000000, 9999999);
    c = getRandom(1000000, 9999999);
    generateNoise();

    for (int i = 0; i < WORLDX; i++) {
        for (int j = 0; j < WORLDZ; j++) {
            terrain[i][j] = ((int)(noise[i][j] * 1000) / 2) + 25;
            if (terrain[i][j] < 0) {
                terrain[i][j] = 0;
            }
            else if (terrain[i][j] > 40) {
                terrain[i][j] = 40;
            }

            for(int k = 0; k <= terrain[i][j]; k++) {
                world[i][k][j] = (k < terrain[i][j]) ? CLR_DIRT : CLR_GRASS;
            }
            if(terrain[i][j] > 38) {
                world[i][(int)terrain[i][j]][j] = CLR_SNOW;
            }
        }
    }

    int x = getRandom(40, 60);
    int z = getRandom(40, 60);
    if(x == 50 && z == 50) {
        x++;
        z++;
    }
    for(int y = 41; y >= 0; y--) {
        if(world[x][y][z] != 0) {
            world[x][y][z] = CLR_D_STAIR;
        }
    }

    for(int i = 0; i < NUM_CLOUDS - 1; i++) {
        makeCloud(i);
    }
}
