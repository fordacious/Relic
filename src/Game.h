#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "DisplaySystem.h"
#include "Player.h"
#include "ComponentSystem.h"
#include "EventSystem.h"

class Game {
    public:
        Stage * stage;
        EventSystem * eventSystem;

        void update(int currentFrame, sf::Vector2<double> mousePosition);
        void render(RenderUtils::DisplayState);

        Game();

        void handleSFEvent(sf::Event event);

    private:
        Player * player;
        std::vector<Entity *> entitiesTest;
        //std::Vector<Enemy> enemies;
        //std::Vector<Entity> props;

        //ParticleSystem particleSystem;
};

#endif