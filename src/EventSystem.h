#ifndef __EVENTSYSTEM_H__
#define __EVENTSYSTEM_H__

#include <vector>
#include <string>
#include <functional>
#include <map>

#include <SFML/Window.hpp>

//#include "ComponentSystem.h"

#define EVENT(X) #X

typedef std::string EventType;

//enum EventType {
//    TestEvent
//};

class Event {
    //Entity * target;
};

typedef sf::Keyboard::Key KeyCode;

class KeyboardEvent : public Event {
    public:
        int keyCode;
};

typedef std::function<void(Event *)> EventCallback;

class EventDispatcher {
    public:
        void on(EventType, EventCallback);
        void off(EventType);
        void dispatchEvent(EventType, Event *);
    private:
        std::map<EventType, EventCallback> eventMap;
};

typedef EventDispatcher EventSystem;

#endif