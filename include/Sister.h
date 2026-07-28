#include "Hero.h"
#include "GameTypes.h"

class Sister : public Hero
{
    private:


    public:
        Sister(std::string name, int Id, HeroesTeam Team, int hp, AttackType attack, int maxhp, CardOwner owner): Hero(name, Id, Team, hp, attack, maxhp, owner)
        {}

        void SpecialAbility(Board&, Map&, Player*) override;
};
