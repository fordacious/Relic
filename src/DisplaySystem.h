#ifndef __DISPLAYOBJECT_H__
#define __DISPLAYOBJECT_H__

#include <vector>
#include <SFML/System.hpp>
#include "RenderUtils.h"
#include "ComponentSystem.h"

class DisplayObject {
    public:

        DisplayObject * parent;

        Entity * entity;

        std::vector<DisplayObject*> children;
        DisplayObject * addChild (DisplayObject*);
        DisplayObject * addChildAt (DisplayObject*, int);
        DisplayObject * removeChild (DisplayObject*);
        DisplayObject * removeChildAt (int);

        double alpha = 0;
        RenderUtils::Colour colour = RenderUtils::Colour(0, 0, 0);

        bool visible = true;

        virtual void render(RenderUtils::DisplayState);

    private:
        int getChildPos(DisplayObject*);
};

class Stage : public DisplayObject {};

#endif