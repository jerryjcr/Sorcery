#include "ConcreteMinion.h"

DefaultMinion::DefaultMinion() : Minion{"Default", 1, 1, 1, nullptr} {}

const std::vector<std::string>& DefaultMinion::getDescription() const {
  return std::vector<std::string>{"This is the default Minion.", "",
                                  "Hopefully this works"};
}

AirElemental::AirElemental() :Minion{"Air Elemental", 0, 1, 1, nullptr} {}

const std::vector<std::string>& AirElemental::getDescription() const {
  return std::vector<std::string>{"","",""};
}

EarthElemental::EarthElemental() :Minion{"Earth Elemental", 3, 4, 4, nullptr} {}

const std::vector<std::string>& EarthElemental::getDescription() const {
  return std::vector<std::string>{"","",""};
}
