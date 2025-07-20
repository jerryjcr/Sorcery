#include "Spell.h"

Spell::Spell(const std::string& name, int cost,
        std::shared_ptr<const Ability> activated):
        Card{name, cost, activated} {}
