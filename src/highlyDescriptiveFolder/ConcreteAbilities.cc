#include "ConcreteAbilities.h"

#include <memory>

#include "Ability.h"
#include "Card.h"
#include "Player.h"
#include "Minion.h"
#include "Ritual.h"
#include "Enchantment.h"
#include "ConcreteMinions.h"

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
      std::unique_ptr<Enchantment> tmp(static_cast<Enchantment*>(targetPlayer.getBoard(boardIndex).release()));
      targetPlayer.setBoard(boardIndex,std::move(tmp->getParent()));
    }
  }
}

void BlizzardAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
    for (int i=1;i<6;++i){
      targetPlayer.getBoard(i)->adjustDefence(-2);
    }
  }
}

void BoneGolemAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::MinionLeaves) {
    targetPlayer.getBoard(boardIndex)->adjustAttack(1);
    targetPlayer.getBoard(boardIndex)->adjustDefence(1);
  }
}

void RaiseDeadAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::MinionEnters) {
    targetPlayer.getBoard(boardIndex)->adjustDefence(-1);
  }
}

void PotionSellerAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::EndOfTurn) {
    for (int i=1;i<6;++i){
      targetPlayer.getBoard(i)->adjustDefence(1);
    }
  }
}

void NovicePyromancerAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
    targetPlayer.getBoard(boardIndex)->adjustDefence(-1);
  }
}

void ApprenticeSummonerAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
    int cardsToBePlayed=1;
    for (int i=1;i<6;++i){
      if (cardsToBePlayed==0){
        break;
      }
      if (targetPlayer.getBoard(i).get()==nullptr){
        std::unique_ptr<Minion> p{new AirElemental{}};//subjext to change based on ctor of concrete minion
        targetPlayer.setBoard(i,std::move(p));
        --cardsToBePlayed;
      }
    }
  }
}

void MasterSummonerAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
    int cardsToBePlayed=3;
    for (int i=1;i<6;++i){
      if (cardsToBePlayed==0){
        break;
      }
      if (targetPlayer.getBoard(i).get()==nullptr){
        std::unique_ptr<Minion> p{new AirElemental{}};//subjext to change based on ctor of concrete minion
        targetPlayer.setBoard(i,std::move(p));
        --cardsToBePlayed;
      }
    }
  }
}

void DarkRitualAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::StartOfTurn) {
    targetPlayer.adjustMagic(1);
  }
}

void AuraOfPowerAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::MinionEnters) {
    targetPlayer.getBoard(boardIndex)->adjustAttack(1);
    targetPlayer.getBoard(boardIndex)->adjustDefence(1);
  }
}

void StandstillAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::MinionEnters) {
    std::unique_ptr<Minion> p{nullptr};
    targetPlayer.setBoard(boardIndex,std::move(p));
  }
}


