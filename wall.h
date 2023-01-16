//
// Created by Ty Allembert on 4/29/22.
//

#ifndef FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_WALL_H
#define FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_WALL_H

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

#include "shape.h"
#include "rect.h"
#include "circle.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
using namespace std;
class Wall {
private:
    //colors
    const color placedWall = {255/255.0, 255/255.0, 255/255.0};
    const color hoverWall = {255/255.0, 255/255.0, 255/255.0, 0.5};

    const color healthBarBackground= {115/255.0, 72/255.0, 21/255.0};
    const color healthBarGreen= {78/255.0, 245/255.0, 66/255.0};

    const double STARTING_HEALTH = 100.0;
    vector<unique_ptr<Shape>> pieces;
    int wallID;
    int health;
    int position;
public:
    /* Constructors */
    Wall();

    void initWall();
    void draw();

    int getHealth() const;
    void setHealth(int h, int enemyDamage);

    int getPosition();
    void setPosition(int p);

    int getRightX();
    int getLeftX();

    int getWallID();
    void setWallID(int id);

    void eraseWall();

    void setColor(color c);
};


#endif //FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_WALL_H
