#include "Hero.h"
#include "GameTypes.h"
#include <string>

class Sherlock : public Hero
{
    private:



    public:
        Sherlock(std::string name, int Id, HeroesTeam Team, int hp, AttackType attack, int maxhp, CardOwner owner): Hero(name, Id, Team, hp, attack, maxhp, owner)
        {}

        void SpecialAbility(Board&, Map&, Player*) override;
};

