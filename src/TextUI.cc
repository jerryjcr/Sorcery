#include "TextUI.h"

const int kWidth = 33;
const int kHeight = 11;
const int kBoardWidth = 5;

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

void printSorcery() {
  std::fstream sorcery("src/assets/text/sorcery.txt");
  std::string templine;
  while (std::getline(sorcery, templine)) {
    std::cout << templine << std::endl;
  }
}

std::string abilityCostBox(const Minion& m) {
  return std::string(" ") + std::to_string(m.getAbilityCost()) +
         std::string("   |");
}

std::vector<std::string> visualizePlayer(const Player& p, bool isActive) {
  std::vector<std::string> block;
  // line 0
  block.emplace_back(kHorizontalBar);
  // line 1, 2 & 3
  if (isActive) {
    // line 1
    block.emplace_back("| ");
    block.back() += std::to_string(p.getLife());
    block.back().resize(std::string("|     |").length() - 1, ' ');
    block.back() += "|";
    block.back().resize(kWidth - std::string("| 26  |").length(), ' ');
    block.back() += "| " + std::to_string(p.getMagic());
    block.back().resize(kWidth - 1, ' ');
    block.back() += "|";
    // line 2
    block.emplace_back("|------                   ------|");
    // line 3
    block.emplace_back(kEmpty);
  } else {
    // line 1
    block.emplace_back(kEmpty);
    // line 2
    block.emplace_back(kEmpty);
    // line 3
    block.emplace_back("| ");
    block.back().resize(
        (kWidth - p.getName().length() - std::string("| ").length() * 2) / 2,
        ' ');
    block.back() += p.getName();
    block.back().resize(kWidth - 1, ' ');
    block.back() += "|";
  }
  // line 4
  block.emplace_back(kEmpty);
  // line 5
  block.emplace_back(kEmpty);
  // line 6
  block.emplace_back(kEmpty);
  // line 7,8 & 9
  if (isActive) {
    block.emplace_back("| ");
    block.back().resize(
        (kWidth - p.getName().length() - std::string("| ").length() * 2) / 2,
        ' ');
    block.back() += p.getName();
    block.back().resize(kWidth - 1, ' ');
    block.back() += "|";
    // line 8
    block.emplace_back(kEmpty);
    // line 9
    block.emplace_back(kEmpty);
  } else {
    // line 7
    block.emplace_back(kEmpty);
    // line 8
    block.emplace_back("|------                   ------|");
    // line 9
    block.emplace_back("| ");
    block.back() += std::to_string(p.getLife());
    block.back().resize(std::string("|     |").length() - 1, ' ');
    block.back() += "|";
    block.back().resize(kWidth - std::string("| 26  |").length(), ' ');
    block.back() += "| " + std::to_string(p.getMagic());
    block.back().resize(kWidth - 1, ' ');
    block.back() += "|";
  }
  // line 10
  block.emplace_back(kHorizontalBar);

  return block;
}

