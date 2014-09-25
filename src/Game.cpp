#include <math.h>

#include <SFML/OpenGL.hpp>

#include "Game.h"
#include "RenderUtils.h"

Game::Game ():player(Player()) {}

void Game::render () {
    double d = sin(this->player.size / 20) / 10;
    RenderUtils::renderSquare(this->player.pos, d,d, 
        RenderUtils::Colour(0x00, 0xaa, 0xcc));
}

void Game::update (int currentFrame) {
    this->player.size = currentFrame;
}