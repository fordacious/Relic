#include <iostream>

#include <stdlib.h>
#include <math.h>

#include "Game.h"
#include "DisplayEntity.h"
#include "RenderUtils.h"

#define NUM_ENTITIES 10000

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
        entitiesTest.push_back(d);
    }

}

void Game::render (int currentFrame) {
    DisplayEntity * curEntity;
    for (int i = 0 ; i < NUM_ENTITIES; i ++) {
        entitiesTest[i]->render(currentFrame);
    }
}

void Game::update (int currentFrame, Vector2D<double> mouse) {
    DisplayEntity * curEntity;
    for (int i = 0 ; i < NUM_ENTITIES; i ++) {
        curEntity = entitiesTest[i];
        curEntity->accel.x = (mouse.x - curEntity->pos.x) / 2000;
        curEntity->accel.y = (mouse.y - curEntity->pos.y) / 2000;
        curEntity->update();
    }
}