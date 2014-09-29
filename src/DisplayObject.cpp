#include "DisplayObject.h"

DisplayObject * DisplayObject::addChild (DisplayObject * obj) {
    children.push_back(obj);
    return obj;
}
DisplayObject * DisplayObject::addChildAt (DisplayObject * obj, int i) {
    children.insert(children.begin() + i, obj);
    return obj;
}
DisplayObject * DisplayObject::removeChild (DisplayObject * obj) {
    children.erase(children.begin() + getChildPos(obj));
    return obj;
}
DisplayObject * DisplayObject::removeChildAt (int i) {
    DisplayObject * obj = children[i];
    children.erase(children.begin() + i);
    return obj;
}

void DisplayObject::render (RenderUtils::DisplayState ds) {
    for_each (children.begin(), children.end(), [ds] (DisplayObject * child) {
        child->render(ds);
    });
}

int DisplayObject::getChildPos (DisplayObject * obj) {
    int sz = children.size();
    for (int i = 0; i < sz; i ++) {
        if (children[i] == obj) {
            return i;
        }
    }
    throw "Object not in display list";
}