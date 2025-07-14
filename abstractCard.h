#ifndef ABSTRACTCARD_H_
#define ABSTRACTCARD_H_

#include <string>
#include <memory>

enum triggerType {ON_TURN_START,ON_MINION_PLAYED,ON_MINION_LEAVE,ON_TURN_END};
enum cardType {MINION,SPELL,ENCHANTMENT,RITUAL};

class Player;

class Card {
    std::string name;
    int id;
    int playingCost;
    cardType type;
    public:
        Card(std::string name, int id, int playingCost, std::string description, cardType type);
        virtual void play(std::shared_ptr<Card> target, Player &activePlayer, Player &inactivePlayer)=0;
        virtual void activeAbility(std::shared_ptr<Card> target, Player &activePlayer, Player &inactivePlayer)=0;
        virtual void describe()=0;
        virtual void triggerAbility(triggerType trigger, std::shared_ptr<Card> target, Player &activePlayer, Player &inactivePlayer)=0;
};

#endif
