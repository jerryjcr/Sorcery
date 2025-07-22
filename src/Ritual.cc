#include "Ritual.h"

#include <memory>
#include <string>

#include "Ability.h"
#include "Card.h"

Ritual::Ritual(const std::string& name, int cost, int charges, int chargeCost,
               std::unique_ptr<const Ability> ability)
    : Card{name, cost, CardType::Ritual, std::move(ability)},
      charges{charges},
      chargeCost{chargeCost} {}

Ritual::~Ritual() {}

int Ritual::getCharges() {
  return charges;
}
