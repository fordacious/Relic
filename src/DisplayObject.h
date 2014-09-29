// renderable object

#include <vector>
#include "Vector2D.h"
#include "RenderUtils.h"

#ifndef __DISPLAYOBJECT_H__
#define __DISPLAYOBJECT_H__

class DisplayObject {
    public:
        std::vector<DisplayObject*> children;
        DisplayObject * addChild (DisplayObject*);
        DisplayObject * addChildAt (DisplayObject*, int);
        DisplayObject * removeChild (DisplayObject*);
        DisplayObject * removeChildAt (int);

        virtual void render(RenderUtils::DisplayState);

    private:
        int getChildPos(DisplayObject*);
};

#endif