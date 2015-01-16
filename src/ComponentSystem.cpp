#include <algorithm>

#include "ComponentSystem.h"

// Components
void Component::update () {
    if (!initialised) {
        initialised = true;
        runStart();
    }
    runUpdate();
}

// Entities
Component * Entity::addComponent(ComponentType typeName, void * obj) {
    components[typeName] = (Component *)obj;
    ((Component *)obj)->entity = this;
    return (Component *)obj;
}
Component * Entity::removeComponent(ComponentType typeName) {
    Component * c = components[typeName];
    components.erase(typeName);
    return c;
}
Component * Entity::getComponent(ComponentType typeName) {
    return components[typeName];
}

Entity::Entity(EventSystem * es) : eventSystem(es) {}

void Entity::update() {
    for (auto pair : components) {
        pair.second->update();
    };
}