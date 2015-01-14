#ifndef __DISPLAYOBJECT_H__
#define __DISPLAYOBJECT_H__

#include <vector>
#include <SFML/System.hpp>
#include "RenderUtils.h"

class DisplayObject {
    public:
        std::vector<DisplayObject*> children;
        DisplayObject * addChild (DisplayObject*);
        DisplayObject * addChildAt (DisplayObject*, int);
        DisplayObject * removeChild (DisplayObject*);
        DisplayObject * removeChildAt (int);

        sf::Vector2<double> pos = sf::Vector2<double>(0,0);
        sf::Vector2<double> scale = sf::Vector2<double>(0, 0);
        double rotation = 0;
        double alpha = 0;
        RenderUtils::Colour colour = RenderUtils::Colour(0, 0, 0);

        bool visible = true;

        virtual void render(RenderUtils::DisplayState);

    private:
        int getChildPos(DisplayObject*);
};

#endif