#include "ConcreteMinions.h"

#include "Card.h"
#include "Minion.h"
#include "ConcreteAbilities.h"
#include "Player.h"
#include <iostream>

DefaultMinion::DefaultMinion() : Minion{"Default", 1, 1, 1} {}

AirElemental::AirElemental() : Minion{"Air Elemental", 0, 1, 1} {}

EarthElemental::EarthElemental() : Minion{"Earth Elemental", 3, 4, 4} {}

BoneGolem::BoneGolem() : Minion{"Bone Golem", 2, 1, 3, std::make_unique<BoneGolemAbility>()} {}

bool BoneGolem::useCardAbility(Player& targetPlayer, Card& targetCard, TriggerType type) {
  std::cerr<<"Error: cannot target this card(the card may not be targetable, or the target is of incorrect type)"<<std::endl;
  return false;
}

bool BoneGolem::useCardAbility(Player& activePlayer, Player& inactivePlayer, TriggerType type) {
  std::vector<std::unique_ptr<Minion>> v=activePlayer.getBoard();
  int i=0;
  for (;i<v.size();++i){
    if (v[i].get()==this)break;
  }
  return ability->useAbility(activePlayer,*v[i],type);
}

FireElemental::FireElemental() : Minion{"Fire Elemental", 2, 2, 2, std::make_unique<FireElementalAbility>()} {}

PotionSeller::PotionSeller() : Minion{"Potion Seller", 2, 1, 3, std::make_unique<PotionSellerAbility>()} {}

NovicePyromancer::NovicePyromancer() : Minion{"Novice Pyromancer", 1, 0, 1, std::make_unique<NovicePyromancerAbility>()} {}

ApprenticeSummoner::ApprenticeSummoner() : Minion{"Apprentice Summoner", 1, 1, 1, std::make_unique<ApprenticeSummonerAbility>()} {}

MasterSummoner::MasterSummoner() : Minion{"Master Summoner", 3, 2, 3, std::make_unique<MasterSummonerAbility>()} {}
