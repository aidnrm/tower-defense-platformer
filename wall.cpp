//
// Created by Ty Allembert on 4/29/22.
//

#include "wall.h"

Wall::Wall(){
    wallID = -1;
    position = 0;
    health = STARTING_HEALTH;
    initWall();
}

void Wall::initWall(){
    //looks like fork
    //base
    pieces.push_back(make_unique<Rect>(hoverWall, point2D(-500,360), dimensions(7,40)));
    //horizontal piece
    pieces.push_back(make_unique<Rect>(hoverWall, point2D(pieces[0]->getCenterX(),pieces[0]->getCenterY()-22.5), dimensions(25,5)));
    //prongs
    pieces.push_back(make_unique<Rect>(hoverWall, point2D(pieces[1]->getCenterX(),pieces[1]->getCenterY()-10), dimensions(5,15))); // middle prong
    pieces.push_back(make_unique<Rect>(hoverWall, point2D(pieces[1]->getCenterX() + 15,pieces[1]->getCenterY()-10), dimensions(5,15)));
    pieces.push_back(make_unique<Rect>(hoverWall, point2D(pieces[1]->getCenterX() - 15,pieces[1]->getCenterY()-10), dimensions(5,15)));

    //health bar
    pieces.push_back(make_unique<Rect>(healthBarBackground, point2D(pieces[0]->getCenterX(),pieces[0]->getCenterY()-70), dimensions(44,10)));
    pieces.push_back(make_unique<Rect>(healthBarGreen, point2D(pieces[0]->getCenterX(),pieces[0]->getCenterY()-70), dimensions(40,6)));

}
void Wall::draw(){
    for(unique_ptr<Shape> &s: pieces){
        s->draw();
    }
}

int Wall::getHealth() const{
    return health;
}
void Wall::setHealth(int h, int enemyDamage){
    health = h;
    double healthPercentage = health/STARTING_HEALTH;
    pieces[pieces.size()-1]->setWidth((pieces[pieces.size()-2]->getWidth()-4)*healthPercentage);
    pieces[pieces.size()-1]->setCenterX(pieces[pieces.size()-1]->getCenterX()-((pieces[pieces.size()-2]->getWidth()-4)*enemyDamage/200));
}

int Wall::getPosition(){
    return position;
}
void Wall::setPosition(int p){
    position = p;
    for(unique_ptr<Shape> &s: pieces){
        s->setCenterX(position);
    }
    pieces[3]->setCenterX(pieces[3]->getCenterX() + 10);
    pieces[4]->setCenterX(pieces[4]->getCenterX() - 10);
}
// TODO: Make sure Wall Width is still 20, because we hard-coded the following getter values:
//something like  return position + pieces[0].getWidth();
int Wall::getRightX(){
    return position + 10;
}
int Wall::getLeftX() {
    return position-10;
}
void Wall::eraseWall() {
    position = -500;
    for(unique_ptr<Shape> &s: pieces){
        s->setCenterX(-500);
    }
}
void Wall::setWallID(int id){
    wallID = id;
}
int Wall::getWallID(){
    return wallID;
}
void Wall::setColor(color c){

    for(int i = 0; i < pieces.size()-2; ++i){
        pieces[i]->setColor(c);
    }
}
