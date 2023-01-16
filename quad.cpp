#include "Quad.h"
#include "graphics.h"

Quad::Quad() {
    fill = {0, 0, 0};
    center = {0, 0};
    width = 50;
    height = 50;
}

Quad::Quad(quadColor fill, point center, unsigned int width, unsigned int height) {
    this->fill = fill;
    this->center = center;
    this->width = width;
    this->height = height;
}


int Quad::getLeftX() const {
    return center.x - (width / 2);
}

int Quad::getRightX() const {
    return center.x + (width / 2);
}



int Quad::getTopY() const {
    return center.y - (height / 2);
}

int Quad::getBottomY() const {
    return center.y + (height / 2);
}


unsigned int Quad::getWidth() const {
    return width;
}

unsigned int Quad::getHeight() const {
    return height;
}

void Quad::setColor(double red, double green, double blue) {
    fill = {red, green, blue};
}

void Quad::setColor(quadColor fill) {
    this->fill = fill;
}

void Quad::move(int deltaX, int deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}

void Quad::resize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

void Quad::draw() const {
    // Implemented
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getRightX(), getTopY());
    glVertex2i(getRightX(),getBottomY());
    glVertex2i(getLeftX(), getBottomY());
    glEnd();
    // Don't forget to set the quadColor to the fill field
}