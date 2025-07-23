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
    std::fstream sorcery("sorcery.txt");
    std::string templine;
    while (std::getline(sorcery, templine)) {
        std::cout << templine << std::endl;
    }
}

std::vector<std::string> visualizePlayer(const Player& p, bool isActive) {
  std::vector<std::string> block;
  // line 0
  block.emplace_back(kHorizontalBar);
  // line 1, 2 & 3
  if (isActive) {
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
  } else {
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
  } else {
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
  }
  // line 10
  block.emplace_back(kHorizontalBar);

  return block;
}

std::vector<std::string> visualizeCard(const Card& c) {
  std::vector<std::string> block;

  CardType type = c.getType();

  // line 0
  block.emplace_back(kHorizontalBar);
  // line 1
  block.emplace_back("| ");
  block[1] += c.getName();
  block[1].resize(kWidth - std::string("| 26 |").length(), ' ');
  block[1] += "| " + std::to_string(c.getCost());
  block[1].resize(kWidth - 1, ' ');
  block[1] += "|";
  // line 2
  block.emplace_back(kHorizontalBar);
  // line 3
  std::string typeName;
  if (type == CardType::Minion) {
    typeName = "Minion";
  } else if (type == CardType::Enchantment) {
    typeName = "Enchantment";
  } else if (type == CardType::Spell) {
    typeName = "Spell";
  } else {  // must be ritual
    typeName = "Ritual";
  }

  block.emplace_back("|");
  block[3].resize(kWidth - (typeName + " |").length(), ' ');
  block[3] += typeName + " |";
  // line 4
  block.emplace_back(kHorizontalBar);
  // line 5
  block.emplace_back("| ");
  block[5] += c.getDescription()[0];
  block[5].resize(kWidth - 1, ' ');
  block[5] += "|";
  // line 6
  block.emplace_back("| ");
  block[6] += c.getDescription()[0];
  block[6].resize(kWidth - 1, ' ');
  block[6] += "|";
  // line 7
  block.emplace_back("| ");
  block[7] += c.getDescription()[0];
  block[7].resize(kWidth - 1, ' ');
  block[7] += "|";
  // line 8 & 9
  if (type == CardType::Minion) {
    // line 8
    block.emplace_back("|------                   ------|");
    // line 9
    block.emplace_back("| ");
    block[9] += std::to_string(static_cast<const Minion&>(c).getAttack());
    block[9].resize(std::string("|   ").length(), ' ');
    block[9] += "|";
    block[9].resize(kWidth - std::string("| 26 |").length(), ' ');
    block[9] +=
        "| " + std::to_string(static_cast<const Minion&>(c).getDefence());
    block[9].resize(kWidth - 1, ' ');
    block[9] += "|";
  } else if (type == CardType::Enchantment) {
    // IMPORTANT NOTE: Enchantments have 5 like descriptions not 3 like the rest

    block.emplace_back("| ");
    block[8] += static_cast<const Enchantment&>(c).getDescription()[3];
    block[8].resize(kWidth - 1, ' ');
    block[8] += "|";
    // line 9
    block.emplace_back("| ");
    block[9] += static_cast<const Enchantment&>(c).getDescription()[4];
    block[9].resize(kWidth - 1, ' ');
    block[9] += "|";
  } else if (type == CardType::Ritual) {
    block.emplace_back("|                         ------|");
    // line 9
    block.emplace_back("| ");
    block[9].resize(kWidth - std::string("| 26 |").length(), ' ');
    block[9] +=
        "| " + std::to_string(static_cast<const Ritual&>(c).getCharges());
    block[9].resize(kWidth - 1, ' ');
    block[9] += "|";
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

void printRow(std::vector<std::vector<std::string>>& row) {
  for (int i = 0; i < kHeight; i++) {
    std::cout << "|";
    for (int j = 0; j < kBoardWidth; j++) {
      std::cout << row[j][i];
    }
    std::cout << "|" << std::endl;
  }
}

void printHand(Player& p) {
  std::vector<std::unique_ptr<Card>>& hand = p.getHand();
  std::vector<std::vector<std::string>> hand_text;
  int currHandSize = 0;
  for (auto it = hand.begin(); it != hand.end(); ++it) {
    hand_text.emplace_back(visualizeCard(**it));
    currHandSize++;
  }
  while (currHandSize < kBoardWidth) {
    hand_text.emplace_back(kEmptyBlock);
    currHandSize++;
  }

  for (int i = 0; i < kHeight; i++) {
    for (int j = 0; j < kBoardWidth; j++) {
      std::cout << hand_text[j][i];
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

  if (active.getRitual() != nullptr) {
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
