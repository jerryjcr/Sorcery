#include "Enchantment.h"

Enchantment::Enchantment(const std::string& name, int cost,
                         std::unique_ptr<Minion> parent)
    : Minion{name, cost, 6969, 6969}, parent{std::move(parent)} {}

std::unique_ptr<Minion>& Enchantment::getParent() { return parent; }

void Enchantment::setParent(std::unique_ptr<Minion> parent) {
  parent = std::move(parent);
}

Enchantment::~Enchantment() {}

CardType Enchantment::getType() const { return CardType::Enchantment; }

int Enchantment::getCost() const {
  if (parent.get() == nullptr) {
    return cost;
  }
  return parent->getCost();
}

const std::string& Enchantment::getName() const {
  if (parent.get() == nullptr) {
    return name;
  }
  return parent->getName();
}
