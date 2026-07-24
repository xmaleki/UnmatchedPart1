#pragma once
#include "GameTypes.h"
#include <vector>

using namespace std;

class Hero;

class Space
{
    private:
        int Id;
        vector<ZoneTypes> zones;
        bool HaveSecretPassage = false;
        Hero* hero = nullptr;
        vector<Space *> AdjacentSpaces;

    public:
        Space(int id):Id(id){}
        bool IsSecretPassage() const;
        void SetSecretPassage(bool );
        int GetId() const;
        const std::vector<ZoneTypes>& GetZones() const;
        void AddZone(ZoneTypes);
        void SetHero(Hero* Hero);
        Hero* GetHero() const;
        bool IsHeroAvailable() const;
        void AddNeighbor(Space * neighbor);
        bool HasZone(const ZoneTypes&) const;
};