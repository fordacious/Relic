// game entity

#include <map>
#include <string>
#include "Component.h"

#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity {
    public:
        Component * addComponent(std::string typeName, Component *);
        Component * removeComponent(std::string typeName);
        Component * getComponent(std::string typeName);

        std::map<std::string, Component *> components;

        double rotation = 0;

        virtual void update();
};

#endif