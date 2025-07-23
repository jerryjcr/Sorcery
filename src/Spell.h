#ifndef SPELL_H_
#define SPELL_H_

#include <memory>
#include <vector>

#include "Ability.h"
#include "Card.h"

class Player;

class Spell : public Card {
 public:
  Spell(const std::string& name, int cost, std::unique_ptr<Ability> ability);
  virtual ~Spell() = 0;
};

#endif
