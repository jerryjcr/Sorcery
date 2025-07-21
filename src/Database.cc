#include "Database.h"

void findMinion(const std::string& code, std::string& name, int& cost,
                std::shared_ptr<const Ability>& activated,
                std::shared_ptr<const Ability>& triggered, int& attack,
                int& defence) {
  if (code == "Mplaceholder") {
  } else {  // default minion
    name = "Minion Default";
    cost = 1;
    activated = nullptr;
    triggered = nullptr;
    attack = 1;
    defence = 1;
  }
}

void findSpell(const std::string& code, std::string& name, int& cost,
               std::shared_ptr<const Ability>& activated) {
  if (code == "placeholder") {
  } else {  // default spell
    name = "Spell Default";
    cost = 1;
    activated = nullptr;
  }
}

void findEnchantment(const std::string& code, std::string& name, int& cost,
                     std::shared_ptr<const Ability>& activated,
                     std::shared_ptr<const Ability>& triggered) {
  if (code == "Mplaceholder") {
  } else {  // default enchantment
    // we didn't come up with a class definition yet however we will eventually
  }
}

void findRitual(const std::string& code, std::string& name, int& cost,
                std::shared_ptr<const Ability>& activated,
                std::shared_ptr<const Ability>& triggered, int& charges,
                int& chargeCost) {
  if (code == "Mplaceholder") {
  } else {  // default ritual
    // not sure what this would look right rn
  }
}
