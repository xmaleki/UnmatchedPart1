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

void Hero::TakeDamage(int dam)
{
    HP -= dam;
    if(HP < 0)
        HP = 0;
}

void Hero::Heal(int heal)
{
    HP += heal;
    
    if(HP >= MaxHP)
        HP = MaxHP;
}

CardOwner Hero::GetOwnerType() const
{
    return OwnerType;
}


int Hero::GetHP() const
{
    return HP;
}