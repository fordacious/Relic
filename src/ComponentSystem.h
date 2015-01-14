#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <map>
#include <string>

#include <SFML/System.hpp>

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

struct Transform {
    sf::Vector2<double> pos = sf::Vector2<double>(0, 0);
    sf::Vector2<double> scale = sf::Vector2<double>(0, 0);
    double rotation = 0;
};

class Entity {
    public:
        Component * addComponent(ComponentType, void *);
        Component * removeComponent(ComponentType);
        Component * getComponent(ComponentType);

        bool destroyed = false;

        // Transform
        Transform transform;

        virtual void update();

    private:
        std::map<std::string, Component *> components;
};

#endif