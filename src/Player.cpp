#include <math.h>

#include "Player.h"
#include "PhysicsComponent.h"

Player::Player (EventSystem * eventSystem) : Entity(eventSystem) {
    ADD_COMPONENT(PhysicsComponent);
    // TODO ADD_COMPONENT(PlayerInputComponent);
    eventSystem->on(EVENT(KeyboardEvent), [&](Event * e) {
        handleKeyboardInput((KeyboardEvent *)e);
    });
}

void Player::handleKeyboardInput(KeyboardEvent * event) {
    if (event->keyCode == KeyCode::W) {
        transform.pos.y += 0.01;
    }
    else if (event->keyCode == KeyCode::S) {
        transform.pos.y -= 0.01;
    }
    else if (event->keyCode == KeyCode::A) {
        transform.pos.x -= 0.01;
    }
    else if (event->keyCode == KeyCode::D) {
        transform.pos.x += 0.01;
    }
}