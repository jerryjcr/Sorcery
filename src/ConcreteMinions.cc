#include "ConcreteMinions.h"

#include <iostream>
#include <string>

#include "Card.h"
#include "ConcreteAbilities.h"
#include "Minion.h"
#include "Player.h"

std::string abilityCostBox(const Minion& m) {
  return std::string(" ") + std::to_string(m.getAbilityCost()) +
         std::string("   |");
}

DefaultMinion::DefaultMinion() : Minion{"Default", 1, 1, 1} {}

const std::vector<std::string> DefaultMinion::getDescription() const {
  return std::vector<std::string>{" This is the default minion", "", ""};
}

AirElemental::AirElemental() : Minion{"Air Elemental", 0, 1, 1} {}

const std::vector<std::string> AirElemental::getDescription() const {
  return std::vector<std::string>{"", "", ""};
}

EarthElemental::EarthElemental() : Minion{"Earth Elemental", 3, 4, 4} {}

const std::vector<std::string> EarthElemental::getDescription() const {
  return std::vector<std::string>{"", "", ""};
}

BoneGolem::BoneGolem()
    : Minion{"Bone Golem", 2, 1, 3, std::make_unique<BoneGolemAbility>(0)} {}

bool BoneGolem::useCardAbility(Player& targetPlayer, Card& targetCard,
                               TriggerType type) {
  std::cerr << "Error: Cannot target this card, or this ability may not "
               "target a card."
            << std::endl;
  return false;
}

bool BoneGolem::useCardAbility(Player& activePlayer, Player& inactivePlayer,
                               TriggerType type) {
  std::vector<std::unique_ptr<Minion>>& v = activePlayer.getBoard();
  int i = 0;
  for (; i < static_cast<int>(v.size()); ++i) {
    if (v[i].get() == this) break;
  }
  return ability->useAbility(activePlayer, *v[i], type);
}

const std::vector<std::string> BoneGolem::getDescription() const {
  return std::vector<std::string>{" Gain +1/+1 whenever a minion",
                                  " leaves play.", ""};
}

FireElemental::FireElemental()
    : Minion{"Fire Elemental", 2, 2, 2,
             std::make_unique<FireElementalAbility>(0)} {}

const std::vector<std::string> FireElemental::getDescription() const {
  return std::vector<std::string>{" Whenever an opponent's minion",
                                  " enters play, deal 1 damage to", "it."};
}

PotionSeller::PotionSeller()
    : Minion{"Potion Seller", 2, 1, 3,
             std::make_unique<PotionSellerAbility>(0)} {}

const std::vector<std::string> PotionSeller::getDescription() const {
  return std::vector<std::string>{" At the end of your turn, all",
                                  " your minions gain +0/+1.", ""};
}

NovicePyromancer::NovicePyromancer()
    : Minion{"Novice Pyromancer", 1, 0, 1,
             std::make_unique<NovicePyromancerAbility>(1)} {}

const std::vector<std::string> NovicePyromancer::getDescription() const {
  return std::vector<std::string>{
      abilityCostBox(*this) + std::string(" Deal 1 damage to target"),
      "------ minion.", ""};
}

ApprenticeSummoner::ApprenticeSummoner()
    : Minion{"Apprentice Summoner", 1, 1, 1,
             std::make_unique<ApprenticeSummonerAbility>(1)} {}

const std::vector<std::string> ApprenticeSummoner::getDescription() const {
  return std::vector<std::string>{
      abilityCostBox(*this) + std::string(" Summon a 1/1 air"),
      "------ elemental.", ""};
}

MasterSummoner::MasterSummoner()
    : Minion{"Master Summoner", 3, 2, 3,
             std::make_unique<MasterSummonerAbility>(2)} {}

const std::vector<std::string> MasterSummoner::getDescription() const {
  return std::vector<std::string>{
      abilityCostBox(*this) + std::string(" Summon up to three 1/1"),
      "------ air elementals.", ""};
}
