#ifndef __SHIPCOMPONENT_H__
#define __SHIPCOMPONENT_H__

#include <math.h>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "ComponentSystem.h"
#include "ShipPart.h"
#include "EventSystem.h"

// ship control
/*
you could use an analog stick to aim
and an analog trigger to boost
and some other buttons to shoot
or
you could use analog stick to boost+aim
and use a second analog stick to only aim
and use buttons to shoot
or
touch screen, this game can very well work on a tablet.
or
use a mouse cause its the best even though boost isnt analog.
*/

struct ShipState {
    bool BOOST = false;
    bool FIRE1 = false;
    bool FIRE2 = false;
};

class ShipComponent : public Component {
    public:
        ShipComponent(EventSystem *);
        ShipState shipState;
        int health;
        int energy;
        void installPart(int threshold, ShipPart part);
        // TODO how to store threshold energy levels for weapons...
        // easy to look up from a current energy level and etc.
    protected:
        virtual void runStart();
        virtual void runUpdate();
    private:
        std::vector<ShipPart*> parts;
        void handleMouseUp(MouseUpEvent *);
        void handleMouseDown(MouseDownEvent *);
        void boost();
        void fire1();
        void fire2();
};

#endif