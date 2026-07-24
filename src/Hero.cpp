#include "Hero.h"

using namespace std;

HeroesTeam Hero::GetTeam() const
{
    return HeroTeam;
}

int Hero::GetId() const
{
    return id;
}

AttackType Hero::GetAttackType() const
{
    return attacktype;
}