#include "Enchantment.h"
#include <iostream>

Enchantment::Enchantment(const std::string& name, int cost)
    : Minion{name, cost, 420, 420}, parent{nullptr} {}

Enchantment::Enchantment(const std::string& name, int cost,
                         std::unique_ptr<Minion> parent)
    : Minion{name, cost, 6969, 6969}, parent{std::move(parent)} {}

std::unique_ptr<Minion>& Enchantment::getParent() { return parent; }

void Enchantment::setParent(std::unique_ptr<Minion> newParent) {
  parent = std::move(newParent);
}

Enchantment::~Enchantment() {}

CardType Enchantment::getType() const { return CardType::Enchantment; }

bool Enchantment::useCardAbility(Player& activePlayer, Player& inactivePlayer,
                              TriggerType type) {
  if (parent.get()==nullptr){
    return false;
  }
  else {
    if (getActions() <= 0 && type == TriggerType::None){
      std::cout<<"Minion does not have enought actions."<<std::endl;
      return false;
    }
    if (parent->Card::useCardAbility(activePlayer, inactivePlayer, type)) {
      if (type == TriggerType::None) adjustActions(-1);
      return true;
    }
    return false;
  }
}

bool Enchantment::useCardAbility(Player& targetPlayer, Card& targetCard,
                              TriggerType type) {
  if (parent.get()==nullptr){
    return false;
  }
  else {
    if (getActions() <= 0 && type == TriggerType::None) {
      std::cout << "Minion does not have enough actions." << std::endl;
      return false;
    }
    if (parent->Card::useCardAbility(targetPlayer, targetCard, type)) {
      if (type == TriggerType::None) adjustActions(-1);
      return true;
    }
    return false;
  }
} 
\

bool Enchantment::requiresTarget() const {
  if (parent.get()==nullptr){
    return false;
  }
  else {
    return parent->requiresTarget();
  }
}

bool Enchantment::canTarget(CardType targetType) const {
  if (parent.get()==nullptr){
    return false;
  }
  else {
    return parent->canTarget(targetType);
  }
}

int Enchantment::getAttack() const {
  if (parent.get()==nullptr){
    return attack;
  }
  else {
    return parent->getAttack();
  }
}

int Enchantment::getDefence() const {
  if (parent.get()==nullptr){
    return defence;
  }
  else {
    return parent->getDefence();
  }
}

int Enchantment::getActions() const {
  if (parent.get()==nullptr){
    return actions;
  }
  else {
    return parent->getActions();
  }
}

int Enchantment::getAbilityCost() const {
  if (parent.get()==nullptr){
    return -100000;
  }
  else {
    return parent->getAbilityCost();
  }
}

void Enchantment::adjustActions(int amount) {
  if (parent.get()==nullptr){
    return;
  }
  else {
    parent->adjustActions(amount);
  }
}

void Enchantment::adjustAttack(int amount) {
  if (parent.get()==nullptr){
    return;
  }
  else {
    parent->adjustAttack(amount);
  }
}

void Enchantment::adjustDefence(int amount) {
  if (parent.get()==nullptr){
    return;
  }
  else {
    parent->adjustDefence(amount);
  }
}

void Enchantment::resetActions() {
  if (parent.get()==nullptr){
    return;
  }
  else {
    parent->resetActions();
  }
}

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
