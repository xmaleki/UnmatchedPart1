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

void Deck::CreateSherlockDeck()
{
    // Emdad resani
    AddCard(make_unique<AdministerAid>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<AdministerAid>(), HeroesTeam::SHERLOCK);

    // zed hamle
    AddCard(make_unique<Counterpunch>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<Counterpunch>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<Counterpunch>(), HeroesTeam::SHERLOCK);

    // estentaj esteratejic
    AddCard(make_unique<DeduceStrategy>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<DeduceStrategy>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<DeduceStrategy>(), HeroesTeam::SHERLOCK);

    // Amozesh hargez payan nadarad
    AddCard(make_unique<EducationNeverEnds>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<EducationNeverEnds>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<EducationNeverEnds>(), HeroesTeam::SHERLOCK);

    // hazf na momken ha
    AddCard(make_unique<EliminateTheImpossible>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<EliminateTheImpossible>(), HeroesTeam::SHERLOCK);

    // farib
    AddCard(make_unique<Feint>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<Feint>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<Feint>(), HeroesTeam::SHERLOCK);

    // noghte ei sabet dar zamane ei motoghayer
    AddCard(make_unique<FixedPointInAChangingAge>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<FixedPointInAChangingAge>(), HeroesTeam::SHERLOCK);

    // ostad taghir chehre
    AddCard(make_unique<MasterOfDisguise>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<MasterOfDisguise>(), HeroesTeam::SHERLOCK);

    // bazi shoro shode ast
    AddCard(make_unique<TheGameIsAfoot>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<TheGameIsAfoot>(), HeroesTeam::SHERLOCK);

    // selah kamari
    AddCard(make_unique<ServiceRevolver>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<ServiceRevolver>(), HeroesTeam::SHERLOCK);

    // ravesh haye motalee
    AddCard(make_unique<StudyMethods>(), HeroesTeam::SHERLOCK);
    AddCard(make_unique<StudyMethods>(), HeroesTeam::SHERLOCK);

}


void Deck::CreateDraculaDeck()
{
    // atash khon
    AddCard(make_unique<FeedingFrenzy>(), HeroesTeam::DRACULA);
    AddCard(make_unique<FeedingFrenzy>(), HeroesTeam::DRACULA);

    // form meh
    AddCard(make_unique<MistForm>(), HeroesTeam::DRACULA);
    AddCard(make_unique<MistForm>(), HeroesTeam::DRACULA);

    // kamin
    AddCard(make_unique<Ambush>(), HeroesTeam::DRACULA);
    AddCard(make_unique<Ambush>(), HeroesTeam::DRACULA);

    // ghosle khon
    AddCard(make_unique<BaptismOfBlood>(), HeroesTeam::DRACULA);
    AddCard(make_unique<BaptismOfBlood>(), HeroesTeam::DRACULA);

    // form hayola
    AddCard(make_unique<Beastform>(), HeroesTeam::DRACULA);
    AddCard(make_unique<Beastform>(), HeroesTeam::DRACULA);

    // yoresh
    AddCard(make_unique<Dash>(), HeroesTeam::DRACULA);
    AddCard(make_unique<Dash>(), HeroesTeam::DRACULA);
    AddCard(make_unique<Dash>(), HeroesTeam::DRACULA);

    // bahre bardari
    AddCard(make_unique<Exploit>(), HeroesTeam::DRACULA);
    AddCard(make_unique<Exploit>(), HeroesTeam::DRACULA);
    AddCard(make_unique<Exploit>(), HeroesTeam::DRACULA);

    // be cheshmanam negah kon
    AddCard(make_unique<LookIntoMyEyes>(), HeroesTeam::DRACULA);
    AddCard(make_unique<LookIntoMyEyes>(), HeroesTeam::DRACULA);
    AddCard(make_unique<LookIntoMyEyes>(), HeroesTeam::DRACULA);

    // shekar kon
    AddCard(make_unique<PreyUpon>(), HeroesTeam::DRACULA);
    AddCard(make_unique<PreyUpon>(), HeroesTeam::DRACULA);

    // eghvaye siri napazir
    AddCard(make_unique<RaveningSeduction>(), HeroesTeam::DRACULA);
    AddCard(make_unique<RaveningSeduction>(), HeroesTeam::DRACULA);
    AddCard(make_unique<RaveningSeduction>(), HeroesTeam::DRACULA);

    // teshnegi baraye bagha
    AddCard(make_unique<ThirstForSustenance>(), HeroesTeam::DRACULA);
    AddCard(make_unique<ThirstForSustenance>(), HeroesTeam::DRACULA);
    AddCard(make_unique<ThirstForSustenance>(), HeroesTeam::DRACULA);

    // farib
    AddCard(make_unique<Feint>(), HeroesTeam::DRACULA);
    AddCard(make_unique<Feint>(), HeroesTeam::DRACULA);
    AddCard(make_unique<Feint>(), HeroesTeam::DRACULA);

}
