#ifndef DATABASE_H_
#define DATABASE_H_

#include "Card.h"

// assigns values to the given parameters based on the code given
// if the code is invalid will assign a default minion
void findMinion(const std::string& code, std::string& name, int& cost,
                std::shared_ptr<const Ability>& activated,
                std::shared_ptr<const Ability>& triggered, int& attack,
                int& defence);

void findSpell(const std::string& code, std::string& name, int& cost,
              std::shared_ptr<const Ability>& activated);

void findEnchantment(const std::string& code, std::string& name, int& cost,
              std::shared_ptr<const Ability>& activated,
              std::shared_ptr<const Ability>& triggered);

void findRitual(const std::string& code, std::string& name, int& cost,
              std::shared_ptr<const Ability>& activated,
              std::shared_ptr<const Ability>& triggered, int& charges,
              int& chargeCost);

#endif
