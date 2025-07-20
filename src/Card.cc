#include Card.h

Card::Card( const std::string& name, int cost,
            std::shared_ptr<const Ability> activated = nullptr,
            std::shared_ptr<const Ability> triggered = nullptr):
            name{name}, cost{cost}, activatedAbility{activated},
            triggeredAbility{triggered} {}

int Card::getCost() {
    return cost;
}

void Card::activateAbility(Card* target, Player& activePlayer,
                               Player& inactivePlayer) {
    // figure this out later
}
