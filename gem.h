//
// Created by Ty Allembert on 5/2/22.
//

#ifndef FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_GEM_H
#define FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_GEM_H

#include "shape.h"
#include "rect.h"
#include "circle.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
using namespace std;
class Gem {
private:
    //colors
    const color standDarkBrown = {110/255.0, 70/255.0, 15/255.0};
    const color standLightBrown = {163/255.0, 120/255.0, 59/255.0};
    const color gemPurple = {212/255.0, 115/255.0, 245/255.0};
    const color gemLightPurple = {224/255.0, 162/255.0, 245/255.0};
    const color gemDarkPurple = {154/255.0, 42/255.0, 191/255.0};
    const color gemDarkShadowPurple = {103/255.0, 15/255.0, 133/255.0};
    const color hitboxContainer = {0, 1.0, 0, 0};

    const color healthBarBackground= {115/255.0, 72/255.0, 21/255.0};
    const color healthBarGreen= {78/255.0, 245/255.0, 66/255.0};

    const double STARTING_HEALTH = 500.0;
    vector<unique_ptr<Shape>> gem;
    int health;
    int position;
public:
    /* Constructors */
    Gem();

    void initGem(int x, int y, double scale);
    void draw(double scale);

    int getHealth() const;
    void setHealth(int h, int enemyDamage);

    int getPosition();
    void setPosition(int p);

    int getRightX();
    int getLeftX();

    void setColor(color c);
};


#endif //FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_GEM_H
