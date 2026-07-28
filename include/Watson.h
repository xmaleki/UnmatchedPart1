#include "Hero.h"
#include "GameTypes.h"

class Watson : public Hero
{
    private:


    public:
        Watson(std::string name, int Id, HeroesTeam Team, int hp, AttackType attack, int maxhp, CardOwner owner): Hero(name, Id, Team, hp, attack, maxhp, owner)
        {}

        void SpecialAbility(Board&, Map&, Player*) override;
};