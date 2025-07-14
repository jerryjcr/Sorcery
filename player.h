#ifndef PLAYER_H_
#define PLAYER_H_

#include "minions.h"
#include "spells.h"
#include "enchantments.h"
#include "rituals.h"
#include <vector>

class Player {
    std::string playerName;
    int life,magic;
    std::vector<std::shared_ptr<Card>> decklist,deck,hand,graveyard;
    std::vector<std::shared_ptr<Minion>> board;
    std::shared_ptr<Card> ritual;
    public:
        void play(int deckIndex, int boardIndex, std::shared_ptr<Card> target);
};

#endif 