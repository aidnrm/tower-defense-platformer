//
// Created by Ty Allembert on 5/4/22.
//

#ifndef FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_QUAD_H
#define FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_QUAD_H

struct quadColor {
    double red;
    double green;
    double blue;
};

struct point {
    int x;
    int y;
};

class Quad {
protected:
    quadColor fill;
    point center;
    unsigned int width;
    unsigned int height;

public:
    Quad();
    Quad(quadColor fill, point center, unsigned int width, unsigned int height);

    int getLeftX() const;
    int getRightX() const;
    int getTopY() const;
    int getBottomY() const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    void setColor(double red, double green, double blue);
    void setColor(quadColor fill);
    void move(int deltaX, int deltaY);
    void resize(unsigned int width, unsigned int height);

    virtual void draw() const;
};


#endif //FINAL_PROJECT_TALEMBE_NLALOR_AMCCORM2_QUAD_H