std::vector<std::string> visualizeCard(Card& c, bool isInspect = false) {
  std::vector<std::string> block;

  CardType type = c.getType();

  // line 0
  block.emplace_back(kHorizontalBar);
  // line 1
  block.emplace_back("| ");

  // to ge the name of the enchantment when inspecting
  if (c.getType() == CardType::Enchantment && isInspect) {
    block.back() += dynamic_cast<Enchantment*>(&c)->getEnchantName();
  } else {
    block.back() += c.getName();
  }
  block.back().resize(kWidth - std::string("| 26  |").length(), ' ');
  block.back() += "| " + std::to_string(c.getCost());
  block.back().resize(kWidth - 1, ' ');
  block.back() += "|";
  // line 2
  block.emplace_back(kHorizontalBar);
  // line 3
  std::string typeName;
  if (type == CardType::Enchantment) {
    typeName = "Enchantment";
    Enchantment* p = dynamic_cast<Enchantment*>(&c);
    if (p->getParent() != nullptr && !isInspect) {
      typeName = "Enchanted Minion";
    }
  } else if (type == CardType::Minion) {
    typeName = "Minion";
  } else if (type == CardType::Spell) {
    typeName = "Spell";
  } else {  // must be ritual
    typeName = "Ritual";
  }

  block.emplace_back("|");
  block.back().resize(kWidth - (typeName + " |").length(), ' ');
  block.back() += typeName + " |";
  // line 4
  block.emplace_back(kHorizontalBar);

  // line 5, 6, 7 (descriptions)
  // for minions with abilities there is a box with a number which could be
  // changed dynamically
  if (isInspect && type == CardType::Enchantment) {
    for (int i = 0; i < 3; i++) {
      block.emplace_back("|");
      block.back() += static_cast<Enchantment*>(&c)->getEnchantDescription()[i];
      block.back().resize(kWidth - 1, ' ');
      block.back() += "|";
    }
  } else if (c.getName() == std::string("Novice Pyromancer") ||
             c.getName() == std::string("Apprentice Summoner") ||
             c.getName() == std::string("Master Summoner")) {
    block.emplace_back("|");
    block.back() += (abilityCostBox(*static_cast<Minion*>(&c)));
    block.back() += c.getDescription()[0];
    block.back().resize(kWidth - 1, ' ');
    block.back() += "|";

    block.emplace_back("|");
    block.back() += ("------");
    block.back() += c.getDescription()[1];
    block.back().resize(kWidth - 1, ' ');
    block.back() += "|";

    block.emplace_back("|");
    block.back() += ("      ");
    block.back() += c.getDescription()[2];
    block.back().resize(kWidth - 1, ' ');
    block.back() += "|";
  } else {
    for (int i = 0; i < 3; i++) {
      block.emplace_back("|");
      block.back() += c.getDescription()[i];
      block.back().resize(kWidth - 1, ' ');
      block.back() += "|";
    }
  }

  // line 8 & 9
  if (type == CardType::Enchantment) {
    // IMPORTANT NOTE: Enchantments have 5 like descriptions not 3 like the rest
    Enchantment* p = dynamic_cast<Enchantment*>(&c);
    if (p->getParent() != nullptr && !isInspect) {
      // line 8
      block.emplace_back("|------                   ------|");
      // line 9
      block.emplace_back("| ");
      block.back() += std::to_string(static_cast<const Minion&>(c).getAttack());
      block.back().resize(std::string("|     |").length() - 1, ' ');
      block.back() += "|";
      block.back().resize(kWidth - std::string("| 26  |").length(), ' ');
      block.back() +=
          "|  " + std::to_string(static_cast<const Minion&>(c).getDefence());
      block.back().resize(kWidth - 1, ' ');
      block.back() += "|";

    } else {
      block.emplace_back("|");
      block.back() += static_cast<const Enchantment&>(c).getEnchantDescription()[3];
      block.back().resize(kWidth - 1, ' ');
      block.back() += "|";
      // line 9
      block.emplace_back("|");
      block.back() += static_cast<const Enchantment&>(c).getEnchantDescription()[4];
      block.back().resize(kWidth - 1, ' ');
      block.back() += "|";
    }
  } else if (type == CardType::Minion) {
    // line 8
    block.emplace_back("|------                   ------|");
    // line 9
    block.emplace_back("| ");
    block.back() += std::to_string(static_cast<const Minion&>(c).getAttack());
    block.back().resize(std::string("|     |").length() - 1, ' ');
    block.back() += "|";
    block.back().resize(kWidth - std::string("| 26  |").length(), ' ');
    block.back() +=
        "|  " + std::to_string(static_cast<const Minion&>(c).getDefence());
    block.back().resize(kWidth - 1, ' ');
    block.back() += "|";
  } else if (type == CardType::Ritual) {
    block.emplace_back("|                         ------|");
    // line 9
    block.emplace_back("| ");
    block.back().resize(kWidth - std::string("| 26  |").length(), ' ');
    block.back() +=
        "| " + std::to_string(static_cast<const Ritual&>(c).getCharges());
    block.back().resize(kWidth - 1, ' ');
    block.back() += "|";
  } else {  // must be spell
    // line 8
    block.emplace_back(kEmpty);
    // line 9
    block.emplace_back(kEmpty);
  }
  // line 10
  block.emplace_back(kHorizontalBar);

  return block;
}

void printRow(std::vector<std::vector<std::string>>& row, bool isBoard = true) {
  for (int i = 0; i < kHeight; i++) {
    if (isBoard) {
      std::cout << "|";
    }
    for (int j = 0; j < kBoardWidth; j++) {
      std::cout << row[j][i];
    }
    if (isBoard) {
      std::cout << "|" << std::endl;
    } else {
      std::cout << std::endl;
    }
  }
}

