#ifndef __DESTROYEDPLANET_H__
#define __DESTROYEDPLANET_H__

#include "./Planet.h"
#include "./Explorer.h"
#include <string>

class DestroyedPlanet : public Planet {
    private:
        static int numTot;
    public:
        DestroyedPlanet();
        void action(Explorer&) const;
        ~DestroyedPlanet();
};

#endif
