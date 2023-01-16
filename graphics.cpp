/*
 * TODO via 5/4/22
 * implement death menu
 * update player avatar
 * update enemy avatar
 * change menu colors (little diamond circle as well as player's GUI is gross as gray. Find replacement colors)
 * figure out what happens when game ends (when diamond dies, will there be a "leaderboard"?
 *                                                          A death screen w/ play again option? etc)
 * On backspace click make game reset
 * making testing file
 * make sure we have user input, and validation of user input (maybe email Lisa: does keybinds count as ui?)
 * MAKE SURE BULLET SHOOTS RIGHT WAY, used body for conditionals and now body is gone~!!!
 * write readme file
 */

#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include "enemyNPC.h"
#include "wall.h"
#include "gem.h"
#include "menu.h"
#include "button.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
using namespace std;

vector<string> aboutLines;

struct playerOption {
    bool shoot;
    bool build;
};

enum DifferentScreens {startScreen, aboutScreen, gameScreen, endScreen};
DifferentScreens diffScreens;

//DEFINE all global variables here
GLdouble width, height;
int wd;
const int SIDE_LENGTH = 10;
const int JUMP = -7;
int jumpSpeed = JUMP;
playerOption playerMenu;
bool aboutDonePrinting = false;
int waveCounter = 1;
int enemiesPerWave = 4;
int waveNumber = 1;

//Colors
const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color red(1, 0, 0);
const color green(0, 1, 0);
const color blue(0,0,1);
const color white(1,1,1);
const color black(0,0,0);
const color groundSpace(254/255.0, 200/250.0, 216/255.0);

//background colors
const color pastelOne(224/255.0, 84/255.0, 228/255.0);
const color pastelTwo(149/255.0, 125/255.0, 173/255.0);

//player colors
const color playerSkinTone(255/255.0, 223/255.0, 211/255.0);
const color playerSkinToneDarker(238/255.0, 208/255.0, 198/255.0);

//wall colors
const color hoverWall(255/255.0, 255/255.0, 255/255.0, 0.5);
const color placedWall(255/255.0, 255/255.0, 255/255.0);

//Start screen button colors
const color playColor(179/255.0, 111/255.0, 227/255.0);
const color playBorderColor(196/255.0, 146/255.0, 232/255.0);
const color aboutColor(212/255.0, 85/255.0, 201/255.0);
const color aboutBorderColor(232/255.0, 146/255.0, 225/255.0);

//Shapes
Rect ground;
vector<unique_ptr<Shape>> player;
vector<bool> bulletDirection;//if true bullet is going right, if false going left
vector<Circle> bullets;
Menu menu;
vector<Wall> walls;
vector<enemyNPC> enemies;
Gem gem;

Rect playButtonBoarder;
Rect aboutButtonBoarder;

Button playGameButton({playColor.red, playColor.green, playColor.blue}, {350, 250}, 100, 50, "PLAY");
Button aboutGame({aboutColor.red, aboutColor.green, aboutColor.blue}, {650, 250}, 100, 50, "ABOUT GAME");

