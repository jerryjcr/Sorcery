#include "Ability.h"

#include <algorithm>
#include <string>
#include <vector>

Ability::Ability(const std::string& name, int cost,
                 std::vector<TargetType> validTargets)
    : name{name}, cost{cost}, validTargets{std::move(validTargets)} {}

bool Ability::requiresTarget() const { return !validTargets.empty(); }

bool Ability::canTarget(TargetType targetType) const {
  return std::find(validTargets.begin(), validTargets.end(), targetType) !=
         validTargets.end();
}
