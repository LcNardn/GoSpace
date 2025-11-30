#ifndef __EARTHPLANET_H__
#define __EARTHPLANET_H__

#include "./Planet.h"
#include "./Explorer.h"
#include <string>

class EarthPlanet : virtual public Planet {
    private:
        static int numTot;

        objType chooseMineral(objType);
    
    protected:
        const objType minType;
        void mining(Explorer&) const;
    
    public:
        EarthPlanet()=delete;
        EarthPlanet(std::string,objType,float);
        EarthPlanet(const EarthPlanet&);
        void action(Explorer&) const;
        std::string toString() const;
        ~EarthPlanet();
};

#endif
