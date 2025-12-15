#ifndef __EARTHPLANET_H__
#define __EARTHPLANET_H__

#include "./Planet.h"
#include "./Explorer.h"
#include <string>

class EarthPlanet : virtual public Planet {
    private:
        static int numTot;

        objType chooseMineral(objType) noexcept;
    
    protected:
        const objType minType;
        void mining(Explorer&) const noexcept;
    
    public:
        EarthPlanet()=delete;
        EarthPlanet(std::string,objType,float) noexcept;
        EarthPlanet(const EarthPlanet&) noexcept;
        void action(Explorer&) const noexcept;
        std::string toString() const noexcept;
        ~EarthPlanet() noexcept;
};

#endif
