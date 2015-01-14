// game entity

#include <map>
#include <string>
#include "Component.h"

#ifndef __ENTITY_H__
#define __ENTITY_H__

typedef std::string ComponentType;

class Entity {
    public:
        Component * addComponent(ComponentType, void *);
        Component * removeComponent(ComponentType);
        Component * getComponent(ComponentType);

        std::map<std::string, Component *> components;

        bool destroyed = false;

        virtual void update();
};

#endif