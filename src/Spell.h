#ifndef SPELL_H_
#define SPELL_H_

#include <memory>
#include <vector>

#include "Ability.h"
#include "Card.h"

enum class TargetType { Minion, Ritual };

class Spell : public Card {
  std::vector<TargetType> validTargets;

 public:
  Spell(const std::string& name, int cost,
        std::shared_ptr<const Ability> activated,
        std::vector<TargetType> targets = {});
  virtual ~Spell() = 0;

  bool requiresTarget() const;

  void useSpell();
  void useSpell(Player& targetPlayer, int boardIndex);
};

#endif
