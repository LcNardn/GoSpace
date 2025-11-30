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
        void cooking(Explorer&) const;

    public:
        FirePlanet()=delete;
        FirePlanet(std::string,float,float);
        FirePlanet(const FirePlanet&);
        void action(Explorer&) const;
        std::string toString() const;
        ~FirePlanet();
};

#endif
