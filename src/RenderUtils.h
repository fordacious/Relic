// Can probably keep all rendering code in here, or a "renderer" package

#include <iostream>
#include <SFML/System.hpp>

#include <SFML/OpenGL.hpp>

#ifndef __RENDERUTILS_H__
#define __RENDERUTILS_H__

namespace RenderUtils {

    struct Colour {
        int r; int g; int b;
        Colour (int r, int g, int b):r(r),g(g),b(b) {}
    };

    struct DisplayState {
        double width, height; 
        int currentFrame;
        sf::Vector2<double> mousePos;
        DisplayState (int w, int h, int cf, sf::Vector2<double> mp):
            width(w),height(h),currentFrame(cf),mousePos(mp) {};
    };

    // could potentially have multiple renderers
    static void init (double WIDTH, double HEIGHT) {
        glViewport(0, 0, WIDTH, HEIGHT);
        glOrtho(0, WIDTH, HEIGHT, 0, 0, 1000);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }

    static void resize (double w, double h) {
        glViewport(0, 0, w, h);
    }

    static void renderSquare (sf::Vector2<double> & pos, double width, double height, Colour c) {
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