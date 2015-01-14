#include <iostream>
#include <algorithm>

#include <stdlib.h>
#include <math.h>

#include "Game.h"
#include "RenderUtils.h"
#include "PhysicsComponent.h"

#define NUM_ENTITIES 1000

Game::Game () {

    // TODO, could put things like shrapnel and particles on separate thread as its inert
    // each update, incrememnt 'updatesToPerform' on each thread. Threads then perform that
    // amount of updates next frame.

    player = Player();

    for (int i = 0 ; i < NUM_ENTITIES; i ++) {
        Entity * d = new Entity();

        PhysicsComponent * pc = 
            (PhysicsComponent *)d->addComponent(GET_COMPONENT_TYPE(PhysicsComponent), 
                new PhysicsComponent());

        d->colour.r = (rand() / (double)RAND_MAX) * 1 + 0.5;
        d->colour.g = (rand() / (double)RAND_MAX) * 1 + 0.5;
        d->colour.b = (rand() / (double)RAND_MAX) * 1 + 0.5;

        pc->mass = (rand() / (double)RAND_MAX * 5);

        entitiesTest.push_back((Entity *)this->addChild((DisplayObject *)d));
    }
}

void Game::render (RenderUtils::DisplayState ds) {
    DisplayObject::render(ds);
    RenderUtils::renderSquare (ds.mousePos, 1.5 / ds.width, 6 / ds.height, RenderUtils::Colour(0xff, 0xff, 0xff));
    RenderUtils::renderSquare (ds.mousePos, 6 / ds.width, 1.5 / ds.height, RenderUtils::Colour(0xff, 0xff, 0xff));
    for_each(entitiesTest.begin(), entitiesTest.end(), [ds] (Entity * curEntity) {
        PhysicsComponent * pc = (PhysicsComponent *)curEntity->getComponent(GET_COMPONENT_TYPE(PhysicsComponent));
        RenderUtils::renderSquare(curEntity->pos, pc->mass / ds.width, pc->mass / ds.height, curEntity->colour);
    });
}

void Game::update (int currentFrame, sf::Vector2<double> mouse) {
    for_each (entitiesTest.begin(), entitiesTest.end(), [mouse] (Entity * curEntity) {
        PhysicsComponent * physComponent = (PhysicsComponent *)curEntity->getComponent(GET_COMPONENT_TYPE(PhysicsComponent));
        physComponent->accel.x = (mouse.x - curEntity->pos.x) / 5000 * 5 * physComponent->mass;
        physComponent->accel.y = (mouse.y - curEntity->pos.y) / 5000 * 5 * physComponent->mass;
        curEntity->update();
    });
}