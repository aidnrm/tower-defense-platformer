//
// Created by Ty Allembert on 5/4/22.
//

#ifndef FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_BUTTON_H
#define FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_BUTTON_H

#include "Quad.h"
#include <string>

class Button : public Quad {
private:
    std::string label;
    quadColor originalFill, hoverFill, pressFill;

public:
    Button(quadColor fill, point center, unsigned int width, unsigned int height, std::string label);
    /* Uses OpenGL to draw the box with the label on top */
    virtual void draw() const override;

    /* Returns true if the coordinate is inside the box */
    bool isOverlapping(int x, int y) const;

    /* Change quadColor of the Button when the userHitDetector is hovering over it */
    void hover();

    /* Change quadColor of the Button when the userHitDetector is clicking on it */
    void pressDown();

    /* Change the quadColor back when the userHitDetector is not clicking/hovering */
    void release();
};


#endif //FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_BUTTON_H
