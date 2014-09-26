#include "Vector2D.h"

#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity {
    public:
        Vector2D<double> accel;
        Vector2D<double> vel;
        Vector2D<double> pos;

        double rotation = 0;

        virtual void update();
};

#endif