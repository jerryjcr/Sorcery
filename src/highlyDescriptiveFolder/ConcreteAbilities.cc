#include "ConcreteAbilities.h"

#include <memory>

#include "Ability.h"
#include "Card.h"
#include "Player.h"
#include "Minion.h"
#include "Ritual.h"
#include "Enchantment.h"
#include "ConcreteMinions.h"

BanishAbility::BanishAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment,CardType::Ritual}}{}
void BanishAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::None) {
    //move to graveyard
  }
}

UnsummonAbility::UnsummonAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
void UnsummonAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::None) {
    //move from board to hand
  }
}

RechargeAbility::RechargeAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Ritual}}{}
void RechargeAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::None) {
    activePlayer.getRitual()->adjustCharges(3);
  }
}

DisenchantAbility::DisenchantAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Enchantment}}{}
void DisenchantAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>> v=targetPlayer.getBoard();
    int index=0;
    for (;index<v.size();++index){
      if (v[index].get()==targetCard.get()) break;
    }
    Enchantment* tmp=(dynamic_cast<Enchantment*>(targetCard.get()));
    v[index]=std::move(tmp->getParent());
  }
}

BlizzardAbility::BlizzardAbility(int cost):Ability{cost,std::vector<CardType>{}}{}
void BlizzardAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>> v=activePlayer.getBoard();
    for (int i=0;i<v.size();++i){
      v[i]->adjustDefence(-2);
    }
    std::vector<std::unique_ptr<Minion>> v=inactivePlayer.getBoard();
    for (int i=0;i<v.size();++i){
      v[i]->adjustDefence(-2);
    }
  }
}

RaiseDeadAbility::RaiseDeadAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment,CardType::Ritual}}{}
void RaiseDeadAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::None) {  
    //graveyard to board
  }
}

BoneGolemAbility::BoneGolemAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
void BoneGolemAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::MyMinionLeaves||type == TriggerType::OpponentMinionLeaves) {
    Minion* p=(dynamic_cast<Minion*>(targetCard.get()));
    p->adjustAttack(1);
    p->adjustDefence(1);
  }
}

FireElementalAbility::FireElementalAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
void FireElementalAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::OpponentMinionEnters) {
    Minion* p=(dynamic_cast<Minion*>(targetCard.get()));
    p->adjustDefence(-1);
  }
}

PotionSellerAbility::PotionSellerAbility(int cost):Ability{cost,std::vector<CardType>{}}{}
void PotionSellerAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::MyEndOfTurn) {
    std::vector<std::unique_ptr<Minion>> v=activePlayer.getBoard();
    for (int i=0;i<v.size();++i){
      v[i]->adjustDefence(1);
    }
  }
}

NovicePyromancerAbility::NovicePyromancerAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
void NovicePyromancerAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::None) {
    Minion* p=(dynamic_cast<Minion*>(targetCard.get()));
    p->adjustDefence(-1);
  }
}

ApprenticeSummonerAbility::ApprenticeSummonerAbility(int cost):Ability{cost,std::vector<CardType>{}}{}
void ApprenticeSummonerAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>> v=activePlayer.getBoard();
    if (v.size()<5){
      v.emplace_back(AirElemental{});
    }
  }
}

MasterSummonerAbility::MasterSummonerAbility(int cost):Ability{cost,std::vector<CardType>{}}{}
void MasterSummonerAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>> v=activePlayer.getBoard();
    for (int i=0;i<3;++i){
      if (v.size()<5){
        v.emplace_back(AirElemental{});
      }
    }
  }
}

DarkRitualAbility::DarkRitualAbility(int cost):Ability{cost,std::vector<CardType>{}}{}
void DarkRitualAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::MyStartOfTurn) {
    activePlayer.adjustMagic(1);
  }
}

AuraOfPowerAbility::AuraOfPowerAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
void AuraOfPowerAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::MyMinionEnters) {
    Minion* p=(dynamic_cast<Minion*>(targetCard.get()));
    p->adjustAttack(1);
    p->adjustDefence(1);
  }
}

StandstillAbility::StandstillAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
void StandstillAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::MyMinionEnters||type == TriggerType::MyMinionLeaves) {
    //move to graveyard
  }
}


