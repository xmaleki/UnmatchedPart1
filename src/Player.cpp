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
