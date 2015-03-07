#ifndef __COLLISIONCOMPONENT_H__
#define __COLLISIONCOMPONENT_H__

#include <SFML/System.hpp>
#include "ComponentSystem.h"
#include <vector>

// has a bunch of hitbox parts and then that composes the entire entities collision area

// then also has the function where you query if something hits, and if yes itll handle things

// so a hitbox component is going to ask: 

// hey entity do you have hitbox if yes i would like to compare for collision

// ideally any complicated hitbox has an encompassing radius anyway



// hey wait a minute, all our hitboxes are probably circle. =/=/

class CollisionComponent : public Component {

};

#endif
