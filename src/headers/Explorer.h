#ifndef __EXPLORER_H__
#define __EXPLORER_H__

#include <iostream>
#include <unordered_map>

typedef enum{
    fish,food,rocket,no_Rocket,mineral_1,mineral_2
} objType;

class Explorer{
    private:

        // limiti
        static const int oxInit;
        static const float enInit;
        static const float heInit;
        static const int maxCapacity;

        // statistiche
        int oxygen;
        float energy;
        float health;
        std::unordered_map<objType,int> inventory;

    public:

        // costruttori
        Explorer() noexcept;
        Explorer(const Explorer&) noexcept;
        Explorer(Explorer&&) noexcept =default;
        Explorer& operator=(const Explorer&) noexcept = default;
        Explorer& operator=(Explorer&&) noexcept = default;


        // getters
        float getEn() const noexcept;
        float getHe() const noexcept;

        // inventario
        Explorer& operator+=(objType) noexcept;
        Explorer& operator-=(objType); // throws logic_error
        bool shootRocket() noexcept;

        // health
        void damageShip(float); // throws logic_error
        bool repairShip() noexcept;

        // energy
        void rest(); // throws logic_error
        void consumeEnergy(float) noexcept;

        // oxygen
        Explorer operator++() noexcept;
        Explorer operator--(); // throws logic_error

        friend std::ostream& operator<<(std::ostream&,const Explorer&);

        ~Explorer() noexcept;
};

std::ostream& operator<<(std::ostream&,const Explorer&);

#endif
