//
// Created by Ty Allembert on 5/2/22.
//

#include "graphics.h"
#include "gem.h"

Gem::Gem(){
    position = 0;
    health = STARTING_HEALTH;

    //initGem(500, 300);
}

void Gem::initGem(int x, int y, double scale){
    gem.push_back(make_unique<Rect>(hitboxContainer, point2D(x,y), dimensions(85/scale,150/scale)));

}
void Gem::draw(double scale){
    for(unique_ptr<Shape> &s: gem){
        s->draw();
    }

    //stand
//    glColor3f(standDarkBrown.red, standDarkBrown.green, standDarkBrown.blue);
//    glBegin(GL_QUADS);
//    glVertex2i((gem[0]->getCenterX()-50)/scale, (gem[0]->getCenterY()+100)/scale);
//    glVertex2i((gem[0]->getCenterX()-20)/scale, (gem[0]->getCenterY()+40)/scale);
//    glColor3f(standLightBrown.red, standLightBrown.green, standLightBrown.blue);
//    glVertex2i((gem[0]->getCenterX()+20)/scale, (gem[0]->getCenterY()+40)/scale);
//    glVertex2i((gem[0]->getCenterX()+50)/scale, (gem[0]->getCenterY()+100)/scale);
//    glEnd();

    //center triangle
    glColor3f(gemPurple.red, gemPurple.green, gemPurple.blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i((gem[0]->getCenterX()+20)/scale, (gem[0]->getCenterY())/scale);
    glVertex2i((gem[0]->getCenterX()-20)/scale, (gem[0]->getCenterY())/scale);
    glVertex2i((gem[0]->getCenterX())/scale, (gem[0]->getCenterY()+50)/scale);
    glEnd();
    //right triangle
    glColor3f(gemLightPurple.red, gemLightPurple.green, gemLightPurple.blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i((gem[0]->getCenterX()+20)/scale, (gem[0]->getCenterY())/scale);
    glVertex2i((gem[0]->getCenterX()+40)/scale, (gem[0]->getCenterY()+5)/scale);
    glVertex2i((gem[0]->getCenterX())/scale, (gem[0]->getCenterY()+50)/scale);
    glEnd();
    //left triangle
    glColor3f(gemDarkPurple.red, gemDarkPurple.green, gemDarkPurple.blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i((gem[0]->getCenterX()-20)/scale, (gem[0]->getCenterY())/scale);
    glVertex2i((gem[0]->getCenterX()-40)/scale, (gem[0]->getCenterY()+5)/scale);
    glVertex2i((gem[0]->getCenterX())/scale, (gem[0]->getCenterY()+50)/scale);
    glEnd();
    //top center
    glColor3f(gemDarkPurple.red, gemDarkPurple.green, gemDarkPurple.blue);
    glBegin(GL_QUADS);
    glVertex2i((gem[0]->getCenterX()+20)/scale, (gem[0]->getCenterY())/scale);
    glVertex2i((gem[0]->getCenterX()-20)/scale, (gem[0]->getCenterY()/scale));
    glColor3f(gemPurple.red, gemPurple.green, gemPurple.blue);
    glVertex2i((gem[0]->getCenterX()-15)/scale, (gem[0]->getCenterY()-20)/scale);
    glVertex2i((gem[0]->getCenterX()+15)/scale, (gem[0]->getCenterY()-20)/scale);
    glEnd();
    //top right
    glColor3f(gemPurple.red, gemPurple.green, gemPurple.blue);
    glBegin(GL_QUADS);
    glVertex2i((gem[0]->getCenterX()+20)/scale, (gem[0]->getCenterY())/scale);
    glVertex2i((gem[0]->getCenterX()+40)/scale, (gem[0]->getCenterY()+5)/scale);
    glColor3f(gemLightPurple.red, gemLightPurple.green, gemLightPurple.blue);
    glVertex2i((gem[0]->getCenterX()+30)/scale, (gem[0]->getCenterY()-15)/scale);
    glVertex2i((gem[0]->getCenterX()+15)/scale, (gem[0]->getCenterY()-20)/scale);
    glEnd();
    //top left
    glColor3f(gemDarkShadowPurple.red, gemDarkShadowPurple.green, gemDarkShadowPurple.blue);
    glBegin(GL_QUADS);
    glVertex2i((gem[0]->getCenterX()-20)/scale, (gem[0]->getCenterY())/scale);
    glVertex2i((gem[0]->getCenterX()-40)/scale, (gem[0]->getCenterY()+5)/scale);
    glColor3f(gemDarkPurple.red, gemDarkPurple.green, gemDarkPurple.blue);
    glVertex2i((gem[0]->getCenterX()-30)/scale, (gem[0]->getCenterY()-15)/scale);
    glVertex2i((gem[0]->getCenterX()-15)/scale, (gem[0]->getCenterY()-20)/scale);
    glEnd();
}

int Gem::getHealth() const{
    return health;
}
void Gem::setHealth(int h, int enemyDamage){
    health = h;
    double healthPercentage = health/STARTING_HEALTH;
    cout << healthPercentage << endl;
    cout << "health: " << health << endl;
    gem[2]->setWidth((gem[1]->getWidth()-4)*healthPercentage);
    gem[2]->setCenterX(gem[2]->getCenterX()-((gem[1]->getWidth()-4)*enemyDamage/200));
}

int Gem::getPosition(){
    return position;
}
void Gem::setPosition(int p){
    position = p;
    for(unique_ptr<Shape> &s: gem){
        s->setCenterX(position);
    }
}
int Gem::getRightX(){
    return gem[0]->getRightX();
}
int Gem::getLeftX() {
    return gem[0]->getLeftX();
}

void Gem::setColor(color c){
    for(unique_ptr<Shape> &s: gem){
        s->setColor(c);
    }
}