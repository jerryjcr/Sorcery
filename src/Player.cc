#include "Player.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "Card.h"
#include "Enchantment.h"
#include "Minion.h"
#include "Ritual.h"
#include "Spell.h"

const int kInitialLife = 20;
const int kInitialMagic = 3;
const int kMaxHandSize = 5;

bool Player::boundIndex(int index, int lower, int upper,
                        const std::string& indexName) const {
  if (index < lower || index > upper) {
    std::cerr << "Invalid input: " << indexName << " index is out of bounds."
              << std::endl;
    return false;
  }
  return true;
}

bool Player::canAfford(int cost) const {
  if (magic < cost) {
    std::cout << "Not enough magic to play this card." << std::endl;
    return false;
  }
  return true;
}

Player::Player(const std::string& name, std::vector<std::unique_ptr<Card>> deck)
    : name{name},
      life{kInitialLife},
      magic{kInitialMagic},
      deck{std::move(deck)} {}

void Player::shuffleDeck() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

void Player::playCard(int handIndex, Player& inactivePlayer) {
  if (!boundIndex(handIndex, 1, static_cast<int>(hand.size()), "Hand")) return;

  handIndex--;

  std::unique_ptr<Card>& card = hand[handIndex];
  int cost = card->getCost();
  if (!canAfford(cost)) return;

  // detect the type of card by casting to the appropriate pointer
  if (card->getType() == CardType::Minion) {
    if (board.size() >= 5) {
      std::cout << "Board is full. Cannot play minion." << std::endl;
      return;
    }
    std::unique_ptr<Minion> minion(dynamic_cast<Minion*>(card.release()));
    board.push_back(std::move(minion));
  } else if (card->getType() == CardType::Spell) {
    std::unique_ptr<Spell> spell(dynamic_cast<Spell*>(card.release()));
    // call the version of the method with no target
    spell->useCardAbility(*this, inactivePlayer);
  } else if (card->getType() == CardType::Ritual) {
    std::unique_ptr<Ritual> newRitual(static_cast<Ritual*>(card.release()));
    ritual = std::move(newRitual);
  } else {
    std::cerr << "Invalid input: Must specify target player and index to play "
                 "this card."
              << std::endl;
    return;
  }

  magic -= cost;
  hand.erase(hand.begin() + handIndex);
}

void Player::playCard(int handIndex, Player& targetPlayer, int targetIndex) {
  if (!boundIndex(handIndex, 1, static_cast<int>(hand.size()), "Hand")) return;
  if (!boundIndex(targetIndex, 1,
                  static_cast<int>(targetPlayer.board.size()) + 1, "Target"))
    return;

  handIndex--;
  targetIndex--;

  if (targetIndex == 5 && !targetPlayer.ritual) {
    std::cout << "Target ritual does not exist." << std::endl;
    return;
  }

  std::unique_ptr<Card>& card = hand[handIndex];
  int cost = card->getCost();
  if (!canAfford(cost)) return;

  // detect the type of card by casting to the appropriate pointer
  if (card->getType() == CardType::Spell) {
    std::unique_ptr<Spell> spell(dynamic_cast<Spell*>(card.release()));
    if (targetIndex == 5) {
      spell->useCardAbility(targetPlayer, *ritual);
    } else {
      spell->useCardAbility(targetPlayer, *targetPlayer.board[targetIndex]);
    }
  } else if (card->getType() == CardType::Enchantment) {
    std::unique_ptr<Enchantment> enchantment(
        dynamic_cast<Enchantment*>(card.release()));
    if (targetIndex == 5) {
      std::cout << "Cannot play an enchantment on a ritual." << std::endl;
    } else {
      std::unique_ptr<Minion> targetMinion =
          std::move(targetPlayer.board[targetIndex]);

      enchantment->setParent(std::move(targetMinion));

      targetPlayer.board[targetIndex] = std::move(enchantment);
    }
  } else {
    std::cerr << "Invalid input: This card does not require a target."
              << std::endl;
    return;
  }

  magic -= cost;
  hand.erase(hand.begin() + handIndex);
}

void Player::drawCard() {
  if (deck.empty()) {
    std::cout << "Deck is empty. Cannot draw a card." << std::endl;
    return;
  }
  if (hand.size() >= kMaxHandSize) {
    std::cout << "Hand is full. Cannot draw a card." << std::endl;
    return;
  }

  hand.push_back(std::move(deck.back()));
  deck.pop_back();
}