void printHand(Player& p) {
  std::vector<std::unique_ptr<Card>>& hand = p.getHand();
  std::vector<std::vector<std::string>> handText;
  int currHandSize = 0;
  for (auto it = hand.begin(); it != hand.end(); ++it) {
    handText.emplace_back(visualizeCard(**it));
    currHandSize++;
  }
  while (currHandSize < kBoardWidth) {
    handText.emplace_back(kEmptyBlock);
    currHandSize++;
  }

  for (int i = 0; i < kHeight; i++) {
    for (int j = 0; j < kBoardWidth; j++) {
      std::cout << handText[j][i];
    }
    std::cout << std::endl;
  }
}

void printBoard(Player& active, Player& opponent) {
  std::vector<std::vector<std::string>> currRow;

  std::string theLine = "-";
  theLine.resize(kWidth * kBoardWidth, '-');
  std::cout << "-" << theLine << "-" << std::endl;

  // first row
  if (opponent.getRitual().get() != nullptr) {
    currRow.emplace_back(visualizeCard(*opponent.getRitual()));
  } else {
    currRow.emplace_back(kEmptyBlock);
  }
  currRow.emplace_back(kBlankBlock);
  currRow.emplace_back(visualizePlayer(opponent, false));
  currRow.emplace_back(kBlankBlock);

  if (opponent.getGraveyard().empty()) {
    currRow.emplace_back(kEmptyBlock);
  } else {
    currRow.emplace_back(visualizeCard(*opponent.getGraveyard().back()));
  }

  printRow(currRow);
  currRow.clear();

  // second row
  int currBoardSize = 0;
  std::vector<std::unique_ptr<Minion>>& oppBoard = opponent.getBoard();
  for (auto it = oppBoard.begin(); it != oppBoard.end(); ++it) {
    currRow.emplace_back(visualizeCard(**it));
    currBoardSize++;
  }
  while (currBoardSize < kBoardWidth) {
    currRow.emplace_back(kEmptyBlock);
    currBoardSize++;
  }
  currBoardSize = 0;

  printRow(currRow);
  currRow.clear();

  // sorcery
  printSorcery();

  // third row
  std::vector<std::unique_ptr<Minion>>& activeBoard = active.getBoard();
  for (auto it = activeBoard.begin(); it != activeBoard.end(); ++it) {
    currRow.emplace_back(visualizeCard(**it));
    currBoardSize++;
  }
  while (currBoardSize < kBoardWidth) {
    currRow.emplace_back(kEmptyBlock);
    currBoardSize++;
  }
  currBoardSize = 0;

  printRow(currRow);
  currRow.clear();
  // fourth row

  if (active.getRitual().get() != nullptr) {
    currRow.emplace_back(visualizeCard(*active.getRitual()));
  } else {
    currRow.emplace_back(kEmptyBlock);
  }
  currRow.emplace_back(kBlankBlock);
  currRow.emplace_back(visualizePlayer(active, false));
  currRow.emplace_back(kBlankBlock);

  if (active.getGraveyard().empty()) {
    currRow.emplace_back(kEmptyBlock);
  } else {
    currRow.emplace_back(visualizeCard(*active.getGraveyard().back()));
  }

  printRow(currRow);
  currRow.clear();

  std::cout << "-" << theLine << "-" << std::endl;
}

void inspectCard(Minion& m) {
  std::vector<std::vector<std::string>> currRow;
  currRow.emplace_back(visualizeCard(m));
  currRow.emplace_back(kBlankBlock);
  currRow.emplace_back(kBlankBlock);
  currRow.emplace_back(kBlankBlock);
  currRow.emplace_back(kBlankBlock);
  printRow(currRow, false);

  if (m.getType() == CardType::Enchantment) {
    Enchantment* e = dynamic_cast<Enchantment*>(&m);

    while (e != nullptr) {
      currRow.clear();
      for (int i = 0; i < kBoardWidth; i++) {
        if (e != nullptr) {
          currRow.emplace_back(visualizeCard(*e, true));
        } else {
          currRow.emplace_back(kBlankBlock);
        }

        if (e != nullptr &&
            e->getParent()->getType() == CardType::Enchantment) {
          e = dynamic_cast<Enchantment*>(e->getParent().get());
        } else {
          e = nullptr;
        }
      }
      printRow(currRow, false);
    }
  }
}
