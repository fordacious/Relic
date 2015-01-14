#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "ComponentSystem.h"

class Player : public Entity {
    public:
        Player();
        double size;
    protected:
        void update();
};

#endif