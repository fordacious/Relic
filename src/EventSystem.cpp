#include "EventSystem.h"

namespace EventIdSystem {
    #include "ClassIdSystem.cpp"
}

void EventDispatcher::on(EventType type, EventCallback callback){
    eventMap[type] = callback;
}

void EventDispatcher::off(EventType type) {
    eventMap.erase(type);
}

void EventDispatcher::dispatchEvent(EventType type, Event * event) {
    if (eventMap.find(type) != eventMap.end()) {
        eventMap[type](event);
    }
}