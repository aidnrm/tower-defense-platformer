#include "menu.h"
using namespace std;

Menu::Menu(){
    money = 0;
    gemHealth = STARTING_HEALTH;
}

void Menu::initMenu(int height, int width){
    //black border
    menuBody.push_back(make_unique<Rect>(black, point2D(width/2, height-60), dimensions(244, 104)));
    //background
    menuBody.push_back(make_unique<Rect>(menuBackground, point2D(menuBody[0]->getCenterX(), menuBody[0]->getCenterY()), dimensions(240, 100)));
    //gem pic
    menuBody.push_back(make_unique<Circle>(menuBackground, width/2-120,40, 37));
    menuBody.push_back(make_unique<Circle>(menuButtonColor, width/2-120,40, 35));
    cout << width/2-120 << endl;
    menuGem.initGem(width/2+70,50, 1.5);

    // health bar
    menuBody.push_back(make_unique<Rect>(healthBarBackground,point2D((width/2) + 60, 20), dimensions(279, 14)));
    menuBody.push_back(make_unique<Rect>(healthBarGreen,point2D(width/2 + 60, 20), dimensions(275, 10)));

    // shoot button & build button BORDERS
    menuBody.push_back(make_unique<Rect>(black,point2D(menuBody[0]->getCenterX()-(menuBody[0]->getWidth()/4), menuBody[0]->getCenterY() + 25), dimensions(94, 44)));
    menuBody.push_back(make_unique<Rect>(black,point2D(menuBody[0]->getCenterX()+(menuBody[0]->getWidth()/4), menuBody[0]->getCenterY() + 25), dimensions(94, 44)));
    // shoot button & build button
    menuBody.push_back(make_unique<Rect>(menuButtonColor,point2D(menuBody[0]->getCenterX()-(menuBody[0]->getWidth()/4), menuBody[0]->getCenterY() + 25), dimensions(90, 40)));
    menuBody.push_back(make_unique<Rect>(menuButtonColor,point2D(menuBody[0]->getCenterX()+(menuBody[0]->getWidth()/4), menuBody[0]->getCenterY() + 25), dimensions(90, 40)));

}
void Menu::draw(){
    for(unique_ptr<Shape> &s: menuBody){
        s->draw();
    }
    //label for shoot
    string shootString = "Shoot";
    glColor3f(black.red, black.green, black.blue);
    glRasterPos2i(menuBody[menuBody.size()-2]->getCenterX()-17, menuBody[menuBody.size()-2]->getCenterY()+5);
    for(const char &letter : shootString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
    }
    //label for build
    string buildString = "Build";
    glColor3f(black.red, black.green, black.blue);
    glRasterPos2i(menuBody[menuBody.size()-1]->getCenterX()-30, menuBody[menuBody.size()-1]->getCenterY()+5);
    for(const char &letter : buildString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
    }

    menuGem.draw(1.5);
    string amountMoney = to_string(money);
    string coinsString = "Coins: ";
    glColor3f(black.red, black.green, black.blue);
    glRasterPos2i(menuBody[0]->getCenterX()-100, menuBody[0]->getCenterY()-30);
    for(const char &letter : coinsString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
    }
    glColor3f(coinsGold.red, coinsGold.green, coinsGold.blue);
    glRasterPos2i(menuBody[0]->getCenterX()-45, menuBody[0]->getCenterY()-30);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '$');
    for(const char &letter : amountMoney) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
    }
    //enemies killed text
    string eKilled = to_string(enemiesKilled);
    string killed = "Enemies Killed: ";
    glColor3f(black.red, black.green, black.blue);
    glRasterPos2i(menuBody[0]->getCenterX()-100, menuBody[0]->getCenterY()-6);
    for(const char &letter : killed) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
    }
    glColor3f(red.red, red.green, red.blue);
    glRasterPos2i(menuBody[0]->getCenterX()+25, menuBody[0]->getCenterY()-6);
    for(const char &letter : eKilled) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
    }
}

void Menu::changeHealth(){

}
void Menu::addMoney(int amount){
    money += amount;
}
void Menu::subtractMoney(int amount){
    money -= amount;
}
int Menu::getMoney() {
    return money;
}
void Menu::addEnemiesKilled(){
    enemiesKilled++;
}
int Menu::getEnemiesKilled(){
    return enemiesKilled;
}
void Menu::setHealth(int h, int enemyDamage){
    gemHealth = h;
    double healthPercentage = gemHealth/STARTING_HEALTH;
    int beforeWidth = menuBody[5]->getWidth();
    menuBody[5]->setWidth((menuBody[4]->getWidth()-4)*healthPercentage);
    menuBody[5]->setCenterX(menuBody[5]->getCenterX()-(beforeWidth-(menuBody[4]->getWidth()-4)*healthPercentage)/2);
}
int Menu::getGemHealth() {
    return gemHealth;
}
string Menu::setActiveButton(int x, int y){
    //if for the right button(build)
    if(x >= menuBody[menuBody.size() - 1]->getLeftX() && x <= menuBody[menuBody.size() - 1]->getRightX() && y >= menuBody[menuBody.size() - 1]->getTopY() && y <= menuBody[menuBody.size() - 1]->getBottomY()){
        menuBody[menuBody.size() - 1]->setColor(menuActiveButtonColor);
        menuBody[menuBody.size() - 2]->setColor(menuButtonColor);
        return "build";
    }
    else if(x >= menuBody[menuBody.size() - 2]->getLeftX() && x <= menuBody[menuBody.size() - 2]->getRightX() && y >= menuBody[menuBody.size() - 2]->getTopY() && y <= menuBody[menuBody.size() - 2]->getBottomY()){
        menuBody[menuBody.size() - 2]->setColor(menuActiveButtonColor);
        menuBody[menuBody.size() - 1]->setColor(menuButtonColor);
        return "shoot";
    }
    return "";
}