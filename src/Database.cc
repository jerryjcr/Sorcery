#include "Card.h"
#include "DefaultMinion.h"
#include "Minion.h"
#include "Ritual.h"
#include "Spell.h"

std::unique_ptr<Card> findCard(const std::string& code) {
  if (code == "Placeholder") {
    // for now this returns the default so that this always returns a value
    // in the future this will be a real card
    //return std::unique_ptr<Card>(new DefaultMinion);
    return nullptr;
  } else {  // default card which is a basic minion
    return std::make_unique<DefaultMinion>();
  }
}
