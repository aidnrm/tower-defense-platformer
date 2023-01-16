#include "enemyNPC.h"
using namespace std;

enemyNPC::enemyNPC(){
    speed = (double)rand()/(RAND_MAX+1)*(2-0.5)+2;
    health = 100;
    damage = 10;
    alive = true;
}

void enemyNPC::initEnemy(){
    startSide = rand() % 2;
    position = rand() % 300 + 51.0;
    if (startSide == 0) {
        position = -(position);
    }else{
        position = 1000 + position;
    }
    //position = 400;
    //startSide = 0;

    //hitbox
    body.push_back(make_unique<Rect>(hitBox, point2D(position,300), dimensions(50,100)));

    //frosting
    body.push_back(make_unique<Rect>(white, point2D(body[0]->getCenterX(),body[0]->getCenterY()+20), dimensions(54,6)));
    body.push_back(make_unique<Rect>(white, point2D(body[0]->getCenterX(),body[0]->getCenterY()-10), dimensions(44,6)));
    body.push_back(make_unique<Rect>(white, point2D(body[0]->getCenterX(),body[0]->getCenterY()-40), dimensions(34,6)));

//    body.push_back(Rect(theColor, point2D(body[frostingLevelOfCandle]->getCenterX()+ xPlacementOfCandle,body[1]->getCenterY()-5), dimensions(5,30)));

    //candles
    body.push_back(make_unique<Rect>(minecraftCandleBrown, point2D(body[1]->getCenterX(),body[1]->getCenterY()-8), dimensions(5,16)));
    body.push_back(make_unique<Rect>(mincraftTorchFlameColor, point2D(body[4]->getCenterX(),body[4]->getCenterY()-10.5), dimensions(5,5)));

    body.push_back(make_unique<Rect>(minecraftCandleBrown, point2D(body[2]->getCenterX(),body[2]->getCenterY()-8), dimensions(5,16)));
    body.push_back(make_unique<Rect>(mincraftTorchFlameColor, point2D(body[6]->getCenterX(),body[6]->getCenterY()-10.5), dimensions(5,5)));

    body.push_back(make_unique<Rect>(minecraftCandleBrown, point2D(body[3]->getCenterX(),body[3]->getCenterY()-8), dimensions(5,16)));
    body.push_back(make_unique<Rect>(mincraftTorchFlameColor, point2D(body[8]->getCenterX(),body[8]->getCenterY()-10.5), dimensions(5,5)));

//    candles.push_back(Rect(white, point2D(body[0]->getCenterX(),body[0]->getCenterY()+20), dimensions(54,6)));

    //health bar
    body.push_back(make_unique<Rect>(healthBarBackground, point2D(body[0]->getCenterX(),body[0]->getCenterY()-70), dimensions(84,10)));
    body.push_back(make_unique<Rect>(healthBarGreen, point2D(body[0]->getCenterX(),body[0]->getCenterY()-70), dimensions(80,6)));

}

void enemyNPC::draw(double scale) {
    body[0]->draw();
    body[body.size()-2]->draw();
    body[body.size()-1]->draw();
    //lower cake
    glColor3f(enemyColorOne.red, enemyColorOne.green, enemyColorOne.blue);
    glBegin(GL_QUADS);
    glVertex2i((body[0]->getCenterX()-25)/scale, (body[0]->getCenterY()+50)/scale);
    glVertex2i((body[0]->getCenterX()+25)/scale, (body[0]->getCenterY()+50)/scale);
    glColor3f(enemyColorTwo.red, enemyColorTwo.green, enemyColorTwo.blue);
    glVertex2i((body[0]->getCenterX()+25)/scale, (body[0]->getCenterY()+20)/scale);
    glVertex2i((body[0]->getCenterX()-25)/scale, (body[0]->getCenterY()+20)/scale);
    glEnd();

    //middle cake
    glColor3f(enemyColorOne.red, enemyColorOne.green, enemyColorOne.blue);
    glBegin(GL_QUADS);
    glVertex2i((body[0]->getCenterX()-20)/scale, (body[0]->getCenterY()+20)/scale);
    glVertex2i((body[0]->getCenterX()+20)/scale, (body[0]->getCenterY()+20)/scale);
    glColor3f(enemyColorTwo.red, enemyColorTwo.green, enemyColorTwo.blue);
    glVertex2i((body[0]->getCenterX()+20)/scale, (body[0]->getCenterY()-10)/scale);
    glVertex2i((body[0]->getCenterX()-20)/scale, (body[0]->getCenterY()-10)/scale);
    glEnd();

    //top cake
    glColor3f(enemyColorOne.red, enemyColorOne.green, enemyColorOne.blue);
    glBegin(GL_QUADS);
    glVertex2i((body[0]->getCenterX()-15)/scale, (body[0]->getCenterY()-10)/scale);
    glVertex2i((body[0]->getCenterX()+15)/scale, (body[0]->getCenterY()-10)/scale);
    glColor3f(enemyColorTwo.red, enemyColorTwo.green, enemyColorTwo.blue);
    glVertex2i((body[0]->getCenterX()+15)/scale, (body[0]->getCenterY()-40)/scale);
    glVertex2i((body[0]->getCenterX()-15)/scale, (body[0]->getCenterY()-40)/scale);
    glEnd();

    //frosting
    body[1]->draw();
    body[2]->draw();
    body[3]->draw();

    for(int i = 4; i < 10; ++i){
        body[i]->draw();
    }

}

