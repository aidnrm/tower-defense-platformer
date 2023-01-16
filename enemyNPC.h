
#ifndef FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_ENEMYNPC_H
#define FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_ENEMYNPC_H

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
#include "wall.h"
#include "gem.h"
#include "menu.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
using namespace std;
class enemyNPC {
private:
    //colors
    //210, 145, 188
    const color enemyColorOne = {181/255.0, 116/255.0, 72/255.0}; //dark cake color
    const color enemyColorTwo = {199/255.0, 148/255.0, 113/255.0}; //light cake color
    //const color enemyColorThree = {255/255.0, 98/255.0, 87/255.0}; //lighter red

    const color black = {0, 0, 0};
    const color white = {1.0, 1.0, 1.0};
    const color healthBarBackground= {115/255.0, 72/255.0, 21/255.0};
    const color healthBarGreen= {78/255.0, 245/255.0, 66/255.0};
    const color hitBox = {0, 0, 0, 0};

    //candle colors
    const color minecraftCandleBrown= {120/255.0, 78/255.0, 34/255.0};
    const color mincraftTorchFlameColor = {240/255.0, 145/255., 46/255.};

    const double STARTING_HEALTH = 100.0;
    vector<unique_ptr<Shape>> body;
    vector<Rect> candles;
    int health;
    int damage;
    bool alive;
    double speed;
    //if side = 0 left if side = 1 right
    int startSide;
    double position;
public:
    /* Constructors */
    enemyNPC();

    void initEnemy();
    void draw(double scale);

    int getHealth() const;
    void setHealth(int h, double bulletDamage);
    int getDamage() const;
    void setDamage(int d);

    double getSpeed();
    int getPosition();
    void moveLeft(int num);
    void moveRight(int num);

    bool isOverlappingWall(vector<Wall> &walls);
    bool isOverlappingGem(Gem &gem, Menu &menu);
    bool hitByBullet(Circle b);
    void killed();
    bool isLiving();
};


#endif //FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_ENEMYNPC_H
