#include "ConcreteAbilities.h"

#include <memory>
#include <iostream>

#include "Ability.h"
#include "Card.h"
#include "Player.h"
#include "Minion.h"
#include "Ritual.h"
#include "Enchantment.h"
#include "ConcreteMinions.h"

BanishAbility::BanishAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment,CardType::Ritual}}{}
bool BanishAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::None) {
    //move to graveyard
  }
  return true;
}

UnsummonAbility::UnsummonAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
bool UnsummonAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::None) {
    //move from board to hand
  }
  return true;
}

RechargeAbility::RechargeAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Ritual}}{}
bool RechargeAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::None) {
    if (activePlayer.getRitual().get()){
      activePlayer.getRitual()->adjustCharges(3);
      return true;
    }
    else {
      std::cerr<<"Error: cannot use Recharge with no active ritual"<<std::endl;
      return false;
    }
  }
}

DisenchantAbility::DisenchantAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Enchantment}}{}
bool DisenchantAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>> v=targetPlayer.getBoard();
    int index=0;
    for (;index<v.size();++index){
      if (v[index].get()==targetCard.get()) break;
    }
    Enchantment* tmp=(dynamic_cast<Enchantment*>(targetCard.get()));
    v[index]=std::move(tmp->getParent());
  }
  return true;
}

BlizzardAbility::BlizzardAbility(int cost):Ability{cost,std::vector<CardType>{}}{}
bool BlizzardAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
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
  return true;
}

RaiseDeadAbility::RaiseDeadAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment,CardType::Ritual}}{}
bool RaiseDeadAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::None) { 
    if (!activePlayer.isGraveyardEmpty()) {
      //graveyard to board
      return true;
    }
    else {
      std::cerr<<"Cannot use Raise Dead if the graveyard is empty"<<std::endl;
      return false;
    }
  }
}

BoneGolemAbility::BoneGolemAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
bool BoneGolemAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::MyMinionLeaves||type == TriggerType::OpponentMinionLeaves) {
    Minion* p=(dynamic_cast<Minion*>(targetCard.get()));
    p->adjustAttack(1);
    p->adjustDefence(1);
  }
  return true;
}

FireElementalAbility::FireElementalAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
bool FireElementalAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::OpponentMinionEnters) {
    Minion* p=(dynamic_cast<Minion*>(targetCard.get()));
    p->adjustDefence(-1);
  }
  return true;
}

PotionSellerAbility::PotionSellerAbility(int cost):Ability{cost,std::vector<CardType>{}}{}
bool PotionSellerAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::MyEndOfTurn) {
    std::vector<std::unique_ptr<Minion>> v=activePlayer.getBoard();
    for (int i=0;i<v.size();++i){
      v[i]->adjustDefence(1);
    }
  }
  return true;
}

NovicePyromancerAbility::NovicePyromancerAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
bool NovicePyromancerAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::None) {
    Minion* p=(dynamic_cast<Minion*>(targetCard.get()));
    p->adjustDefence(-1);
  }
  return true;
}

ApprenticeSummonerAbility::ApprenticeSummonerAbility(int cost):Ability{cost,std::vector<CardType>{}}{}
bool ApprenticeSummonerAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>> v=activePlayer.getBoard();
    if (v.size()<5){
      v.emplace_back(AirElemental{});
      return true;
    }
    else {
      std::cerr<<"Error: Cannot use summoner ability when board is empty"<<std::endl;
      return false;
    }
  }
}

MasterSummonerAbility::MasterSummonerAbility(int cost):Ability{cost,std::vector<CardType>{}}{}
bool MasterSummonerAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>> v=activePlayer.getBoard();
    if (v.size()<5){
      for (int i=0;i<3;++i){
        if (v.size()<5){
          v.emplace_back(AirElemental{});
        }
      }
      return true;
    }
    else {
      std::cerr<<"Error: Cannot use summoner ability when board is empty"<<std::endl;
      return false;
    }
  }
}

DarkRitualAbility::DarkRitualAbility(int cost):Ability{cost,std::vector<CardType>{}}{}
bool DarkRitualAbility::useAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::MyStartOfTurn) {
    activePlayer.adjustMagic(1);
  }
  return true;
}

AuraOfPowerAbility::AuraOfPowerAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
bool AuraOfPowerAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::MyMinionEnters) {
    Minion* p=(dynamic_cast<Minion*>(targetCard.get()));
    p->adjustAttack(1);
    p->adjustDefence(1);
  }
  return true;
}

StandstillAbility::StandstillAbility(int cost):Ability{cost,std::vector<CardType>{CardType::Minion,CardType::Enchantment}}{}
bool StandstillAbility::useAbility(Player& targetPlayer, std::unique_ptr<Card>& targetCard, TriggerType type) {
  if (type == TriggerType::MyMinionEnters||type == TriggerType::MyMinionLeaves) {
    //move to graveyard
  }
  return true;
}


