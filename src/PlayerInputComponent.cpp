#include <iostream>

#include "PlayerInputComponent.h"
#include "EventSystem.h"

PlayerInputComponent::PlayerInputComponent(EventSystem * es) : Component() {
    es->on(EVENT(KeyDownEvent), [this](Event * e) {
        handleKeyDown((KeyDownEvent *) e);
    });
    es->on(EVENT(KeyUpEvent), [this](Event * e) {
        handleKeyUp((KeyUpEvent *) e);
    });
}

void PlayerInputComponent::handleKeyDown(KeyDownEvent * event) {
    if (event->keyCode == KeyCode::W) {
        keyboardState.W = true;
    }
    else if (event->keyCode == KeyCode::S) {
        keyboardState.S = true;
    }
    else if (event->keyCode == KeyCode::A) {
        keyboardState.A = true;
    }
    else if (event->keyCode == KeyCode::D) {
        keyboardState.D = true;
    }
}

void PlayerInputComponent::handleKeyUp(KeyUpEvent * event) {
    if (event->keyCode == KeyCode::W) {
        keyboardState.W = false;
    }
    else if (event->keyCode == KeyCode::S) {
        keyboardState.S = false;
    }
    else if (event->keyCode == KeyCode::A) {
        keyboardState.A = false;
    }
    else if (event->keyCode == KeyCode::D) {
        keyboardState.D = false;
    }
}

void PlayerInputComponent::runStart() {}

void PlayerInputComponent::runUpdate() {
    if (keyboardState.W) {
        GET_COMPONENT(entity, PlayerComponent)->moveUp();
    }
    if (keyboardState.S) {
        GET_COMPONENT(entity, PlayerComponent)->moveDown();
    }
    if (keyboardState.A) {
        GET_COMPONENT(entity, PlayerComponent)->moveLeft();
    }
    if (keyboardState.D) {
        GET_COMPONENT(entity, PlayerComponent)->moveRight();
    }
}