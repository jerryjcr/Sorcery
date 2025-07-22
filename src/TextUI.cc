#include "TextUI.h"

const int kWidth = 33;

const std::string kHorizontalBar = "|-------------------------------|";
const std::string kEmpty = "|                               |";
const std::string kBlank = "                                 ";

const std::vector<std::string> kEmptyBlock{
    kHorizontalBar, kEmpty, kEmpty, kEmpty, kEmpty,        kEmpty,
    kEmpty,         kEmpty, kEmpty, kEmpty, kHorizontalBar};

const std::vector<std::string> kBlankBlock{
    kBlank, kBlank, kBlank, kBlank, kBlank, kBlank,
    kBlank, kBlank, kBlank, kBlank, kBlank,
};

std::vector<std::string> visualizeActivePlayer(Player& p) {
  std::vector<std::string> block;
  // line 0
  block.emplace_back(kHorizontalBar);
  // line 1
  block.emplace_back("| ");
  block[1] += std::to_string(p.getLife());
  block[1].resize(std::string("|   ").length(), ' ');
  block[1] += "|";
  block[1].resize(kWidth - std::string("| 26 |").length(), ' ');
  block[1] += "| " + std::to_string(p.getMagic());
  block[1].resize(kWidth - 1, ' ');
  block[1] += "|";
  // line 2
  block.emplace_back("|------                   ------|");
  // line 3
  block.emplace_back(kEmpty);
  // line 4
  block.emplace_back(kEmpty);
  // line 5
  block.emplace_back(kEmpty);
  // line 6
  block.emplace_back(kEmpty);
  // line 7
  block.emplace_back("| ");
  block[7].resize(
      (kWidth - p.getName().length() - std::string("| ").length() * 2) / 2,
      ' ');
  block[7] += p.getName();
  block[7].resize(kWidth - 1, ' ');
  block[7] += "|";
  // line 8
  block.emplace_back(kEmpty);
  // line 9
  block.emplace_back(kEmpty);
  // line 10
  block.emplace_back(kHorizontalBar);

  return block;
}

std::vector<std::string> visualizeOpponentPlayer(Player& p) {
  std::vector<std::string> block;
  // line 0
  block.emplace_back(kHorizontalBar);
  // line 1
  block.emplace_back(kEmpty);
  // line 2
  block.emplace_back(kEmpty);
  // line 3
  block.emplace_back("| ");
  block[7].resize(
      (kWidth - p.getName().length() - std::string("| ").length() * 2) / 2,
      ' ');
  block[7] += p.getName();
  block[7].resize(kWidth - 1, ' ');
  block[7] += "|";
  // line 4
  block.emplace_back(kEmpty);
  // line 5
  block.emplace_back(kEmpty);
  // line 6
  block.emplace_back(kEmpty);
  // line 7
  block.emplace_back(kEmpty);
  // line 8
  block.emplace_back("|------                   ------|");
  // line 9
  block.emplace_back("| ");
  block[9] += std::to_string(p.getLife());
  block[9].resize(std::string("|   ").length(), ' ');
  block[9] += "|";
  block[9].resize(kWidth - std::string("| 26 |").length(), ' ');
  block[9] += "| " + std::to_string(p.getMagic());
  block[9].resize(kWidth - 1, ' ');
  block[9] += "|";
  // line 10
  block.emplace_back(kHorizontalBar);

  return block;
}

std::vector<std::string> visualizeMinion(Minion& m) {
  std::vector<std::string> block;
  // line 0
  block.emplace_back(kHorizontalBar);
  // line 1
  block.emplace_back("| ");
  block[1] += m.getName();
  block[1].resize(kWidth - std::string("| 26 |").length(), ' ');
  block[1] += "| " + std::to_string(m.getCost());
  block[1].resize(kWidth - 1, ' ');
  block[1] += "|";
  // line 2
  block.emplace_back("kHorizontalBar");
  // line 3
  block.emplace_back("|");
  block[3].resize(kWidth - std::string("Minion |").length(), ' ');
  block[3] += "Minion |";
  // line 4
  block.emplace_back(kHorizontalBar);
  // line 5
  block.emplace_back("| ");
  block[5] += m.getDescription()[0];
  block[5].resize(kWidth - 1, ' ');
  block[5] += "|";
  // line 6
  block.emplace_back("| ");
  block[6] += m.getDescription()[1];
  block[6].resize(kWidth - 1, ' ');
  block[6] += "|";
  // line 7
  block.emplace_back("| ");
  block[7] += m.getDescription()[2];
  block[7].resize(kWidth - 1, ' ');
  block[7] += "|";
  // line 8
  block.emplace_back("|------                   ------|");
  // line 9
  block.emplace_back("| ");
  block[9] += std::to_string(m.getAttack());
  block[9].resize(std::string("|   ").length(), ' ');
  block[9] += "|";
  block[9].resize(kWidth - std::string("| 26 |").length(), ' ');
  block[9] += "| " + std::to_string(m.getDefence());
  block[9].resize(kWidth - 1, ' ');
  block[9] += "|";
  // line 10
  block.emplace_back(kHorizontalBar);

  return block;
}

