#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <map>
#include <string>

#include <SFML/System.hpp>

#include "DisplayObject.h"

#define GET_COMPONENT_TYPE(X) #X

class Entity;

class Component {
    public:
        Entity * entity;
        bool initialised = false;
        void update();
    protected:
        virtual void runStart () = 0;
        virtual void runUpdate () = 0;
};

typedef std::string ComponentType;

class Entity : public DisplayObject {
public:
    Component * addComponent(ComponentType, void *);
    Component * removeComponent(ComponentType);
    Component * getComponent(ComponentType);

    bool destroyed = false;

    virtual void update();

private:
    std::map<std::string, Component *> components;
};

#endif