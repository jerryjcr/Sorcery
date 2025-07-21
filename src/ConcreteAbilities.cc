#include "ConcreteAbilities.h"

#include "Card.h"

void BanishAbility::useAbility(TriggerType type, Player& targetPlayer,
                               int boardIndex) {
  if (type == TriggerType::None) {
    std::unique_ptr<Card> p = nullptr;
    targetPlayer.setBoard(boardIndex, std::move(p));
  }
}

void UnsummonAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
  }
}
