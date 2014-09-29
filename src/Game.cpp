#include <iostream>

#include <stdlib.h>
#include <math.h>

#include "Game.h"
#include "DisplayEntity.h"
#include "RenderUtils.h"

#define NUM_ENTITIES 20000

Game::Game ():player(Player()) {
    for (int i = 0 ; i < NUM_ENTITIES; i ++) {
        DisplayEntity * d = new DisplayEntity();
        d->r = (rand() / (double)RAND_MAX) * 1 + 0.5;
        d->g = (rand() / (double)RAND_MAX) * 1 + 0.5;
        d->b = (rand() / (double)RAND_MAX) * 1 + 0.5;
        d->pos.x = (rand() / (double)RAND_MAX) * 2 - 1;
        d->pos.y = (rand() / (double)RAND_MAX) * 2 - 1;
        d->vel.x = ((rand() / (double)RAND_MAX) * 2 - 1) / 50;
        d->vel.y = ((rand() / (double)RAND_MAX) * 2 - 1) / 50;
        entitiesTest.push_back((DisplayEntity *)this->addChild(d));
    }
}

void Game::render (RenderUtils::DisplayState ds) {
    DisplayObject::render(ds);
    RenderUtils::renderSquare (ds.mousePos, 1.5 / ds.width, 6 / ds.height, RenderUtils::Colour(0xff, 0xff, 0xff));
    RenderUtils::renderSquare (ds.mousePos, 6 / ds.width, 1.5 / ds.height, RenderUtils::Colour(0xff, 0xff, 0xff));
}

void Game::update (int currentFrame, Vector2D<double> mouse) {
    for_each (entitiesTest.begin(), entitiesTest.end(), [&] (DisplayEntity * curEntity) {
        curEntity->accel.x = (mouse.x - curEntity->pos.x) / 5000 / curEntity->size * 5;
        curEntity->accel.y = (mouse.y - curEntity->pos.y) / 5000 / curEntity->size * 5;
        curEntity->pos.x = fmin(1024, curEntity->pos.x);
        curEntity->pos.x = fmax(0, curEntity->pos.x);
        curEntity->update();
    });
}