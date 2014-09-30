#include "Vector2D.h"
#include "Component.h"

#ifndef __PHYSICSCOMPONENT_H__
#define __PHYSICSCOMPONENT_H__

class PhysicsComponent : public Component {
    public:
        PhysicsComponent();
        Vector2D<double> accel;
        Vector2D<double> vel;
        Vector2D<double> pos;
    protected:
        virtual void runStart ();
        virtual void runUpdate ();
};

#endif