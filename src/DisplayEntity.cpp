#include <math.h>

#include <SFML/OpenGL.hpp>

#include "DisplayEntity.h"
#include "RenderUtils.h"

void DisplayEntity::render(int currentFrame) {
    //glTranslated(-this->pos.x, -this->pos.y, 0);
    //glRotated(this->rotation * 10 * 3.14159, 0, 0, 1);
    //glTranslated(this->pos.x, this->pos.y, 0);

    //double d = sin((double)currentFrame / 30) / 40 + 0.01;
    RenderUtils::renderSquare(this->pos, 0.001,0.001, 
        RenderUtils::Colour(this->r, this->g, this->b));
}