// TODO probably include game in update funcs

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#define GET_COMPONENT_TYPE(X) #X

class Component {
    public:
        bool initialised;
        void update();
        Component ();
    protected:
        virtual void runStart () = 0;
        virtual void runUpdate () = 0;
};

#endif