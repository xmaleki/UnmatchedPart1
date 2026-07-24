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

void Hero::SetAttackType(AttackType attack)
{
    attacktype = attack;
}

string Hero::GetName() const
{
    return Name;
}

bool Hero::IsDead() const
{
    return HP <= 0;
}