//INITIALIZE functions here
void initPlayer(){

    //head 0
    player.push_back(make_unique<Circle>(playerSkinTone, width/2,300, 22));

//    player.push_back(make_unique<Rect>(white, point2D(player[0]->getCenterX(), player[0]->getCenterY()-30), dimensions(30, 10)));
//    player.push_back(make_unique<Rect>(white, point2D(player[0]->getCenterX(), player[0]->getCenterY()-40), dimensions(15, 10)));

// EYES
    //black part of eyes 1 2
    player.push_back(make_unique<Circle>(black, player[0]->getCenterX()-10,player[0]->getCenterY(), 5));
    player.push_back(make_unique<Circle>(black, player[0]->getCenterX()+10,player[0]->getCenterY(), 5));

    //white part of eyes 3 4
    player.push_back(make_unique<Circle>(white, player[1]->getCenterX()-2,player[0]->getCenterY(), 2));
    player.push_back(make_unique<Circle>(white, player[2]->getCenterX()-2,player[0]->getCenterY(), 2));

// chef hat 5 6 7
    player.push_back(make_unique<Rect>(white, point2D(player[0]->getCenterX(), player[0]->getCenterY()-30), dimensions(40, 47)));
    player.push_back(make_unique<Circle>(white, width/2 - 10, player[1]->getCenterY()-50, 18));
    player.push_back(make_unique<Circle>(white, width/2 + 10, player[1]->getCenterY()-50, 18));

    // body 8
    player.push_back(make_unique<Rect>(playerSkinTone, point2D(player[0]->getCenterX(), player[0]->getCenterY()+40), dimensions(15, 40)));

    // legs 9 10
    player.push_back(make_unique<Rect>(playerSkinTone, point2D(player[0]->getCenterX()-10, player[0]->getCenterY()+60), dimensions(10, 17)));
    player.push_back(make_unique<Rect>(playerSkinTone, point2D(player[0]->getCenterX()+10, player[0]->getCenterY()+60), dimensions(10, 17)));

    // arms 11 12
    player.push_back(make_unique<Rect>(playerSkinTone, point2D(player[0]->getCenterX()-10, player[0]->getCenterY()+45), dimensions(17, 7)));
    player.push_back(make_unique<Rect>(playerSkinTone, point2D(player[0]->getCenterX()+10, player[0]->getCenterY()+45), dimensions(17, 7)));

//    //body 5
//    player.push_back(make_unique<Rect>(brown, point2D(player[0]->getCenterX(), player[0]->getCenterY()+15+player[0]->getWidth()/2), dimensions(20, 40)));
//
//    //mouth 11
//    player.push_back(make_unique<Rect>(black,point2D(player[0]->getCenterX(), player[0]->getCenterY()+10), dimensions(10, 2)));
//
//    // legs 7 8
//    player.push_back(make_unique<Rect>(playerSkinTone, point2D(player[0]->getCenterX()-10, player[0]->getCenterY()+40+player[0]->getWidth()/2), dimensions(10, 25)));
//    player.push_back(make_unique<Rect>(playerSkinTone, point2D(player[0]->getCenterX()+10, player[0]->getCenterY()+40+player[0]->getWidth()/2), dimensions(10, 25)));


}
void initPlayButtonBoarder(){
    playButtonBoarder.setCenter(350, 250);
    playButtonBoarder.setSize(104, 54);
    playButtonBoarder.setColor(playBorderColor);
}

void initAboutGameBoarder(){
    aboutButtonBoarder.setCenter(650, 250);
    aboutButtonBoarder.setSize(104, 54);
    aboutButtonBoarder.setColor(aboutBorderColor);

}
void initGround(){
    ground.setCenter(width/2,height-(height/8));
    ground.setSize(width, height/4);
    ground.setColor(groundSpace);
}
void initWalls(){
    walls.push_back(Wall());
}
void initBullets(){
    bullets.push_back(Circle(white, width+10, player[0]->getCenterY(), 7));
    bulletDirection.push_back(true);
}
void initEnemies(int numEnemies){
    cout << "init enemies" << endl;
    cout << enemiesPerWave << endl;
    for(int i = 0; i < numEnemies; ++i){
        enemies.push_back(enemyNPC());
        enemies[enemies.size()-1].initEnemy();
    }
}
void initAbout(){
    string string1 = "Welcome to Fortnite 2. Use WASD to move & jump, and Space bar to shoot.";
    string string2 = "You must protect your diamond from the enemies. Kill them with shoot, and keep them away using walls.";
    string string3 = "Your score will be dependent on how far you go without dying.";

    aboutLines.push_back(string1);
    aboutLines.push_back(string2);
    aboutLines.push_back(string3);
}

void init(){
    width = 1000;
    height = 500;
    srand(time(0));
    diffScreens = startScreen;
    initPlayer();
    initGround();
    initBullets();
    menu.initMenu(height, width);
    initWalls();
    initEnemies(enemiesPerWave);
    // this is the big gem
    gem.initGem(500, 300, 1.0);
    initAbout();
}
void initGL() {
    // Set "clearing" or background color
    glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, 1.0f);
}
void drawBackground(string fileName){
    glColor3f(pastelOne.red, pastelOne.green, pastelOne.blue);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(width, 0);
    glColor3f(pastelTwo.red, pastelTwo.green, pastelTwo.blue);
    glVertex2i(width, height);
    glVertex2i(0, height);
    glEnd();
}

