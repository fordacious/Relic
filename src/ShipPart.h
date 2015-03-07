#ifndef __SHIPPART_H__
#define __SHIPPART_H__

// since abilities might scale based on how much energy, give energy so yeah.
// err.. they need to be able to spawn things...
// so have to query spawn component of entity. oh my.
class ShipPart {
    public:
      int minimumCost;
      Entity parent;
    protected:
      virtual void activate(int energy);
};

#endif