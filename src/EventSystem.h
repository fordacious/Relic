#ifndef __EVENTSYSTEM_H__
#define __EVENTSYSTEM_H__

#include <vector>
#include <string>
#include <functional>
#include <map>

#include <SFML/Window.hpp>

#define EVENT(TYPE) EventIdSystem::getId<TYPE>()

// generates a unique id for each event
namespace EventIdSystem {
    #include "ClassIdSystem.h"
}

typedef int EventType;

struct Event {};

typedef sf::Keyboard::Key KeyCode;

typedef sf::Mouse::Button MouseCode;

struct KeyboardEvent : public Event {
    int keyCode;
};

struct MouseEvent : public Event {
    int mouseCode;
};

struct KeyDownEvent : public KeyboardEvent {};
struct KeyUpEvent : public KeyboardEvent {};
struct MouseDownEvent : public MouseEvent {};
struct MouseUpEvent : public MouseEvent {};

typedef std::function<void(Event *)> EventCallback;

class EventDispatcher {
    public:
        void on(EventType, EventCallback);
        void off(EventType);
        void dispatchEvent(EventType, Event *);
    private:
        // TODO very inefficient, replace with component enum as index and lookup an array
        std::map<EventType, EventCallback> eventMap;
};

typedef EventDispatcher EventSystem;

#endif