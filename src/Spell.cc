#include "Spell.h"

#include <memory>
#include <string>

#include "Ability.h"
#include "Card.h"

Spell::Spell(const std::string& name, int cost,
             std::shared_ptr<const Ability> activated)
    : Card{name, cost, activated} {}

bool Spell::requiresTarget() const { return false; }
