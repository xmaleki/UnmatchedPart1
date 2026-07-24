#include "Space.h"

bool Space::IsSecretPassage() const
{
    return HaveSecretPassage; 
}

void Space::SetSecretPassage(bool secret)
{
    HaveSecretPassage = secret;
}

int Space::GetId() const
{
    return Id;
}

const std::vector<ZoneTypes>& Space::GetZones() const
{
    return zones;
}

void Space::SetHero(Hero* Hero)
{
    hero = Hero;
}

Hero* Space::GetHero() const
{
    return hero; 
}

bool Space::IsHeroAvailable() const
{
    return !(hero == nullptr);
}

void Space::AddZone(ZoneTypes zone)
{
    zones.push_back(zone);
}

void Space::AddNeighbor(Space* neighbor)
{
    AdjacentSpaces.push_back(neighbor);
}

bool Space::HasZone(const ZoneTypes &zone) const
{
    for(const auto &z : zones)
    {
        if(z == zone)
            return true;
    }
    return false;
}