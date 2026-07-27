#include "Deck.h"
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

Deck::Deck(){}

void Deck::AddCard(unique_ptr<Card> card, HeroesTeam heroteam)
{
    if(heroteam == HeroesTeam::SHERLOCK)
    {
        SherlockDeck.push_back(std::move(card));
    }
    else
    {
        DraculaDeck.push_back(std::move(card));
    }
}