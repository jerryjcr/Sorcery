#include "ConcreteAbilities.h"

#include <iostream>
#include <memory>

#include "Ability.h"
#include "Card.h"
#include "ConcreteMinions.h"
#include "Enchantment.h"
#include "Minion.h"
#include "Player.h"
#include "Ritual.h"

BanishAbility::BanishAbility(int cost)
    : Ability{cost,
              std::vector<CardType>{CardType::Minion, CardType::Enchantment,
                                    CardType::Ritual}} {}
bool BanishAbility::useAbility(Player& targetPlayer, Card& targetCard,
                          Player& activePlayer, Player& otherPlayer,
                          TriggerType type) {
  if (!this->canTarget(targetCard.getType())) {
    std::cerr << "Error: Cannot target card of this type." << std::endl;
    return false;
  }
  if (type == TriggerType::None &&
      (targetCard.getType() == CardType::Minion ||
       targetCard.getType() == CardType::Enchantment)) {
    std::vector<std::unique_ptr<Minion>>& v = targetPlayer.getBoard();
    int i = 0;
    for (; i < static_cast<int>(v.size()); ++i) {
      if (v[i].get() == &targetCard) break;
    }
    if (&targetPlayer==&activePlayer){
      activePlayer.triggerBoard(otherPlayer,*v[i],TriggerType::MyMinionLeaves);
      otherPlayer.triggerBoard(activePlayer,*v[i],TriggerType::OpponentMinionLeaves);
    }
    else if (&targetPlayer==&otherPlayer) {
      activePlayer.triggerBoard(otherPlayer,*v[i],TriggerType::OpponentMinionLeaves);
      otherPlayer.triggerBoard(otherPlayer,*v[i],TriggerType::MyMinionLeaves);
    }
    targetPlayer.killMinion(i+1);
    return true;
  } else if (type == TriggerType::None) {
    targetPlayer.killRitual();
    return true;
  }
  return false;
}

UnsummonAbility::UnsummonAbility(int cost)
    : Ability{cost,
              std::vector<CardType>{CardType::Minion, CardType::Enchantment}} {}
bool UnsummonAbility::useAbility(Player& targetPlayer, Card& targetCard,
                          Player& activePlayer, Player& otherPlayer,
                          TriggerType type) {
  if (!this->canTarget(targetCard.getType())) {
    std::cerr << "Error: Cannot target card of this type." << std::endl;
    return false;
  }
  if (type == TriggerType::None) {
    if (targetPlayer.getHand().size() >= 5&& &targetPlayer==&otherPlayer) {
      std::cerr << "Error: Cannot play Unsummon if hand is full." << std::endl;
      return false;
    }
    std::vector<std::unique_ptr<Minion>>& v = targetPlayer.getBoard();
    int i = 0;
    for (; i < static_cast<int>(v.size()); ++i) {
      if (v[i].get() == &targetCard) break;
    }
    if (&targetPlayer==&activePlayer){
      activePlayer.triggerBoard(otherPlayer,*v[i],TriggerType::MyMinionLeaves);
      otherPlayer.triggerBoard(activePlayer,*v[i],TriggerType::OpponentMinionLeaves);
    }
    else if (&targetPlayer==&otherPlayer) {
      activePlayer.triggerBoard(otherPlayer,*v[i],TriggerType::OpponentMinionLeaves);
      otherPlayer.triggerBoard(otherPlayer,*v[i],TriggerType::MyMinionLeaves);
    }
    targetPlayer.returnMinionToHand(i+1);
    return true;
  }
  return false;
}

RechargeAbility::RechargeAbility(int cost)
    : Ability{cost, std::vector<CardType>{CardType::Ritual}} {}
bool RechargeAbility::useAbility(Player& activePlayer, Player& inactivePlayer,
                                 TriggerType type) {
  if (type == TriggerType::None) {
    if (activePlayer.getRitual().get()) {
      activePlayer.getRitual()->adjustCharges(3);
      return true;
    } else {
      std::cerr << "Error: Cannot use Recharge with no active ritual."
                << std::endl;
      return false;
    }
  }
  return false;
}

DisenchantAbility::DisenchantAbility(int cost)
    : Ability{cost, std::vector<CardType>{CardType::Enchantment}} {}
