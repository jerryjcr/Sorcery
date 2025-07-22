#include "DefaultMinion.h"

#include "Card.h"
#include "Minion.h"

DefaultMinion::DefaultMinion() : Minion{"Default", 1, 1, 1, nullptr} {}
const std::vector<const std::string>& DefaultMinion::getDescription() const {
    return std::vector<const std::string> {"this is the default minion", "I really hope this works",""};
}
