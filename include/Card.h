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


// class MISTFORM
class MistForm : public Card
{
    private:

    public:
        MistForm();

        void ApplyScheme(SchemeContext&) override;


};

class Ambush : public Card
{
    private:

    public:
        Ambush();
        void ApplyDuringCombat(CombatContext&) override;


};


// class BAPTISM OF BOOLD
class BaptismOfBlood : public Card
{
    private:

    public:
        BaptismOfBlood();
    
        void ApplyScheme(SchemeContext&) override;

};


// class BEASTFORM

class Beastform : public Card
{

    public:
        Beastform();
        void ApplyDuringCombat(CombatContext&) override;
};

class Dash : public Card
{
    private:

    public:
        Dash();

        void ApplyAfterCombat(CombatContext&) override;
};


class Exploit : public Card
{
    private:

    public:
        Exploit();

        void ApplyAfterCombat(CombatContext&) override;

};


class LookIntoMyEyes : public Card
{
    private:


    public:
        LookIntoMyEyes();

        void ApplyDuringCombat(CombatContext&) override;


};

// class PreyUpon

class PreyUpon : public Card
{
    public:
        PreyUpon();

        void ApplyScheme(SchemeContext&) override;

};


// class Ravening Seduction

class RaveningSeduction : public Card
{

    public:
        RaveningSeduction();

        void ApplyScheme(SchemeContext&) override;



};




class ThirstForSustenance : public Card
{
    private:


    public:
        ThirstForSustenance();

        void ApplyAfterCombat(CombatContext&) override;



};


class Feint : public Card
{
    private:

    public:
        Feint();

        void ApplyImmediately(CombatContext&);


};



// =================================== Sherlock holmes ===================================


class AdministerAid : public Card
{

    public:
        AdministerAid();

        void ApplyScheme(SchemeContext&);

};

/*
class ConfirmSuspicion : public Card
{

    public:
        ConfirmSuspicion();

        void ApplyScheme(SchemeContext&) override;

};
*/



class Counterpunch: public Card
{

    public:
        Counterpunch();

        void ApplyAfterCombat(CombatContext&) override;

};


class DeduceStrategy : public Card
{

    public:
        DeduceStrategy();

        void ApplyDuringCombat(CombatContext&) override;

};


class EducationNeverEnds : public Card
{

    public:
        EducationNeverEnds();

        void ApplyAfterCombat(CombatContext&) override;

};


// class Elementary


class EliminateTheImpossible : public Card
{
    public:
        EliminateTheImpossible();

        void ApplyScheme(SchemeContext&) override;
};



class FixedPointInAChangingAge : public Card
{

    public:
        FixedPointInAChangingAge();

        void ApplyAfterCombat(CombatContext&) override;

};


class MasterOfDisguise : public Card
{

    public:
        MasterOfDisguise();

        void ApplyScheme(SchemeContext&) override;
};


class TheGameIsAfoot : public Card
{

    public:
        TheGameIsAfoot();

        void ApplyAfterCombat(CombatContext&) override;

};

class ServiceRevolver : public Card
{
    public:
        ServiceRevolver();
        
};


class StudyMethods : public Card
{
    public:
        StudyMethods();

        void ApplyAfterCombat(CombatContext&) override;
};
