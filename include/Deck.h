#pragma once
#include "GameTypes.h"
#include "Card.h"
#include <vector>
#include <memory>

class Deck
{
    private:
        std::vector<std::unique_ptr<Card>> SherlockDeck;
        std::vector<std::unique_ptr<Card>> DraculaDeck;
    public:
        Deck();
        void AddCard(std::unique_ptr<Card>, HeroesTeam);
        std::unique_ptr<Card> DrawCard(HeroesTeam);
        void Shuffle(HeroesTeam);
        void CreateSherlockDeck();
        void CreateDraculaDeck();
        int GetSize(HeroesTeam) const;
        bool IsEmpty(HeroesTeam) const;
};