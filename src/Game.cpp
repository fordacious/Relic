#include <iostream>
#include <algorithm>

#include <stdlib.h>
#include <math.h>

#include "Game.h"
#include "RenderUtils.h"
#include "PhysicsComponent.h"
#include "DisplaySystem.h"
#include "EventSystem.h"

#define NUM_ENTITIES 1000

class TestRenderer : public DisplayObject {
    void render(RenderUtils::DisplayState ds) {
        auto pc = GET_COMPONENT(entity, PhysicsComponent);
        RenderUtils::renderSquare(entity->transform.pos, pc->mass / ds.width, pc->mass / ds.height, colour);
    }
};

Game::Game () {

    // TODO, could put things like shrapnel and particles on separate thread as its inert
    // each update, incrememnt 'updatesToPerform' on each thread. Threads then perform that
    // amount of updates next frame.

    stage = new Stage();
    stage->stage = stage;

    eventSystem = new EventSystem();

    player = new Player(eventSystem);

    for (int i = 0 ; i < NUM_ENTITIES; i ++) {
        Entity * d = new Entity(eventSystem);

        auto pc = (PhysicsComponent *)d->addComponent(GET_COMPONENT_TYPE(PhysicsComponent), new PhysicsComponent());

        auto tr = (TestRenderer *)stage->addChild(new TestRenderer());
        tr->entity = d;

        tr->colour.r = (rand() / (double)RAND_MAX) * 1 + 0.5;
        tr->colour.g = (rand() / (double)RAND_MAX) * 1 + 0.5;
        tr->colour.b = (rand() / (double)RAND_MAX) * 1 + 0.5;

        pc->mass = (rand() / (double)RAND_MAX * 5);

        entitiesTest.push_back(d);
    }

    auto tr = new TestRenderer();
    stage->addChild(tr)->entity = player;
    auto pc = GET_COMPONENT(player, PhysicsComponent);
    pc->mass = 20;
    tr->colour.r = 255;
}

void Game::render (RenderUtils::DisplayState ds) {
    stage->render(ds);
    RenderUtils::renderSquare (ds.mousePos, 1.5 / ds.width, 6 / ds.height, RenderUtils::Colour(0xff, 0xff, 0xff));
    RenderUtils::renderSquare (ds.mousePos, 6 / ds.width, 1.5 / ds.height, RenderUtils::Colour(0xff, 0xff, 0xff));
}

void Game::update (int currentFrame, sf::Vector2<double> mouse) {
    for (auto curEntity : entitiesTest) {
        auto physComponent = GET_COMPONENT(curEntity, PhysicsComponent);
        physComponent->accel.x = (mouse.x - curEntity->transform.pos.x) / 5000 * 5 * physComponent->mass;
        physComponent->accel.y = (mouse.y - curEntity->transform.pos.y) / 5000 * 5 * physComponent->mass;
        curEntity->update();
    };

    player->update();
}

void Game::handleSFEvent(sf::Event event) {
    // TODO convert to relic event and dispatch
    if (event.type == sf::Event::KeyPressed) {
        KeyDownEvent e;
        e.keyCode = event.key.code;
        eventSystem->dispatchEvent(EVENT(KeyDownEvent), (Event *)&e);
    }
    else if (event.type == sf::Event::KeyReleased) {
        KeyUpEvent e;
        e.keyCode = event.key.code;
        eventSystem->dispatchEvent(EVENT(KeyUpEvent), (Event *)&e);
    }
}