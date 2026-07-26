#pragma once
#include "GameTypes.h"
#include <string>



class Card
{
    private:
        std::string Name;
        CardType Type;
        int Value;
        int Boost;
        Timing Time;
        std::string EffectDescription;
        CardOwner Owner;
    public:
        Card(const std::string& name, CardType type, int val, int bst, Timing time, const std::string& effect
        , CardOwner owner);
        std::string GetName() const;
        CardType GetType() const;
        std::string ToStringType(CardType ) const;
        int GetValue() const;
        int GetBoost() const;
        Timing GetTiming() const;
        std::string GetEffect() const;
        CardOwner GetOwner() const;
        std::string ToStringOwner(CardOwner) const;
        virtual void ApplyImmediately(CombatContext&) {};
        virtual void ApplyDuringCombat(CombatContext&) {};
        virtual void ApplyAfterCombat(CombatContext&) {};
        virtual void ApplyScheme(SchemeContext&) {};
};


class FeedingFrenzy : public Card
{
    private:


    public:
        FeedingFrenzy();

        void ApplyDuringCombat(CombatContext&) override;
};

