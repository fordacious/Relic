#include "Entity.h"

Component * Entity::addComponent(std::string typeName, Component * obj) {
    components[typeName] = obj;
    return obj;
}
Component * Entity::removeComponent(std::string typeName) {
    Component * c = components[typeName];
    components.erase(typeName);
    return c;
}
Component * Entity::getComponent(std::string typeName) {
    return components[typeName];
}

void Entity::update () {
    for_each (components.begin(), components.end(), [] (std::pair<std::string, Component *> pair) {
        pair.second->update();
    });
}