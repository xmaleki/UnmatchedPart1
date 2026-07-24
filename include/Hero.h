#pragma once
#include "GameTypes.h"
#include <string>



class Hero
{
    private:
        std::string Name;
        int id;
        HeroesTeam HeroTeam;
        int HP;
        AttackType attacktype;
        int MaxHP;
        CardOwner OwnerType;

    public:
        Hero(std::string name, int Id, HeroesTeam Team, int hp, AttackType attack, int maxhp, CardOwner owner) : id(Id), HeroTeam(Team), HP(hp),
        attacktype(attack), Name(name), MaxHP(maxhp), OwnerType(owner)  {}
        void SetId(int);
        int GetId() const;
        void SetTeamId(int);
        HeroesTeam GetTeam() const;
        virtual void SpecialAbility(Board&, Map&, Player*) = 0;
        AttackType GetAttackType() const;
        void SetAttackType(AttackType);
        std::string GetName() const;
        bool IsDead() const;
        void TakeDamage(int);
        void Heal(int);
        CardOwner GetOwnerType() const;
        int GetHP() const;
};