std::vector<std::string> visualizeSpell(Spell& s) {
  std::vector<std::string> block;
  // line 0
  block.emplace_back(kHorizontalBar);
  // line 1
  block.emplace_back("| ");
  block[1] += s.getName();
  block[1].resize(kWidth - std::string("| 26 |").length(), ' ');
  block[1] += "| " + std::to_string(s.getCost());
  block[1].resize(kWidth - 1, ' ');
  block[1] += "|";
  // line 2
  block.emplace_back(kHorizontalBar);
  // line 3
  block.emplace_back("|");
  block[3].resize(kWidth - std::string("Spell |").length(), ' ');
  block[3] += "Spell |";
  // line 4
  block.emplace_back(kHorizontalBar);
  // line 5
  block.emplace_back("| ");
  block[5] += s.getDescription()[0];
  block[5].resize(kWidth - 1, ' ');
  block[5] += "|";
  // line 6
  block.emplace_back("| ");
  block[6] += s.getDescription()[1];
  block[6].resize(kWidth - 1, ' ');
  block[6] += "|";
  // line 7
  block.emplace_back("| ");
  block[7] += s.getDescription()[2];
  block[7].resize(kWidth - 1, ' ');
  block[7] += "|";
  // line 8
  block.emplace_back(kEmpty);
  // line 9
  block.emplace_back(kEmpty);
  // line 10
  block.emplace_back(kHorizontalBar);

  return block;
}

std::vector<std::string> visualizeRitual(Ritual& r) {
  std::vector<std::string> block;
  // line 0
  block.emplace_back(kHorizontalBar);
  // line 1
  block.emplace_back("| ");
  block[1] += r.getName();
  block[1].resize(kWidth - std::string("|   |").length(), ' ');
  block[1] += "| " + std::to_string(r.getCost());
  block[1].resize(kWidth - 1, ' ');
  block[1] += "|";
  // line 2
  block.emplace_back(kHorizontalBar);
  // line 3
  block.emplace_back("|");
  block[3].resize(kWidth - std::string("Ritual |").length(), ' ');
  block[3] += "Ritual |";
  // line 4
  block.emplace_back(kHorizontalBar);
  // line 5
  block.emplace_back("| ");
  block[5] += r.getDescription()[0];
  block[5].resize(kWidth - 1, ' ');
  block[5] += "|";
  // line 6
  block.emplace_back("| ");
  block[6] += r.getDescription()[1];
  block[6].resize(kWidth - 1, ' ');
  block[6] += "|";
  // line 7
  block.emplace_back("| ");
  block[7] += r.getDescription()[2];
  block[7].resize(kWidth - 1, ' ');
  block[7] += "|";
  // line 8
  block.emplace_back("|                         ------|");
  // line 9
  block.emplace_back("| ");
  block[9].resize(kWidth - std::string("| 26 |").length(), ' ');
  block[9] += "| " + std::to_string(r.getCharges());
  block[9].resize(kWidth - 1, ' ');
  block[9] += "|";
  // line 10
  block.emplace_back(kHorizontalBar);

  return block;
}

// IMPORTANT NOTE: ENCHANTMENT DESCRIPTION HAS 5 LINES instead of 5

std::vector<std::string> visualizeEnchantment(Enchantment& e) {
  std::vector<std::string> block;
  // line 0
  block.emplace_back(kHorizontalBar);
  // line 1
  block.emplace_back("| ");
  block[1] += e.getName();
  block[1].resize(kWidth - std::string("| 26 |").length(), ' ');
  block[1] += "| " + std::to_string(e.getCost());
  block[1].resize(kWidth - 1, ' ');
  block[1] += "|";
  // line 2
  block.emplace_back(kHorizontalBar);
  // line 3
  block.emplace_back("|");
  block[3].resize(kWidth - std::string("Spell |").length(), ' ');
  block[3] += "Spell |";
  // line 4
  block.emplace_back(kHorizontalBar);
  // line 5
  block.emplace_back("| ");
  block[5] += e.getDescription()[0];
  block[5].resize(kWidth - 1, ' ');
  block[5] += "|";
  // line 6
  block.emplace_back("| ");
  block[6] += e.getDescription()[1];
  block[6].resize(kWidth - 1, ' ');
  block[6] += "|";
  // line 7
  block.emplace_back("| ");
  block[7] += e.getDescription()[2];
  block[7].resize(kWidth - 1, ' ');
  block[7] += "|";
  // line 8
  block.emplace_back("| ");
  block[8] += e.getDescription()[3];
  block[8].resize(kWidth - 1, ' ');
  block[8] += "|";
  // line 9
  block.emplace_back("| ");
  block[9] += e.getDescription()[4];
  block[9].resize(kWidth - 1, ' ');
  block[9] += "|";
  // line 10
  block.emplace_back(kHorizontalBar);

  return block;
}

/*
|-------------------------------|
| Banish                    | 2 |
|-------------------------------|
| Spell                         |
|-------------------------------|
| Destroy target minion or      |
| ritual                        |
|                               |
|                               |
|                               |
|-------------------------------|

|-------------------------------|
| Air Elemental             | 0 |
|-------------------------------|
|                         Minion|
|-------------------------------|
|                               |
|                               |
|                               |
|------                   ------|
| 26 |                     | 26 |
|-------------------------------|
*/