void printLabel(string string, int moveX, int moveY, color c){
    glColor3f(c.red, c.green, c.blue);
    glRasterPos2i(width/2 + moveX, height/2 + moveY);
    for(const char &letter : string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
    }
}

//DISPLAY function
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    //Makes alpha work
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE
    int moveX = -400;
    int moveY = -60;
    string label;

    switch (diffScreens) {
        case startScreen:
            drawBackground("space_background.txt");
            //draw button border
            aboutButtonBoarder.draw();
            playButtonBoarder.draw();
            //draw button on top
            playGameButton.draw();
            aboutGame.draw();
            break;
        case aboutScreen:

            for(string &s: aboutLines){
                printLabel( s, moveX, moveY, black);
                moveY += 20;
            }
            break;

        case gameScreen:
            //draw background
            drawBackground("space_background.txt");

            //draw ground
            ground.draw();

            //draw menu
            menu.draw();

            //draw walls
            for(Wall &w: walls){
                w.draw();
            }

            //draw Gem
            gem.draw(1.0);

            //draw player
            for (unique_ptr<Shape> &s : player) {
                s->draw();
            }

            //draw enemy
            for (enemyNPC &e : enemies) {
                e.draw(1.0);
            }

            //draw bullets
            for (Circle &s : bullets) {
                s.draw();
            }
            break;
        case endScreen:
            //draw background
            glColor3f(black.red, black.green, black.blue);
            glBegin(GL_QUADS);
            glVertex2i(0,0);
            glVertex2i(width, 0);
            glColor3f(pastelTwo.red, pastelTwo.green, pastelTwo.blue);
            glVertex2i(width, height);
            glVertex2i(0, height);
            glEnd();

            //prints # waves
            label = "Number of Waves: " + to_string(waveNumber);
            printLabel(label,-(label.size()*3), -100, white);

            //prints # enemies killed
            label = "Enemies killed: " + to_string(menu.getEnemiesKilled());
            printLabel(label,-(label.size()*3), -50, white);

            //prints play again
            label = "Press [Enter] to play again";
            printLabel(label,-(label.size()*3), 0, white);

            //prints exit
            label = "Press [Esc] to exit";
            printLabel(label,-(label.size()*3), +50, white);

            break;
    }

    glFlush();  // Render now
}

