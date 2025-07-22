#ifndef SPELL_H_
#define SPELL_H_

#include <memory>
#include <vector>

#include "Ability.h"
#include "Card.h"

class Player;

class Spell : public Card {
 public:
  Spell(const std::string& name, int cost,
        std::shared_ptr<const Ability> activated);
  virtual ~Spell() = 0;

  void useSpell();
  void useSpell(Player& targetPlayer, int boardIndex);

  bool requiresTarget() const;
  bool canTarget(TargetType targetType) const;
};

#endif
