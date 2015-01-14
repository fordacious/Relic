// renderable entity

#include "Entity.h"
#include "DisplayObject.h"
#include "RenderUtils.h"

#ifndef __DISPLAYENTITY_H__
#define __DISPLAYENTITY_H__

using namespace RenderUtils;

class DisplayEntity : public Entity, public DisplayObject {
    public:
        Colour colour = Colour(0,0,0);

        double size;

        bool visible = true;

        DisplayEntity () {
            size = (rand() / (double)RAND_MAX) * 4;
        }

        virtual void render(RenderUtils::DisplayState);
};

#endif