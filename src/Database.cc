#include "Card.h"
#include "ConcreteMinion.h"
#include "Minion.h"
#include "Ritual.h"
#include "Spell.h"

std::unique_ptr<Card> findCard(const std::string& code) {
  if (code == "AirElemental") {
    return std::make_unique<AirElemental>();
  } else if (code == "EarthElemental") {
    return std::make_unique<EarthElemental>();
  } else {  // default card which is a basic minion
    return std::make_unique<DefaultMinion>();
  }
}
