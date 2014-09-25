#include "Vector2D.h"

#ifndef __RENDERUTILS_H__
#define __RENDERUTILS_H__

namespace RenderUtils {

    struct Colour {
        int r; int g; int b;
        Colour (int r, int g, int b):r(r),g(g),b(b) {

        }
    };

    inline void renderSquare (Vector2D<double> & pos, double width, double height, Colour c) {
        glBegin(GL_QUADS);
            glColor3d(c.r,c.g,c.b);
            glVertex3f(pos.x-width,pos.y-height,0);
            glVertex3f(pos.x+width,pos.y-height,0);
            glVertex3f(pos.x+width,pos.y+height,0);
            glVertex3f(pos.x-width,pos.y+height,0);
        glEnd();
    }
}

#endif