#ifndef __PLAYERINPUTCOMPONENT_H__
#define __PLAYERINPUTCOMPONENT_H__

#include <SFML/System.hpp>
#include "ComponentSystem.h"
#include "EventSystem.h"
#include "PlayerComponent.h"

struct KeyboardState {
    bool W = false;
    bool A = false;
    bool S = false;
    bool D = false;
};

class PlayerInputComponent : public Component {
    public:
        PlayerInputComponent(EventSystem *);
        KeyboardState keyboardState;
    protected:
        virtual void runStart();
        virtual void runUpdate();
    private:
        void handleKeyDown(KeyDownEvent *);
        void handleKeyUp(KeyUpEvent *);
};

#endif