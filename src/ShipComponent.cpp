#include <iostream>

#include "PhysicsComponent.h"
#include "ShipComponent.h"

#include "ArtificialMouse.h"

// TODO: installPart, fire1, fire2

ShipComponent::ShipComponent (EventSystem * es) : Component() {
    es->on(EVENT(MouseDownEvent), [this](Event * e) {
        handleMouseDown((MouseDownEvent *) e);
    });
    es->on(EVENT(MouseUpEvent), [this](Event * e) {
        handleMouseUp((MouseUpEvent *) e);
    });
}

void installPart(int threshold, ShipPart part) {
  // store threshold and part slot
}

void ShipComponent::handleMouseUp(MouseUpEvent * e){
  if(e->mouseCode == MouseCode::Left){
    shipState.BOOST = false;
  }
}

void ShipComponent::handleMouseDown(MouseDownEvent * e){
  if(e->mouseCode == MouseCode::Left){
    shipState.BOOST = true;
  }
}

void ShipComponent::boost() {
    double x = 0;
    double y = 0;
    x = mousePos.x - entity->transform.pos.x;
    y = mousePos.y - entity->transform.pos.y;
    
    double length = sqrt(x*x + y*y);
    x /= length;
    y /= length;
    
    auto pc = GET_COMPONENT(entity, PhysicsComponent);
    pc->vel.x += x/2000;
    pc->vel.y += y/2000;
}

void ShipComponent::fire1(){
  // checks amount of energy and tells weapon to fire
  // this should always be your energy-bar-to-charge-level-item, consistent
}

void ShipComponent::fire2(){
  // this one is a little tricky, we're going to pass this function off to potential entities we spawn as well.
  // fire2 is our funky button
}

void ShipComponent::runStart(){
  health = 100;
  energy = 0;
}

// well, these things can change, 
// ints are fine since % remaining health damage is only if movement was not so important
void ShipComponent::runUpdate(){
  if(energy < 100){
    energy++;
  }
  if(shipState.BOOST == true){
    boost();
  }
  if(shipState.FIRE1 == true){
    fire1();
  }
  if(shipState.FIRE2 == true){
    fire2();
  }
}
