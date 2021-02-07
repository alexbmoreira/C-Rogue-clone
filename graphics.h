#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

#ifdef __LINUX__
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

        /* world size and storage array */
#define WORLDX 100
#define WORLDY 50
#define WORLDZ 100

	/* list of cubes to draw with each screen update */
#define MAX_DISPLAY_LIST 500000

	/* maximum number of user defined colours */
#define NUMBERCOLOURS 100

GLubyte world[WORLDX][WORLDY][WORLDZ];
