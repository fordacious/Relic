#include <vector>
#include "Vector2D.h"
#ifndef __DISPLAYOBJECT_H__
#define __DISPLAYOBJECT_H__

class DisplayObject {
    public:
        DisplayObject * children;
        DisplayObject * addChild (DisplayObject*);
        DisplayObject * addChildAt (DisplayObject*, int);
        DisplayObject * removeChild (DisplayObject*);
        DisplayObject * removeChildAt (DisplayObject*, int);

        virtual void render(int) = 0;

};

#endif