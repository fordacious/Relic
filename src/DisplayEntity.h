// renderable entity

#include "Entity.h"
#include "DisplayObject.h"

#ifndef __DISPLAYENTITY_H__
#define __DISPLAYENTITY_H__

class DisplayEntity : public Entity, public DisplayObject {
    public:
        int r;
        int g;
        int b;

        double size;

        DisplayEntity () {
            size = (rand() / (double)RAND_MAX) * 4;
        }

        virtual void render(RenderUtils::DisplayState);
};

#endif