bool DisenchantAbility::useAbility(Player& targetPlayer, Card& targetCard,
                          Player& activePlayer, Player& otherPlayer,
                          TriggerType type) {
  if (!this->canTarget(targetCard.getType())) {
    std::cerr << "Error: Cannot target card of this type." << std::endl;
    return false;
  }
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>>& v = targetPlayer.getBoard();
    int index = 0;
    for (; index < static_cast<int>(v.size()); ++index) {
      if (v[index].get() == &targetCard) break;
    }
    Enchantment* tmp = (dynamic_cast<Enchantment*>(&targetCard));
    v[index] = std::move(tmp->getParent());
    return true;
  }
  return false;
}

BlizzardAbility::BlizzardAbility(int cost)
    : Ability{cost, std::vector<CardType>{}} {}
bool BlizzardAbility::useAbility(Player& activePlayer, Player& inactivePlayer,
                                 TriggerType type) {
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>>& v = activePlayer.getBoard();
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
      v[i]->adjustDefence(-2);
    }
    std::vector<std::unique_ptr<Minion>>& k = inactivePlayer.getBoard();
    for (int i = 0; i < static_cast<int>(k.size()); ++i) {
      k[i]->adjustDefence(-2);
    }
    return true;
  }
  return false;
}

RaiseDeadAbility::RaiseDeadAbility(int cost)
    : Ability{cost,
              std::vector<CardType>{CardType::Minion, CardType::Enchantment,
                                    CardType::Ritual}} {}
bool RaiseDeadAbility::useAbility(Player& activePlayer, Player& inactivePlayer,
                                  TriggerType type) {
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>>& v = activePlayer.getGraveyard();
    if (!v.empty()) {
      v.back()->adjustDefence(1 - (v.back()->getDefence()));
      activePlayer.reviveMinion();
      return true;
    } else {
      std::cerr << "Cannot use Raise Dead if the graveyard is empty."
                << std::endl;
      return false;
    }
  }
  return false;
}

BoneGolemAbility::BoneGolemAbility(int cost)
    : Ability{cost,
              std::vector<CardType>{CardType::Minion, CardType::Enchantment}} {}
bool BoneGolemAbility::useAbility(Player& targetPlayer, Card& targetCard,
                          Player& activePlayer, Player& otherPlayer,
                          TriggerType type) {
  if (!this->canTarget(targetCard.getType())) {
    std::cerr << "Error: Cannot target card of this type." << std::endl;
    return false;
  }
  if (type == TriggerType::MyMinionLeaves ||
      type == TriggerType::OpponentMinionLeaves) {
    Minion* p = (dynamic_cast<Minion*>(&targetCard));
    p->adjustAttack(1);
    p->adjustDefence(1);
    return true;
  }
  return false;
}

FireElementalAbility::FireElementalAbility(int cost)
    : Ability{cost,
              std::vector<CardType>{CardType::Minion, CardType::Enchantment}} {}
bool FireElementalAbility::useAbility(Player& targetPlayer, Card& targetCard,
                          Player& activePlayer, Player& otherPlayer,
                          TriggerType type) {
  if (!this->canTarget(targetCard.getType())) {
    std::cerr << "Error: Cannot target card of this type." << std::endl;
    return false;
  }
  if (type == TriggerType::OpponentMinionEnters) {
    Minion* p = (dynamic_cast<Minion*>(&targetCard));
    p->adjustDefence(-1);
    return true;
  }
  return false;
}

PotionSellerAbility::PotionSellerAbility(int cost)
    : Ability{cost, std::vector<CardType>{}} {}
bool PotionSellerAbility::useAbility(Player& activePlayer,
                                     Player& inactivePlayer, TriggerType type) {
  if (type == TriggerType::MyEndOfTurn) {
    std::vector<std::unique_ptr<Minion>>& v = activePlayer.getBoard();
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
      v[i]->adjustDefence(1);
    }
    return true;
  }
  return false;
}

NovicePyromancerAbility::NovicePyromancerAbility(int cost)
    : Ability{cost,
              std::vector<CardType>{CardType::Minion, CardType::Enchantment}} {}
bool NovicePyromancerAbility::useAbility(Player& targetPlayer, Card& targetCard,
                          Player& activePlayer, Player& otherPlayer,
                          TriggerType type) {
  if (!this->canTarget(targetCard.getType())) {
    std::cerr << "Error: Cannot target card of this type." << std::endl;
    return false;
  }
  if (type == TriggerType::None) {
    Minion* p = (dynamic_cast<Minion*>(&targetCard));
    p->adjustDefence(-1);
    return true;
  }
  return false;
}

ApprenticeSummonerAbility::ApprenticeSummonerAbility(int cost)
    : Ability{cost, std::vector<CardType>{}} {}
