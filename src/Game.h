#include "DisplayObject.h"
#include "Player.h"
#include "Vector2D.h"
#include "DisplayEntity.h"
#ifndef __GAME_H__
#define __GAME_H__

class Game : public DisplayObject {
    public:
        bool editMode;

        void update(int,Vector2D<double>);
        void render(int);

        Game();

    private:
        Player player;
        std::vector<DisplayEntity *> entitiesTest;
        //std::Vector<Enemy> enemies;
        //std::Vector<Entity> props;

        //ParticleSystem particleSystem;
};

#endif