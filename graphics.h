#ifndef FINAL_PROJECT_GRAPHICS_H
#define FINAL_PROJECT_GRAPHICS_H

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "rect.h"
#include "wall.h"
using namespace std;

// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet
void init();

// Initialize OpenGL Graphics
void InitGL();

// Callback functions for GLUT

void printDirection(string string, int moveX, int moveY);

// Draw the window - this is where all the GL actions are
void display();

// Trap and process alphanumeric keyboard events
void kbd(unsigned char key, int x, int y);

// Trap and process special keyboard events
void kbdS(int key, int x, int y);

// Handle "mouse cursor moved" events
void cursor(int x, int y);

// Handle mouse button pressed and released events
void mouse(int button, int state, int x, int y);

bool isOverlapping(int x, int y, Rect r);
// Calls itself after a specified time
void jumpTimer(int dummy);
void bulletTimer(int dummy);
bool wallOverlapping(Wall &w2, int x, int y);
void drawBackground(string fileName);

#endif //FINAL_PROJECT_GRAPHICS_H
