#include "Player.h"
#ifndef __GAME_H__
#define __GAME_H__

class Game {
    public:
        bool editMode;

        void update(int);
        void render();

        Game();

    private:
        Player player;
        //std::Vector<Enemy> enemies;
        //std::Vector<Entity> props;

        //ParticleSystem particleSystem;
};

#endif