#include "Card.h"
#include "ConcreteMinions.h"
#include "ConcreteRituals.h"
#include "ConcreteEnchantments.h"
#include "ConcreteSpells.h"
#include "Minion.h"
#include "Ritual.h"
#include "Spell.h"
#include "Enchantment.h"

std::unique_ptr<Card> findCard(const std::string& code) {
  if (code == std::string("AirElemental")) {
    return std::make_unique<AirElemental>();
  } else if (code == std::string("EarthElemental")) {
    return std::make_unique<EarthElemental>();
  } else if (code == std::string("BoneGolem")) {
    return std::make_unique<BoneGolem>();
  } else if (code == std::string("FireElemental")) {
    return std::make_unique<FireElemental>();
  } else if (code == std::string("PotionSeller")) {
    return std::make_unique<PotionSeller>();
  } else if (code == std::string("NovicePyromancer")) {
    return std::make_unique<NovicePyromancer>();
  } else if (code == std::string("ApprenticeSummoner")) {
    return std::make_unique<ApprenticeSummoner>();
  } else if (code == std::string("MasterSummoner")) {
    return std::make_unique<MasterSummoner>();
  } else if (code == std::string("DarkRitual")) {
    return std::make_unique<DarkRitual>();
  } else if (code == std::string("AuraOfPower")) {
    return std::make_unique<AuraOfPower>();
  } else if (code == std::string("Standstill")) {
    return std::make_unique<Standstill>();
  } else if (code == std::string("GiantStrength")) {
    return std::make_unique<GiantStrength>();
  } else if (code == std::string("Enrage")) {
    return std::make_unique<Enrage>();
  } else if (code == std::string("Haste")) {
    return std::make_unique<Haste>();
  } else if (code == std::string("MagicFatigue")) {
    return std::make_unique<MagicFatigue>();
  } else if (code == std::string("Silence")) {
    return std::make_unique<Silence>();
  } else if (code == std::string("Banish")) {
    return std::make_unique<Banish>();
  } else if (code == std::string("Unsummon")) {
    return std::make_unique<Unsummon>();
  } else if (code == std::string("Recharge")) {
    return std::make_unique<Recharge>();
  } else if (code == std::string("Disenchant")) {
    return std::make_unique<Disenchant>();
  } else if (code == std::string("RaiseDead")) {
    return std::make_unique<RaiseDead>();
  } else if (code == std::string("Blizzard")) {
    return std::make_unique<Blizzard>();
  } else {  // default card which is a basic minion
    return std::make_unique<DefaultMinion>();
  }
}
