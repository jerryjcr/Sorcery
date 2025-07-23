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

bool Ritual::useCardAbility(Player& activePlayer, Player& inactivePlayer,
                            TriggerType type = TriggerType::None) {
  if (charges < chargeCost) {
    // no message if you don't have enough charges, since it's triggered
    return false;
  }
  if (Card::useCardAbility(activePlayer, inactivePlayer, type)) {
    charges -= chargeCost;
    return true;
  }
}

int Ritual::getCharges() const { return charges; }
