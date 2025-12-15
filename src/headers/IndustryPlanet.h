#ifndef __INDUSTRYPLANET_H__
#define __INDUSTRYPLANET_H__

#include "./FirePlanet.h"
#include "./EarthPlanet.h"
#include "./Explorer.h"
#include <string>

class IndustryPlanet : public FirePlanet, public EarthPlanet{
    private:
        static int numTot;

        void makeRockets(Explorer&) const noexcept;
    
    public:
        IndustryPlanet()=delete;
        IndustryPlanet(std::string,float,objType,float) noexcept;
        IndustryPlanet(const IndustryPlanet&) noexcept;
        void action(Explorer&) const noexcept;
        std::string toString() const noexcept;
        ~IndustryPlanet();
};

#endif
