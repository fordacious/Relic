#include "Component.h"

void Component::update () {
    if (!initialised) {
        initialised = true;
        runStart();
    }
    runUpdate();
}