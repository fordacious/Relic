#include <iostream>

#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent () : Component() {}

void PhysicsComponent::runStart () {
    accel.x = 0;
    accel.y = 0;
    vel.x   = 0;
    vel.y   = 0;
    entity->transform.pos.x = 0;
    entity->transform.pos.y = 0;
}

void PhysicsComponent::runUpdate () {
    vel.x += accel.x;
    vel.y += accel.y;
    entity->transform.pos.x += vel.x;
    entity->transform.pos.y += vel.y;
}