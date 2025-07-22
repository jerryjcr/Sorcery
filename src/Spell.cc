#include "Spell.h"

#include <memory>
#include <string>
#include <vector>

#include "Ability.h"
#include "Card.h"

Spell::Spell(const std::string& name, int cost,
             std::shared_ptr<const Ability> activated,
             std::vector<TargetType> targets)
    : Card{name, cost, activated}, validTargets{std::move(targets)} {}

bool Spell::requiresTarget() const { return !validTargets.empty(); }
