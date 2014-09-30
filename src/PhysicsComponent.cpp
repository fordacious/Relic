#include <iostream>

#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent () : Component() {}

void PhysicsComponent::runStart () {
    this->accel.x = 0;
    this->accel.y = 0;
    this->vel.x   = 0;
    this->vel.y   = 0;
    this->pos.x   = 0;
    this->pos.y   = 0;
}

void PhysicsComponent::runUpdate () {
    this->vel.x += this->accel.x;
    this->vel.y += this->accel.y;
    this->pos.x += this->vel.x;
    this->pos.y += this->vel.y;
}