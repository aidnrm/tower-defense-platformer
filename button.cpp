#include "Button.h"
#include "graphics.h"
using namespace std;

Button::Button(quadColor fill, point center, unsigned int width, unsigned int height, std::string label) : Quad(fill, center, width, height) {
    this->label = label;
    originalFill = fill;
    hoverFill = {fill.red + 0.5, fill.green + 0.5, fill.blue + 0.5};
    pressFill = {fill.red - 0.5, fill.green - 0.5, fill.blue - 0.5};
}

void Button::draw() const {
    Quad::draw();
    glColor3f(0, 0, 0);
    glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
    for (const char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

/* Returns true if the coordinate is inside the box */
bool Button::isOverlapping(int x, int y) const {
    // Implement
    if(this->getLeftX() < x && this->getTopY() < y){
        if (this->getBottomY() > y && this->getRightX() > x){
            return true;
        }
    }
    return false; // Placeholder for compilation
}

/* Change quadColor of the box when the userHitDetector is hovering over it */
void Button::hover() {
    setColor(hoverFill);
}

/* Change quadColor of the box when the userHitDetector is clicking on it */
void Button::pressDown() {
    setColor(pressFill);
}

/* Change the quadColor back when the userHitDetector is not clicking/hovering */
void Button::release() {
    setColor(originalFill);
}