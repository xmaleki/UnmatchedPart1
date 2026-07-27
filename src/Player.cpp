#include "Player.h"
#include <vector>
#include <memory>

using namespace std;

Player::Player(std::string name,int year , int month, int day):Name(name), Day(day), Month(month), Year(year)
{}

void Player::SetHero(std::unique_ptr<Hero> hero, int heroid)
{
    HERO = std::move(hero);
    HeroId = heroid;
}

void Player::SetSideKicks(std::unique_ptr<Hero> sidekick, int sidekickid)
{
    SIDEKICKS.push_back(std::move(sidekick));
    SIDEKICKID.push_back(sidekickid);
}

Hero* Player::GetHero() const
{
    return HERO.get();
}

int Player::GetHeroId() const
{
    return HeroId;
}


std::string Player::GetAge() const
{
    std::string Age = std::to_string(Year) + "/" + std::to_string(Month) + "/" + std::to_string(Day);
    return Age;
}

std::string Player::GetName() const
{
    return Name;
}
