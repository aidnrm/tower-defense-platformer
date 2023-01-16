//
// Created by Ty Allembert on 5/2/22.
//

#ifndef FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_MENU_H
#define FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_MENU_H

#include "shape.h"
#include "rect.h"
#include "circle.h"
#include "gem.h"
#include "graphics.h"
#include "menu.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
using namespace std;
class Menu {
private:
    //colors
    const color black = {0, 0, 0};
    const color menuBackground={134/255.0, 144/255.0, 155/255.0};
    const color menuButtonColor={135/255.0, 135/255.0, 155/255.0};
    const color menuActiveButtonColor={155/255.0, 134/255.0, 155/255.0};
    const color coinsGold={199/255.0, 199/255.0, 70/255.0};
    const color red={1,0,0};

    //134, 144, 155
    //135, 134, 155
    //145, 134, 155
    //155, 134, 155

    const color healthBarBackground= {175/255.0, 175/255.0, 175/255.0};
    const color healthBarGreen= {78/255.0, 245/255.0, 66/255.0};

    const double STARTING_HEALTH = 500.0;
    vector<unique_ptr<Shape>> menuBody;
    Gem menuGem;
    int gemHealth;
    int money;
    int enemiesKilled;
public:
    /* Constructors */
    Menu();

    void initMenu(int height, int width);
    void draw();

    void changeHealth();
    void addMoney(int amount);
    void subtractMoney(int amount);
    int getMoney();

    void setHealth(int h, int enemyDamage);
    int getGemHealth();

    void addEnemiesKilled();
    int getEnemiesKilled();

    string setActiveButton(int x, int y);
};



#endif //FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_MENU_H
