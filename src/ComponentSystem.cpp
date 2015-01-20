#include <iostream>
#include <algorithm>

#include "ComponentSystem.h"

namespace ComponentIdSystem {
    #include "ClassIdSystem.cpp"
}

// Components
void Component::update () {
    if (!initialised) {
        initialised = true;
        runStart();
    }
    runUpdate();
}

// Entities
Component * Entity::addComponent(ComponentType type, void * obj) {
    components[type] = (Component *)obj;
    ((Component *)obj)->entity = this;
    return (Component *)obj;
}
Component * Entity::removeComponent(ComponentType type) {
    Component * c = components[type];
    components.erase(type);
    return c;
}
Component * Entity::getComponent(ComponentType type) {
    return components[type];
}

Entity::Entity(EventSystem * es) : eventSystem(es) {}

void Entity::update() {
    for (auto pair : components) {
        pair.second->update();
    };
}