#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/System.hpp>

#include "DisplayObject.h"
#include "Player.h"
#include "Entity.h"

class Game : public DisplayObject {
    public:
        bool editMode;

        void update(int currentFrame, sf::Vector2<double> mousePosition);
        void render(RenderUtils::DisplayState);

        Game();

    private:
        Player player;
        std::vector<Entity *> entitiesTest;
        //std::Vector<Enemy> enemies;
        //std::Vector<Entity> props;

        //ParticleSystem particleSystem;
};

#endif