#include <algorithm>

#include "Entity.h"

Component * Entity::addComponent(ComponentType typeName, void * obj) {
    components[typeName] = (Component *) obj;
    return (Component *) obj;
}
Component * Entity::removeComponent(ComponentType typeName) {
    Component * c = components[typeName];
    components.erase(typeName);
    return c;
}
Component * Entity::getComponent(ComponentType typeName) {
    return components[typeName];
}

void Entity::update () {
    for_each (components.begin(), components.end(), [] (std::pair<ComponentType, Component *> pair) {
        pair.second->update();
    });
}