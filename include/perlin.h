#include <math.h>
#include <stdlib.h>
#include <stdio.h>

float Noise(int x, int y);
float SmoothedNoise(int x, int y);
float Interpolate(float a, float b, float x);
float InterpolatedNoise(float x, float y);
float ValueNoise_2D(float x, float y);
void generateNoise();
void generateTerrain();