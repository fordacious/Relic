#include <iostream>

#include <stdlib.h>
#include <math.h>

#include "Game.h"
#include "DisplayEntity.h"
#include "RenderUtils.h"
#include "PhysicsComponent.h"

#define NUM_ENTITIES 20000

Game::Game () {

    player = Player();

    for (int i = 0 ; i < NUM_ENTITIES; i ++) {
        DisplayEntity * d = new DisplayEntity();

        PhysicsComponent * pc = 
            (PhysicsComponent *)d->addComponent(GET_COMPONENT_TYPE(PhysicsComponent), 
                (Component *)new PhysicsComponent());

        d->r = (rand() / (double)RAND_MAX) * 1 + 0.5;
        d->g = (rand() / (double)RAND_MAX) * 1 + 0.5;
        d->b = (rand() / (double)RAND_MAX) * 1 + 0.5;

        pc->pos.x = (rand() / (double)RAND_MAX) * 2 - 1;
        pc->pos.y = (rand() / (double)RAND_MAX) * 2 - 1;
        pc->vel.x = ((rand() / (double)RAND_MAX) * 2 - 1) / 50;
        pc->vel.y = ((rand() / (double)RAND_MAX) * 2 - 1) / 50;

        entitiesTest.push_back((DisplayEntity *)this->addChild(d));
    }
}

void Game::render (RenderUtils::DisplayState ds) {
    DisplayObject::render(ds);
    RenderUtils::renderSquare (ds.mousePos, 1.5 / ds.width, 6 / ds.height, RenderUtils::Colour(0xff, 0xff, 0xff));
    RenderUtils::renderSquare (ds.mousePos, 6 / ds.width, 1.5 / ds.height, RenderUtils::Colour(0xff, 0xff, 0xff));
}

void Game::update (int currentFrame, Vector2D<double> mouse) {
    for_each (entitiesTest.begin(), entitiesTest.end(), [mouse] (DisplayEntity * curEntity) {
        PhysicsComponent * physComponent = (PhysicsComponent *)curEntity->getComponent(GET_COMPONENT_TYPE(PhysicsComponent));
        physComponent->accel.x = (mouse.x - physComponent->pos.x) / 5000 / curEntity->size * 5;
        physComponent->accel.y = (mouse.y - physComponent->pos.y) / 5000 / curEntity->size * 5;
        physComponent->pos.x = fmin(1024, physComponent->pos.x);
        physComponent->pos.x = fmax(0, physComponent->pos.x);
        curEntity->update();
    });
}