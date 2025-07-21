#include "ConcreteMinions.h"

#include "Card.h"
#include "ConcreteAbilities.h"
#include "Minion.h"

DefaultMinion::DefaultMinion() : Minion{"default", 1, 1, 1} {}
void DefaultMinion::describe() const {}
