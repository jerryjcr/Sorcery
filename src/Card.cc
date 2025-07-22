#include "Card.h"

#include <memory>
#include <string>

#include "Ability.h"
#include "Player.h"

Card::Card(const std::string& name, int cost, CardType type,
           std::unique_ptr<const Ability> ability)
    : name{name}, cost{cost}, type{type}, ability{std::move(ability)} {}

Card::~Card() {}

bool useCardAbility(Player& activePlayer, Player& inactivePlayer,
                    TriggerType type = TriggerType::None);

bool useCardAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard,
                    TriggerType type = TriggerType::None);

const std::string& Card::getName() const { return name; }

int Card::getCost() const { return cost; }

CardType Card::getType() const { return type; }
