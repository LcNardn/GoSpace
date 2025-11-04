#ifndef __WATERPLANET_H__
#define __WATERPLANET_H__

#include "./Planet.h"
#include "./Explorer.h"
#include <string>

class WaterPlanet : virtual public Planet{
    private:
        static int numTot;
    
    protected:
        int qFish;
        void fishing(Explorer&) const;

    public:
        WaterPlanet()=delete;
        WaterPlanet(std::string,int,float);
        WaterPlanet(const WaterPlanet&);
        void action(Explorer&) const;
        ~WaterPlanet();
};

#endif
