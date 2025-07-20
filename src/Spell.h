#ifndef SPELL_H_
#define SPELL_H_

#include "Card.h"

class Spell : public Card {
 public:
  Spell(const std::string& name, int cost,
        std::shared_ptr<const Ability> activated);
  virtual ~Spell() = 0;

  void useSpell(Card* target, Player& activePlayer, Player& inactivePlayer);
};

#endif
