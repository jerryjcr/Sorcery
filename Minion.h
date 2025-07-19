#ifndef MINIONS_H_
#define MINIONS_H_

#include "abstractCard.h"

class Minion : public Card {
    int defense,attack, abilityCost, actionNumber;
    bool hasAbility;
    public:
        virtual int getDefense() const;
        virtual int getAttack() const;
        virtual int getAbilityCost() const;
        virtual int getActionNumber() const;
        virtual int getHasAbility() const;
        Minion(std::string name, int id, int playingCost, std::string description, int defense, int attack, int abilityCost, bool hasAbility);
        virtual ~Minion()=0;
};

class AirElemental : public Minion {
    public:
        AirElemental(std::string name, int id, int playingCost, std::string description, int defense, int attack, int abilityCost, bool hasAbility);
        virtual void play(std::shared_ptr<Card> target, Player &activePlayer, Player &inactivePlayer) override;
        virtual void activeAbility(std::shared_ptr<Card> target, Player &activePlayer, Player &inactivePlayer) override;
        virtual void describe() override;
        virtual void triggerAbility(triggerType trigger, std::shared_ptr<Card> target, Player &activePlayer, Player &inactivePlayer) override;
};



#endif