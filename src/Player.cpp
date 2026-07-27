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

void Player::InitializeDeck(HeroesTeam team)
{
    deck = std::make_unique<Deck>();
    if(team == HeroesTeam::DRACULA)
    {
        deck->CreateDraculaDeck();
    }
    else
    {
        deck->CreateSherlockDeck();
    }
}

Deck* Player::GetDeck() const
{
    return deck.get(); 
}

void Player::InitialHand()
{
    for(int i = 0; i < 5; ++i)
    {
        auto card = deck->DrawCard(HERO->GetTeam());
        if(card)
        {
            HandCards.push_back(move(card));
        }
    }
}

vector<unique_ptr<Card>>& Player::GetHand()
{
    return HandCards;
}

vector<unique_ptr<Hero>>& Player::GetSideKicks()
{
    return SIDEKICKS;
}

void Player::AddCardToHand(unique_ptr<Card> card)
{
    HandCards.push_back(move(card));
}

vector<Hero *> Player::GetAliveHeroes()
{
    vector<Hero *> Heroes;
    
    if(!HERO->IsDead())
    {
        Heroes.push_back(HERO.get());
    }

    for(auto & sidekick: SIDEKICKS)
    {
        if(!sidekick->IsDead())
        {
            Heroes.push_back(sidekick.get());
        }
    }

    return Heroes;
}