void Player::discard(int handIndex) {
  if (!boundIndex(handIndex, 1, static_cast<int>(hand.size()), "Hand")) return;

  hand.erase(hand.begin() + handIndex);
}

void Player::attackMinion(int boardIndex, Player& targetPlayer,
                          int targetIndex) {
  if (!boundIndex(boardIndex, 1, static_cast<int>(board.size()), "Board"))
    return;
  if (!boundIndex(targetIndex, 1, static_cast<int>(targetPlayer.board.size()),
                  "Target"))
    return;

  boardIndex--;
  targetIndex--;

  board[boardIndex]->attackMinion(*targetPlayer.board[targetIndex]);
}

void Player::attackPlayer(int boardIndex, Player& targetPlayer) {
  if (!boundIndex(boardIndex, 1, static_cast<int>(board.size()), "Board"))
    return;

  boardIndex--;

  board[boardIndex]->attackPlayer(targetPlayer);
}

void Player::use(int boardIndex, Player& inactivePlayer) {
  if (!boundIndex(boardIndex, 1, static_cast<int>(board.size()), "Board"))
    return;

  boardIndex--;

  if (board[boardIndex]->useCardAbility(*this, inactivePlayer)) {
    magic -= board[boardIndex]->getAbilityCost();
  }
}

void Player::use(int boardIndex, Player& targetPlayer, int targetIndex) {
  if (!boundIndex(boardIndex, 1, static_cast<int>(board.size()), "Board"))
    return;
  if (!boundIndex(targetIndex, 1,
                  static_cast<int>(targetPlayer.board.size()) + 1, "Target"))
    return;

  boardIndex--;
  targetIndex--;

  if (targetIndex == 5 && !targetPlayer.ritual) {
    std::cout << "Target ritual does not exist." << std::endl;
    return;
  }

  Card& targetCard = *targetPlayer.board[targetIndex];

  if (board[boardIndex]->useCardAbility(targetPlayer, targetCard)) {
    magic -= board[boardIndex]->getAbilityCost();
  }
}

void Player::resetBoardActions() {
  for (auto& minion : board) {
    if (!minion) {
      std::cerr << "Error: Null minion found in board during actions reset."
                << std::endl;
      return;
    }
    minion->resetActions();
  }
}

void Player::checkForDeaths() {
  for (int i = 0; i < static_cast<int>(board.size()); i++) {
    if (board[i]->getDefence() <= 0) {
      killMinion(i);
      i--;  // Adjust index after removal
    }
  }
}

void Player::killMinion(int boardIndex) {
  if (!boundIndex(boardIndex, 1, static_cast<int>(board.size()), "Board"))
    return;

  boardIndex--;

  graveyard.push_back(std::move(board[boardIndex]));
  board.erase(board.begin() + boardIndex);
}

void Player::killRitual() {
  if (!ritual) {
    std::cout << "Target ritual does not exist." << std::endl;
    return;
  }
  ritual.reset();
}

void Player::returnMinionToHand(int boardIndex) {
  if (!boundIndex(boardIndex, 1, static_cast<int>(board.size()), "Board"))
    return;

  boardIndex--;

  if (hand.size() >= kMaxHandSize) {
    std::cout << "Hand is full. Cannot return card to hand." << std::endl;
    return;
  }

  hand.push_back(std::move(board[boardIndex]));
  board.erase(board.begin() + boardIndex);
}

void Player::reviveMinion() {
  if (board.size() >= 5) {
    std::cout << "Board is full. Cannot revive minion." << std::endl;
    return;
  }

  board.push_back(std::move(graveyard.back()));
  graveyard.pop_back();
}

const std::string& Player::getName() const { return name; }

int Player::getLife() const { return life; }

int Player::getMagic() const { return magic; }

void Player::adjustLife(int amount) { life += amount; }

void Player::adjustMagic(int amount) { magic += amount; }

std::vector<std::unique_ptr<Card>>& Player::getHand() { return hand; }

std::vector<std::unique_ptr<Minion>>& Player::getBoard() { return board; }

std::unique_ptr<Ritual>& Player::getRitual() { return ritual; }

std::vector<std::unique_ptr<Minion>>& Player::getGraveyard() {
  return graveyard;
}
