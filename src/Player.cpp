#include <math.h>

#include "Player.h"
#include "PhysicsComponent.h"

Player::Player () {
    addComponent(GET_COMPONENT_TYPE(PhysicsComponent), new PhysicsComponent());
}

void Player::render (RenderUtils::DisplayState ds) {
    DisplayEntity::render(ds);
}

void Player::update () {
    Entity::update();
}