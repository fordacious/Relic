#include <iostream>

#include "PlayerComponent.h"
#include "EventSystem.h"

PlayerComponent::PlayerComponent() : Component() {}

void PlayerComponent::moveUp() {
    entity->transform.pos.y += 0.01;
}

void PlayerComponent::moveDown() {
    entity->transform.pos.y -= 0.01;
}

void PlayerComponent::moveLeft() {
    entity->transform.pos.x -= 0.01;
}

void PlayerComponent::moveRight() {
    entity->transform.pos.x += 0.01;
}

void PlayerComponent::runStart() {}

void PlayerComponent::runUpdate() {}