void kbd(unsigned char key, int x, int y) {

    switch (key) {
        case 'w':
            // eyes
            player[1]->setCenterX(player[0]->getCenterX()-10);
            player[2]->setCenterX(player[0]->getCenterX()+10);
            player[3]->setCenterX(player[1]->getCenterX()-2);
            player[4]->setCenterX(player[2]->getCenterX()-2);

            // chef hat
            player[5]->setCenterX(player[0]->getCenterX());
            player[6]->setCenterX(player[0]->getCenterX()-10);
            player[7]->setCenterX(player[0]->getCenterX()+10);

            // body
            player[8]->setCenterX(player[0]->getCenterX());

            // legs
            player[9]->setCenterX(player[0]->getCenterX()-8);
            player[10]->setCenterX(player[0]->getCenterX()+8);
            //player[9]->setColor(playerSkinTone);
            //player[10]->setColor(playerSkinTone);


//            // body
//            player[5]->setCenterX(player[0]->getCenterX());
//            player[5]->setCenterY(player[0]->getCenterY() + 35);
//
//            // mouth
//            player[6]->setCenterX(player[0]->getCenterX());
//
//            // legs
//            player[7]->setCenterX(player[0]->getCenterX());
//            player[8]->setCenterX(player[0]->getCenterX()-15);

            glutTimerFunc(0, jumpTimer, 0);
            break;
        case 'a':
            // eyes
            player[1]->setCenterX(player[0]->getCenterX()-15);
            player[2]->setCenterX(player[0]->getCenterX()-1);
            player[3]->setCenterX(player[1]->getCenterX()-2);
            player[4]->setCenterX(player[2]->getCenterX()-2);

            // chef hat
            player[5]->setCenterX(player[0]->getCenterX());
            player[6]->setCenterX(player[0]->getCenterX());
            player[7]->setCenterX(player[0]->getCenterX());

            //body
            player[8]->setCenterX(player[0]->getCenterX());

            // legs
            player[9]->setCenterX(player[0]->getCenterX()-5);
            //player[10]->setColor(playerSkinToneDarker);
            player[10]->setCenterX(player[0]->getCenterX()+5);
            //player[9]->setColor(playerSkinTone);

//            //mouth
//            player[6]->setCenterX(player[0]->getCenterX()-10);
//            //body
//            player[5]->setCenterX(player[0]->getCenterX()+20);
//            player[5]->setCenterY(player[0]->getCenterY()+5);
//
//            // legs
//            player[7]->setCenterX(player[0]->getCenterX());
//            player[8]->setCenterX(player[0]->getCenterX()-15);

            for (unique_ptr<Shape> &s : player){
                s->moveX(-5);
            }
            break;
        case 'd':
            // eyes
            player[1]->setCenterX(player[0]->getCenterX()+15);
            player[2]->setCenterX(player[0]->getCenterX()+1);
            player[3]->setCenterX(player[1]->getCenterX()+2);
            player[4]->setCenterX(player[2]->getCenterX()+2);

            //chef hat
            player[5]->setCenterX(player[0]->getCenterX());
            player[6]->setCenterX(player[0]->getCenterX());
            player[7]->setCenterX(player[0]->getCenterX());

            //body
            player[8]->setCenterX(player[0]->getCenterX());

            // legs
            player[9]->setCenterX(player[0]->getCenterX()+5);
            //player[9]->setColor(playerSkinToneDarker);
            player[10]->setCenterX(player[0]->getCenterX()-5);
            //player[10]->setColor(playerSkinTone);



            //mouth
//            player[6]->setCenterX(player[0]->getCenterX()+10);
//
//            //body(hunchbacky)
//            player[5]->setCenterX(player[0]->getCenterX()-20);
//            player[5]->setCenterY(player[0]->getCenterY()+15);
//
//            // legs
//            player[7]->setCenterX(player[0]->getCenterX()-10);
//            player[8]->setCenterX(player[0]->getCenterX());

            for (unique_ptr<Shape> &s : player){
                s->moveX(5);
            }
            break;
        case ' ':
            if(playerMenu.shoot){
                bullets.push_back(Circle(white, player[0]->getCenterX(), player[0]->getCenterY(), 7));
                if(!(player[2]->getCenterX() < player[0]->getCenterX())){
                    bulletDirection.push_back(true);
                }
                else if(!(player[2]->getCenterX() > player[0]->getCenterX())){
                    bulletDirection.push_back(false);
                }else{
                    bulletDirection.push_back(false);
                }
            }
    }
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    // Enter
    if (diffScreens == endScreen && key == 13){
        diffScreens = startScreen;
    }

    if (key == 8){
        diffScreens = startScreen;
    }
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {
    if(playerMenu.build){
        // hover & be red while overlapping
        if (wallOverlapping(walls[walls.size()-1], x, y)) {
            walls[walls.size()-1].setColor(red);
        }else{
            walls[walls.size()-1].setColor(hoverWall);
        }

        walls[walls.size()-1].setPosition(x);
    }

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && playGameButton.isOverlapping(x,y) && state == GLUT_DOWN){
        playGameButton.pressDown();
    }
    else{
        playGameButton.release();
    }
    if(button == GLUT_LEFT_BUTTON && aboutGame.isOverlapping(x,y) && state == GLUT_DOWN){
        aboutGame.pressDown();
    }
    else{
        aboutGame.release();
    }
    if(button == GLUT_LEFT_BUTTON && GLUT_UP == state && playGameButton.isOverlapping(x,y)){
        diffScreens = gameScreen;
    }
    else if(button == GLUT_LEFT_BUTTON && GLUT_UP == state && aboutGame.isOverlapping(x,y)){
        diffScreens = aboutScreen;
    }
    if(GLUT_LEFT_BUTTON == button && GLUT_DOWN == state){
        //choose MENU button active
        if(menu.setActiveButton(x, y) == "shoot"){//see if SHOOT is active
            playerMenu.shoot = true;
            playerMenu.build = false;
            menu.setActiveButton(x, y);
//            menu[2].setColor(menuActiveButtonColor);
//            menu[3].setColor(menuButtonColor);
            if(walls.size() >= 1){
                walls[walls.size()-1].setPosition(-500);
            }
        }
        else if(menu.setActiveButton(x, y) == "build"){//see if BUILD is active
            playerMenu.shoot = false;
            playerMenu.build = true;
//            menu[2].setColor(menuButtonColor);
//            menu[3].setColor(menuActiveButtonColor);
        }
        else if(playerMenu.build){
            if (!wallOverlapping(walls[walls.size()-1], x, y) && menu.getMoney() > 0) {
                walls[walls.size()-1].setPosition(x);
                walls[walls.size()-1].setColor(placedWall);
                walls.push_back(Wall());
                menu.subtractMoney(10);
            }
        }
    }
    glutPostRedisplay();
}
//used for determining if menu button clicked
bool isOverlapping(int x, int y, Rect r){
    if(x >= r.getLeftX() && x <= r.getRightX() && y >= r.getTopY() && y <= r.getBottomY()){
        return true;
    }else{
        return false;
    }
}

