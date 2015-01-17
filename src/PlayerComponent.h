#ifndef __PLAYERCOMPONENT_H__
#define __PLAYERCOMPONENT_H__

#include <SFML/System.hpp>
#include "ComponentSystem.h"

class PlayerComponent : public Component {
    public:
        PlayerComponent();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
    protected:
        virtual void runStart();
        virtual void runUpdate();
};

#endif