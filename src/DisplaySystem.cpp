#include <algorithm>

#include "DisplaySystem.h"

using namespace std;

DisplayObject * DisplayObject::addChild (DisplayObject * obj) {
    children.push_back(obj);
    obj->parent = this;
    obj->stage = stage;
    return obj;
}
DisplayObject * DisplayObject::addChildAt (DisplayObject * obj, int i) {
    children.insert(children.begin() + i, obj);
    return obj;
}
DisplayObject * DisplayObject::removeChild (DisplayObject * obj) {
    children.erase(children.begin() + getChildPos(obj));
    obj->parent = NULL;
    return obj;
}
DisplayObject * DisplayObject::removeChildAt (int i) {
    DisplayObject * obj = children[i];
    children.erase(children.begin() + i);
    obj->parent = NULL;
    return obj;
}

void DisplayObject::render (RenderUtils::DisplayState ds) {
    for (auto child : children) {
        child->render(ds);
    };
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