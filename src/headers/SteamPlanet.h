#ifndef __STEAMPLANET_H__
#define __STEAMPLANET_H__

#include "./FirePlanet.h"
#include "./WaterPlanet.h"
#include "./Explorer.h"
#include <string>

class SteamPlanet : public FirePlanet, public WaterPlanet {
    private:
        static int numTot;
        const int capacityO;

        void replentishO(Explorer&) const;
    
    public:
        SteamPlanet()=delete;
        SteamPlanet(std::string,int,float,int,float);
        SteamPlanet(const SteamPlanet&);
        void action(Explorer&) const;
        std::string toString() const;
        ~SteamPlanet();
};

#endif
