#ifndef RITUALS_H_
#define RITUALS_H_

#include "abstractCard.h"

class Ritual : public Card {
    int charges, chargeCost;
    public:
        Ritual(std::string name, int id, int playingCost, std::string description, int charges, int chargeCost);
};

class DarkRitual : public Ritual {
    public:
        DarkRitual(std::string name, int id, int playingCost, std::string description, int charges, int chargeCost);
        virtual void activeAbility(std::shared_ptr<Card> target, Player &activePlayer, Player &inactivePlayer) override;
};



#endif