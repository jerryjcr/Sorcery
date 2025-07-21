#include "ConcreteAbilities.h"

#include <memory>

#include "Ability.h"
#include "Card.h"
#include "Player.h"
#include "Minion.h"
#include "Ritual.h"
#include "Enchantment.h"

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
    //finish when player is done
  }
}

void RechargeAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
    targetPlayer.getRitual()->adjustCharges(3);
  }
}

void DisenchantAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
    if (targetPlayer.getBoard(boardIndex)->getIsEnchanted()){
      targetPlayer.getBoard(boardIndex); //not done
    }
  }
}

