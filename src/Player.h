// entity of type player

#include "Entity.h"
#include "DisplayEntity.h"
#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player : public DisplayEntity {
    public:
        double size;

        void update();
        void render(RenderUtils::DisplayState);
};

#endif