#include "Entity.h"

void Entity::update () {
    this->vel.x += this->accel.x;
    this->vel.y += this->accel.y;
    this->pos.x += this->vel.x;
    this->pos.y += this->vel.y;
}