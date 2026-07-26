#include "Card.h"
#include "GameTypes.h"
#include <iostream>
#include <random>
#include <memory>
#include <Deck.h>
#include "Hero.h"
#include <algorithm>
#include "Board.h"
#include "Map.h"
#include "Player.h"
#include "Movement.h"
#include "TerminalView.h"

using namespace std;

Card::Card(const std::string&name, CardType type, int value, int boost,
Timing timing, const std::string& effect, CardOwner owner):Name(name), Type(type), Value(value),
Boost(boost), Time(timing), EffectDescription(effect), Owner(owner)
{}

std::string Card::GetName() const
{
    return Name;
}

CardType Card::GetType() const
{
    return Type;
}

string Card::ToStringType(CardType type) const
{
    switch (type)
    {
    case CardType::Attack:
        return "Attack";
        break;
    case CardType::Defence:
        return "Defence";
        break;
    case CardType::Versatile:
        return "Versatile";
        break;
    case CardType::Scheme:
        return "Scheme";
        break;

    default:
        return "";
        break;
    }
}

int Card::GetValue() const
{
    return Value;
}

int Card::GetBoost() const
{
    return Boost;
}

Timing Card::GetTiming() const
{
    return Time;
}

std::string Card::GetEffect() const
{
    return EffectDescription;
}

CardOwner Card::GetOwner() const
{
    return Owner;
}

string Card::ToStringOwner(CardOwner owner) const
{
    switch (owner)
    {
    case CardOwner::Dracula:
        return "Dracula";
        break;
    
    case CardOwner::DrWatson:
        return "Dr Watson";
        break;

    case CardOwner::SherlockHolmes:
        return "Sherlock Holmes";
        break;
    
    case CardOwner::Sisters:
        return "Sister";
        break;

    case CardOwner::Any:
        return "Any";
        break;

    default:
        return "";
        break;
    }

}
