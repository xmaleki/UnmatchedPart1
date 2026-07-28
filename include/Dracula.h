#include "Hero.h"
#include "GameManager.h"
#include <string>

class Dracula : public Hero
{
    private:



    public:
        Dracula(std::string name, int Id, HeroesTeam Team, int hp, AttackType attack, int maxhp, CardOwner owner):Hero(name, Id, Team, hp, attack, maxhp, owner)
        {}

    
    void SpecialAbility(Board&, Map&, Player*) override;
};