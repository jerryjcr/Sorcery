#ifndef SPELL_H
#define SPELL_H

#include "Card.h"

class Spell : public Card {
 public:
  Spell(const std::string& name, int cost,
        std::shared_ptr<const Ability> activated);
  void useSpell(Card* target, Player& activePlayer, Player& inactivePlayer);
  void describe() const override;
};

#endif
