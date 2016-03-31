#include <iostream>
#include <math.h>

#include "Player.h"
#include "PhysicsComponent.h"
#include "PlayerInputComponent.h"
//#include "ShipComponent.h"

Player::Player (EventSystem * eventSystem) : Entity(eventSystem) {
    //ADD_COMPONENT(ShipComponent, eventSystem);
    ADD_COMPONENT(PhysicsComponent);
    ADD_COMPONENT(PlayerComponent);
    ADD_COMPONENT(PlayerInputComponent, eventSystem);
}