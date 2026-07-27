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



unique_ptr<Card> Deck::DrawCard(HeroesTeam heroteam)
{
    if(DraculaDeck.empty() && heroteam == HeroesTeam::DRACULA)
    {
        cout<<"Dracula Deck is empty!\n";
        return nullptr;
    }
    
    if(SherlockDeck.empty() && heroteam == HeroesTeam::SHERLOCK)
    {
        cout<<"SherLock Deck is empty!\n";
        return nullptr;
    }
    
    if(heroteam == HeroesTeam::DRACULA)
    {
        unique_ptr<Card> drawn = move(DraculaDeck.back());
        DraculaDeck.pop_back();
        return drawn;
    }
    else
    {
        unique_ptr<Card> drawn = move(SherlockDeck.back());
        SherlockDeck.pop_back();
        return drawn;
    }
}


void Deck::Shuffle(HeroesTeam heroteam)
{
    auto rng = default_random_engine{};

    if(heroteam == HeroesTeam::DRACULA)
    {
        shuffle(DraculaDeck.begin(), DraculaDeck.end(), rng);
    }
    else
    {
        shuffle(SherlockDeck.begin(), SherlockDeck.end(), rng);
    }
}