bool ApprenticeSummonerAbility::useAbility(Player& activePlayer,
                                           Player& inactivePlayer,
                                           TriggerType type) {
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>>& v = activePlayer.getBoard();
    if (static_cast<int>(v.size()) < 5) {
      std::unique_ptr<Minion> card = std::make_unique<AirElemental>();
      v.push_back(std::move(card));
      Minion& target=*v.back();
      activePlayer.triggerBoard(inactivePlayer,target,TriggerType::MyMinionEnters);
      inactivePlayer.triggerBoard(activePlayer,target,TriggerType::OpponentMinionEnters);
      return true;
    } else {
      std::cerr << "Error: Cannot use summoner ability when board is full."
                << std::endl;
      return false;
    }
  }
  return false;
}

MasterSummonerAbility::MasterSummonerAbility(int cost)
    : Ability{cost, std::vector<CardType>{}} {}
bool MasterSummonerAbility::useAbility(Player& activePlayer,
                                       Player& inactivePlayer,
                                       TriggerType type) {
  if (type == TriggerType::None) {
    std::vector<std::unique_ptr<Minion>>& v = activePlayer.getBoard();
    if (static_cast<int>(v.size()) < 5) {
      for (int i = 0; i < 3; ++i) {
        if (static_cast<int>(v.size()) < 5) {
          std::unique_ptr<Minion> card = std::make_unique<AirElemental>();
          v.push_back(std::move(card));
          Minion& target=*v.back();
        activePlayer.triggerBoard(inactivePlayer,target,TriggerType::MyMinionEnters);
        inactivePlayer.triggerBoard(activePlayer,target,TriggerType::OpponentMinionEnters);
        }
      }
      return true;
    } else {
      std::cerr << "Error: Cannot use summoner ability when board is full."
                << std::endl;
      return false;
    }
  }
  return false;
}

DarkRitualAbility::DarkRitualAbility(int cost)
    : Ability{cost, std::vector<CardType>{}} {}
bool DarkRitualAbility::useAbility(Player& activePlayer, Player& inactivePlayer,
                                   TriggerType type) {
  if (type == TriggerType::MyStartOfTurn) {
    activePlayer.adjustMagic(1);
    return true;
  }
  return false;
}

AuraOfPowerAbility::AuraOfPowerAbility(int cost)
    : Ability{cost,
              std::vector<CardType>{CardType::Minion, CardType::Enchantment}} {}
bool AuraOfPowerAbility::useAbility(Player& targetPlayer, Card& targetCard,
                          Player& activePlayer, Player& otherPlayer,
                          TriggerType type) {
  if (!this->canTarget(targetCard.getType())) {
    std::cerr << "Error: Cannot target card of this type." << std::endl;
    return false;
  }
  if (type == TriggerType::MyMinionEnters) {
    Minion* p = (dynamic_cast<Minion*>(&targetCard));
    p->adjustAttack(1);
    p->adjustDefence(1);
    return true;
  }
  return false;
}

StandstillAbility::StandstillAbility(int cost)
    : Ability{cost,
              std::vector<CardType>{CardType::Minion, CardType::Enchantment}} {}
bool StandstillAbility::useAbility(Player& targetPlayer, Card& targetCard,
                          Player& activePlayer, Player& otherPlayer,
                          TriggerType type) {
  if (!this->canTarget(targetCard.getType())) {
    std::cerr << "Error: Cannot target card of this type." << std::endl;
    return false;
  }
  if (type == TriggerType::MyMinionEnters ||
      type == TriggerType::OpponentMinionEnters) {
    std::vector<std::unique_ptr<Minion>>& v = targetPlayer.getBoard();
    int i = 0;
    bool found=false;
    for (; i < static_cast<int>(v.size()); ++i) {
      if (v[i].get() == &targetCard) {
        found=true;
        break;
      }
    }
    if (!found) return false;
    if (&targetPlayer==&activePlayer){
      activePlayer.triggerBoard(otherPlayer,*v[i],TriggerType::MyMinionLeaves);
      otherPlayer.triggerBoard(activePlayer,*v[i],TriggerType::OpponentMinionLeaves);
    }
    else if (&targetPlayer==&otherPlayer) {
      activePlayer.triggerBoard(otherPlayer,*v[i],TriggerType::OpponentMinionLeaves);
      otherPlayer.triggerBoard(otherPlayer,*v[i],TriggerType::MyMinionLeaves);
    }
    targetPlayer.killMinion(i+1);
    return true;
  }
  return false;
}
