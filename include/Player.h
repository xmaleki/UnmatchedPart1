#pragma once
#include "GameTypes.h"
#include "Hero.h"
#include "Deck.h"
#include <vector>
#include <string>
#include <memory>

class Player
{
    private:
        int Year;
        int Month;
        int Day;
        std::string Name;
        std::unique_ptr<Hero> HERO;
        std::vector<std::unique_ptr<Hero>> SIDEKICKS;
        std::vector<int> SIDEKICKID;
        std::unique_ptr<Deck> deck;
        std::vector<std::unique_ptr<Card>> HandCards;
        std::vector<std::unique_ptr<Card>> DiscardCards;
        int HeroId;

    public:
        Player(std::string ,int, int, int);
        void SetHero(std::unique_ptr<Hero>, int);
        void SetSideKicks(std::unique_ptr<Hero> ,int);
        Hero* GetHero() const;
        int GetHeroId() const;
        std::string GetName() const;
        std::string GetAge() const;
        void InitializeDeck(HeroesTeam);
        Deck* GetDeck() const;
        void InitialHand();
        std::vector<std::unique_ptr<Card>>& GetHand();
        std::vector<std::unique_ptr<Hero>>& GetSideKicks();
        void AddCardToHand(std::unique_ptr<Card>);
        std::vector<Hero *> GetAliveHeroes();
        void DiscardCardFromHand(Card* );
        int GetHandSize() const;  
        Card* GetCardFromHand(int) const;
        void SetSideKickLocation(int);
};
