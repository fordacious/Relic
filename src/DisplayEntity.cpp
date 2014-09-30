
#include <stdlib.h>
#include <math.h>

#include <SFML/OpenGL.hpp>

#include "DisplayEntity.h"
#include "RenderUtils.h"
#include "PhysicsComponent.h"

void DisplayEntity::render(RenderUtils::DisplayState ds) {
    //glTranslated(-pos.x, -pos.y, 0);
    //glRotated(rotation * 10 * 3.14159, 0, 0, 1);
    //glTranslated(pos.x, pos.y, 0);

    //double d = sin((double)currentFrame / 30) / 40 + 0.01;
    RenderUtils::renderSquare(((PhysicsComponent *)getComponent(GET_COMPONENT_TYPE(PhysicsComponent)))->pos, 
        size / ds.width, size / ds.height, 
        RenderUtils::Colour(r, g, b));
}