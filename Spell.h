#ifndef SPELLS_H_
#define SPELLS_H_

#include "abstractCard.h"

class Spell : public Card {};

class Banish : public Spell {
    public:
        Banish(std::string name, int id, int playingCost, std::string description);
        virtual void play(std::shared_ptr<Card> target, Player &activePlayer, Player &inactivePlayer) override;
        virtual void describe() override;
};


#endif