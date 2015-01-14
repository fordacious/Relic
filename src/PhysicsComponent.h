#ifndef __PHYSICSCOMPONENT_H__
#define __PHYSICSCOMPONENT_H__

#include <SFML/System.hpp>
#include "ComponentSystem.h"

class PhysicsComponent : public Component {
    public:
        PhysicsComponent();
        sf::Vector2<double> accel;
        sf::Vector2<double> vel;
        double mass = 0;
    protected:
        virtual void runStart ();
        virtual void runUpdate ();
};

#endif