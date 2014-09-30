#include <math.h>

#include "Player.h"
#include "PhysicsComponent.h"

Player::Player () {
    PhysicsComponent * pc = new PhysicsComponent();
    addComponent(GET_COMPONENT_TYPE(PhysicsComponent), (Component *) pc);
}

void Player::render (RenderUtils::DisplayState ds) {
    DisplayEntity::render(ds);
}

void Player::update () {
    Entity::update();
}