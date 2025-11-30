#ifndef __INDUSTRYPLANET_H__
#define __INDUSTRYPLANET_H__

#include "./FirePlanet.h"
#include "./EarthPlanet.h"
#include "./Explorer.h"
#include <string>

class IndustryPlanet : public FirePlanet, public EarthPlanet{
    private:
        static int numTot;

        void makeRockets(Explorer&) const;
    
    public:
        IndustryPlanet()=delete;
        IndustryPlanet(std::string,float,objType,float);
        IndustryPlanet(const IndustryPlanet&);
        void action(Explorer&) const;
        std::string toString() const;
        ~IndustryPlanet();
};

#endif
