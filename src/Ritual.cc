#include "Ritual.h"

#include <memory>
#include <string>

#include "Ability.h"
#include "Card.h"

Ritual::Ritual(const std::string& name, int cost, int charges, int chargeCost,
               std::shared_ptr<const Ability> triggered)
    : Card{name, cost, nullptr, triggered},
      charges{charges},
      chargeCost{chargeCost} {}

Ritual::~Ritual() {}
