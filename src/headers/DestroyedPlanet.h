#ifndef __DESTROYEDPLANET_H__
#define __DESTROYEDPLANET_H__

#include "./Planet.h"
#include "./Explorer.h"
#include <string>

class DestroyedPlanet : public Planet {
    public:
        DestroyedPlanet() noexcept;
        void action(Explorer&) const noexcept;
        ~DestroyedPlanet() noexcept;
};

#endif