bool wallOverlapping(Wall &w2, int x, int y) {
    bool wallAvailable = false;
    if (walls.size() <= 1) {
        return wallAvailable;
    }
    for(int i = 0; i < walls.size()-1; ++i){
        if ((walls[i].getPosition()-10 <= w2.getPosition()+10) && (walls[i].getPosition()+10 >= w2.getPosition()-10)) {
            wallAvailable = true;
        }
    }
    return wallAvailable;
}

void jumpTimer(int dummy) {

    for (unique_ptr<Shape> &s : player){
        s->moveY(jumpSpeed);
    }

    jumpSpeed = jumpSpeed + 2;

    glutPostRedisplay();
    if(jumpSpeed <= -(JUMP)){
        glutTimerFunc(20, jumpTimer, dummy);
    }else{
        jumpSpeed = JUMP;
    }
}

void enemyWaveTimer(int dummy) {
    if (diffScreens == gameScreen){
        if (waveCounter % 10 == 0) {
            enemiesPerWave += 2;
            initEnemies(enemiesPerWave);
            waveNumber++;
        }
        waveCounter++;
    }

    glutPostRedisplay();
    glutTimerFunc(3000, enemyWaveTimer, dummy);
}
void enemyAndBulletTimer(int dummy) {
    //BULLET part of timer
    for (int i = 0; i < bullets.size(); ++i) {
        if (bulletDirection[i] && bullets[i].getCenterX() < width + 20) {
            bullets[i].setCenterX(bullets[i].getCenterX() + 7);
        } else if (!bulletDirection[i] && bullets[i].getCenterX() > -20) {
            bullets[i].setCenterX(bullets[i].getCenterX() - 7);
        }
        for (enemyNPC &e: enemies) {
            if (e.hitByBullet(bullets[i])) {
                e.setHealth(e.getHealth() - 10, 10);
                if (bulletDirection[i]) {
                    bullets[i].setCenterX(1010);
                } else {
                    bullets[i].setCenterX(-10);
                }
            }
            if (e.getHealth() <= 0 && e.isLiving()) {
                e.killed();
                menu.addMoney(10);
                menu.addEnemiesKilled();
            }
        }
    }

    //ENEMY part of timer
    if(diffScreens == gameScreen) {
        for (enemyNPC &enemy: enemies) {
            if (enemy.getPosition() == width / 2) {
                continue;
            } else if (enemy.getPosition() < width / 2 && enemy.isLiving()) {
                if (walls.size() > 1 && enemy.isOverlappingWall(walls)) {
                    enemy.moveLeft(20);
                }
                if (enemy.isOverlappingGem(gem, menu)) {
                    enemy.moveLeft(20);
                }
                enemy.moveRight(enemy.getSpeed());
            } else if (enemy.getPosition() > width / 2 && enemy.isLiving()) {
                if (enemy.isOverlappingWall(walls)) {
                    enemy.moveRight(20);
                }
                if (enemy.isOverlappingGem(gem, menu)) {
                    enemy.moveRight(20);
                }
                enemy.moveLeft(enemy.getSpeed());
            }
        }
        if (menu.getGemHealth() <= 0) {
            diffScreens = endScreen;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(20, enemyAndBulletTimer, dummy);
}

int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Fortnite 2.0000000000000001");

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, enemyAndBulletTimer, 0);
    glutTimerFunc(0, enemyWaveTimer, 0);
    //glutTimerFunc(0, bulletTimer, 0);
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}