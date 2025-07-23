#include "Spell.h"

#include <memory>
#include <string>
#include <vector>

#include "Ability.h"
#include "Card.h"

Spell::Spell(const std::string& name, int cost,
             std::unique_ptr<const Ability> ability)
    : Card{name, cost, CardType::Spell, std::move(ability)} {}

Spell::~Spell() {}
