#include <math.h>

#include "Player.h"
#include "PhysicsComponent.h"
#include "PlayerInputComponent.h"

Player::Player (EventSystem * eventSystem) : Entity(eventSystem) {
    ADD_COMPONENT(PhysicsComponent);
    ADD_COMPONENT(PlayerComponent);
    ADD_COMPONENT(PlayerInputComponent, eventSystem);
}