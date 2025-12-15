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

        void replentishO(Explorer&) const noexcept;
    
    public:
        SteamPlanet()=delete;
        SteamPlanet(std::string,int,float,int,float) noexcept;
        SteamPlanet(const SteamPlanet&) noexcept;
        void action(Explorer&) const noexcept;
        std::string toString() const noexcept;
        ~SteamPlanet();
};

#endif
