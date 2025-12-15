#ifndef __FIREPLANET_H__
#define __FIREPLANET_H__

#include "./Planet.h"
#include "./Explorer.h"
#include <string>

class FirePlanet : virtual public Planet{
    private:
        static int numTot;
    
    protected:
        const float energySup;
        void cooking(Explorer&) const noexcept;

    public:
        FirePlanet()=delete;
        FirePlanet(std::string,float,float) noexcept;
        FirePlanet(const FirePlanet&) noexcept;
        void action(Explorer&) const noexcept;
        std::string toString() const noexcept;
        ~FirePlanet() noexcept;
};

#endif
