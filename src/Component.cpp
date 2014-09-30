#include "Component.h"

Component::Component () {
    initialised = false;
}

void Component::update () {
    if (!initialised) {
        initialised = true;
        runStart();
    }
    runUpdate();
}