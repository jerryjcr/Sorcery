#include "ConcreteAbilities.h"

#include <memory>

#include "Ability.h"
#include "Card.h"
#include "Player.h"
#include "Minion.h"
#include "Ritual.h"
#include "Enchantment.h"
#include "ConcreteMinions.h"

BanishAbility::BanishAbility(int cost):Ability{cost,std::vector<TargetType>{TargetType::Minion,TargetType::Ritual}}{}
void BanishAbility::useAbility(TriggerType type, Player& targetPlayer,
                          Player& nontargetPlayer, std::unique_ptr<Card> target) {
  if (type == TriggerType::None) {
    std::unique_ptr<Card> p = nullptr;
    targetPlayer.setBoard(boardIndex, std::move(p));
  }
}

UnsummonAbility::UnsummonAbility(int cost):Ability{cost,std::vector<TargetType>{TargetType::Minion}}{}
void UnsummonAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
    //finish when player is done
  }
}

RechargeAbility::RechargeAbility(int cost):Ability{cost,std::vector<TargetType>{TargetType::Ritual}}{}
void RechargeAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
    targetPlayer.getRitual()->adjustCharges(3);
  }
}

DisenchantAbility::DisenchantAbility(int cost):Ability{cost,std::vector<TargetType>{TargetType::Minion}}{}
void DisenchantAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
    if (targetPlayer.getBoard(boardIndex)->getIsEnchanted()){
      std::unique_ptr<Enchantment> tmp(static_cast<Enchantment*>(targetPlayer.getBoard(boardIndex).release()));
      targetPlayer.setBoard(boardIndex,std::move(tmp->getParent()));
    }
  }
}

BlizzardAbility::BlizzardAbility(int cost):Ability{cost,std::vector<TargetType>{}}{}
void BlizzardAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
    for (int i=1;i<6;++i){
      targetPlayer.getBoard(i)->adjustDefence(-2);
    }
  }
}

RaiseDeadAbility::RaiseDeadAbility(int cost):Ability{cost,std::vector<TargetType>{TargetType::Minion,TargetType::Ritual}}{}
void RaiseDeadAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::MinionEnters) {
    targetPlayer.getBoard(boardIndex)->adjustDefence(-1);
  }
}

BoneGolemAbility::BoneGolemAbility(int cost):Ability{cost,std::vector<TargetType>{TargetType::Minion}}{}
void BoneGolemAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::MinionLeaves) {
    targetPlayer.getBoard(boardIndex)->adjustAttack(1);
    targetPlayer.getBoard(boardIndex)->adjustDefence(1);
  }
}

PotionSellerAbility::PotionSellerAbility(int cost):Ability{cost,std::vector<TargetType>{}}{}
void PotionSellerAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::EndOfTurn) {
    for (int i=1;i<6;++i){
      targetPlayer.getBoard(i)->adjustDefence(1);
    }
  }
}

NovicePyromancerAbility::NovicePyromancerAbility(int cost):Ability{cost,std::vector<TargetType>{TargetType::Minion}}{}
void NovicePyromancerAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::None) {
    targetPlayer.getBoard(boardIndex)->adjustDefence(-1);
  }
}

ApprenticeSummonerAbility::ApprenticeSummonerAbility(int cost):Ability{cost,std::vector<TargetType>{}}{}
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

MasterSummonerAbility::MasterSummonerAbility(int cost):Ability{cost,std::vector<TargetType>{}}{}
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

DarkRitualAbility::DarkRitualAbility(int cost):Ability{cost,std::vector<TargetType>{}}{}
void DarkRitualAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::StartOfTurn) {
    targetPlayer.adjustMagic(1);
  }
}

AuraOfPowerAbility::AuraOfPowerAbility(int cost):Ability{cost,std::vector<TargetType>{TargetType::Minion}}{}
void AuraOfPowerAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::MinionEnters) {
    targetPlayer.getBoard(boardIndex)->adjustAttack(1);
    targetPlayer.getBoard(boardIndex)->adjustDefence(1);
  }
}

StandstillAbility::StandstillAbility(int cost):Ability{cost,std::vector<TargetType>{TargetType::Minion}}{}
void StandstillAbility::useAbility(TriggerType type, Player& targetPlayer,
                                 int boardIndex) {
  if (type == TriggerType::MinionEnters) {
    std::unique_ptr<Minion> p{nullptr};
    targetPlayer.setBoard(boardIndex,std::move(p));
  }
}


