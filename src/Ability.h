#ifndef ABILITY_H
#define ABILITY_H

enum TriggerType {NONE,ON_MINION_ENTER,ON_MINION_EXIT,ON_TURN_START,ON_TURN_END};

class Player;
class Card;

class Ability {
    int abilityCost;
    public:
        virtual void useAbility(TriggerType type, Card* target,
                              Player& activePlayer, Player& inactivePlayer)=0;
};



#endif