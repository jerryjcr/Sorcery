#include "Ritual.h"

Ritual::Ritual(const std::string& name, int cost, int charges, int chargeCost,
         std::shared_ptr<const Ability> triggered); 
         Card{name, cost, nullptr, triggered}, charges{charges}, chargesCost{chargesCost} {}