int enemyNPC::getHealth() const {
    return health;
}

void enemyNPC::setHealth(int h, double bulletDamage) {
    health = h;
    double healthPercentage = health/STARTING_HEALTH;
    body[body.size()-1]->setWidth((body[body.size()-2]->getWidth()-4)*healthPercentage);
    //body[body.size()-1]->setCenterX(body[body.size()-1]->getCenterX()-healthPercentage);
    //pieces[2]->setCenterX(pieces[2]->getCenterX()-((pieces[1]->getWidth()-4)*enemyDamage/200));
    //body[body.size()-1]->setCenterX(body[body.size()-1]->getCenterX()-((body[body.size()-2]->getWidth()-4)*bulletDamage/200));
    //body[body.size()-1]->setCenterX(body[body.size()-1]->getCenterX()-10);
    //body[body.size()-1]->setCenterX(body[body.size()-2]->getLeftX()+(body[body.size()-1]->getWidth()/2)+2);
}
int enemyNPC::getDamage() const {
    return damage;
}
void enemyNPC::setDamage(int d) {
    damage = d;
}
double enemyNPC::getSpeed(){
    return speed;
}
int enemyNPC::getPosition(){
    return position;
}
void enemyNPC::moveLeft(int num){
    position -= num;
    for(unique_ptr<Shape> &s: body){
        s->setCenterX(position);
    }
    for(Rect c: candles){
        c.setCenterX(c.getCenterX()-num);
    }
}
void enemyNPC::moveRight(int num){
    position += num;
    for(unique_ptr<Shape> &s: body){
        s->setCenterX(position);
    }
    for(Rect c: candles){
        c.setCenterX(c.getCenterX()+num);
    }
}
bool enemyNPC::isOverlappingWall(vector<Wall> &walls){
    bool overlapTime = false;
    for(int j = 0; j < walls.size()-1; ++j){
        Wall &w = walls[j];
        for(int i = 0; i < body.size()-3; ++i){
            if (this->startSide == 0 && this->body[0]->getCenterY() > 0 && (w.getLeftX() <= body[i]->getRightX() && w.getRightX() >= body[i]->getLeftX())) {
                overlapTime = true;
                w.setHealth(w.getHealth()-damage, damage);
            }
            if (this->startSide == 1 && this->body[0]->getCenterY() > 0 && (w.getRightX() >= body[i]->getLeftX() && w.getLeftX() <= body[i]->getRightX())){
                overlapTime = true;
                w.setHealth(w.getHealth()-damage, damage);
            }
        }

        if(w.getHealth() <= 0){
            w.eraseWall();
        }
    }
    return overlapTime;
}
bool enemyNPC::isOverlappingGem(Gem &gem, Menu &menu){
    if(this->startSide == 0 && this->position >= gem.getLeftX() && this->position <= gem.getRightX()){
        menu.setHealth(menu.getGemHealth()-damage, damage);
        return true;
    }
    else if(this->startSide == 1 && this->position <= gem.getRightX() && this->position >= gem.getLeftX()){
        menu.setHealth(menu.getGemHealth()-damage, damage);
        return true;
    }else{
        return false;
    }
}
bool enemyNPC::hitByBullet(Circle b){

    if((body[0]->getCenterX() + 5 > b.getCenterX())&&(body[0]->getCenterX() - 5 < b.getCenterX()) && b.getCenterX() < 1000 && b.getCenterX() > 0){
        return true;
    }

    return false;
}
void enemyNPC::killed(){
    position = -100;
    alive = false;
    for(unique_ptr<Shape> &s: body){
        s->setCenter(-100, -100);
    }
}
bool enemyNPC::isLiving(){
    return alive;
}
