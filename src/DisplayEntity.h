#include "Entity.h"
#include "DisplayObject.h"

#ifndef __DISPLAYENTITY_H__
#define __DISPLAYENTITY_H__

class DisplayEntity : public Entity, public DisplayObject {
    public:
        int r;
        int g;
        int b;
        virtual void render(int);
};

#endif