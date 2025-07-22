#include "Player.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Card.h"
#include "Minion.h"
#include "Ritual.h"
#include "Spell.h"

const int kInitialLife = 20;
const int kInitialMagic = 3;
const int kMaxHandSize = 5;

bool Player::boundIndex(int index, int lower, int upper,
                        const std::string& indexName) const {
  if (index < lower || index > upper) {
    std::cerr << indexName << " index is out of bounds." << std::endl;
    return false;
  }
  return true;
}

bool Player::canAfford(int cost) const {
  if (magic < cost) {
    std::cerr << "Not enough magic to play this card." << std::endl;
    return false;
  }
  return true;
}

Player::Player(const std::string& name, std::vector<std::unique_ptr<Card>> deck)
    : name{name},
      life{kInitialLife},
      magic{kInitialMagic},
      deck{std::move(deck)} {}

void Player::playCard(int handIndex) {
  if (!boundIndex(handIndex, 0, static_cast<int>(hand.size()) - 1, "Hand"))
    return;

  std::unique_ptr<Card>& card = hand[handIndex];
  if (!canAfford(card->getCost())) return;

  // detect the type of card by casting to the appropriate pointer
  if (card->getType() == CardType::Minion) {
    if (board.size() >= 5) {
      std::cerr << "Board is full. Cannot play minion." << std::endl;
      return;
    }
    std::unique_ptr<Minion> minion(dynamic_cast<Minion*>(card.release()));
    board.push_back(std::move(minion));
  } else if (card->getType() == CardType::Spell) {
    std::unique_ptr<Spell> spell(dynamic_cast<Spell*>(card.release()));
    spell->useSpell();  // call the version of the method with no target
  } else if (card->getType() == CardType::Ritual) {
    std::unique_ptr<Ritual> newRitual(static_cast<Ritual*>(card.release()));
    ritual = std::move(newRitual);
  } else {
    std::cerr << "Must specify target player and index to play this card."
              << std::endl;
    return;
  }

  magic -= card->getCost();
  hand.erase(hand.begin() + handIndex);
}

void Player::playCard(int handIndex, Player& targetPlayer, int targetIndex) {
  if (!boundIndex(handIndex, 0, static_cast<int>(hand.size()) - 1, "Hand"))
    return;
  if (!boundIndex(targetIndex, 0, static_cast<int>(targetPlayer.board.size()),
                  "Target"))
    return;
  if (targetIndex == 0 && !targetPlayer.ritual) {
    std::cerr << "Target ritual does not exist." << std::endl;
    return;
  }

  std::unique_ptr<Card>& card = hand[handIndex];
  if (!canAfford(card->getCost())) return;

  // detect the type of card by casting to the appropriate pointer
  if (card->getType() == CardType::Spell) {
    std::unique_ptr<Spell> spell(dynamic_cast<Spell*>(card.release()));
    spell->useSpell(targetPlayer, targetIndex);
  } else {
    std::cerr << "This card does not require a target." << std::endl;
    return;
  }

  magic -= card->getCost();
  hand.erase(hand.begin() + handIndex);
}

void Player::drawCard() {
  if (deck.empty()) {
    std::cerr << "Deck is empty. Cannot draw a card." << std::endl;
    return;
  }
  if (hand.size() >= kMaxHandSize) {
    std::cerr << "Hand is full. Cannot draw a card." << std::endl;
    return;
  }

  hand.push_back(std::move(deck.back()));
  deck.pop_back();
}

void Player::discard(int handIndex) {
  if (!boundIndex(handIndex, 0, static_cast<int>(hand.size()) - 1, "Hand"))
    return;

  hand.erase(hand.begin() + handIndex);
}

void Player::attackMinion(int boardIndex, Player& targetPlayer,
                          int targetIndex) {
  if (!boundIndex(boardIndex, 1, static_cast<int>(board.size()), "Board"))
    return;
  if (!boundIndex(targetIndex, 1, static_cast<int>(targetPlayer.board.size()),
                  "Target"))
    return;

  board[boardIndex]->attackMinion(*targetPlayer.board[targetIndex]);
}

void Player::attackPlayer(int boardIndex, Player& targetPlayer) {
  if (!boundIndex(boardIndex, 1, static_cast<int>(board.size()), "Board"))
    return;

  board[boardIndex]->attackPlayer(targetPlayer);
}

void Player::use(int boardIndex, Player& inactivePlayer) {
  if (!boundIndex(boardIndex, 1, static_cast<int>(board.size()), "Board"))
    return;

  board[boardIndex]->useCardAbility(*this, inactivePlayer);
}

void Player::use(int boardIndex, Player& targetPlayer, int targetIndex) {
  if (!boundIndex(boardIndex, 1, static_cast<int>(board.size()), "Board"))
    return;
  if (targetIndex < 0 ||
      targetIndex > static_cast<int>(targetPlayer.board.size())) {
    std::cerr << "Target index out of bounds." << std::endl;
    return;
  }
  if (targetIndex == 0 && !targetPlayer.ritual) {
    std::cerr << "Target ritual does not exist." << std::endl;
    return;
  }

  board[boardIndex]->useCardAbility()

  if (board[boardIndex]->canTarget(targetType)) {
    board[boardIndex]->activateAbility(targetPlayer, targetIndex);
  } else {
    std::cerr << "This ability cannot target a "
              << (targetType == TargetType::Minion ? "minion." : "ritual.")
              << std::endl;
    return;
  }
}

int Player::getCost(int handIndex) const {
  if (handIndex < 0 || handIndex >= static_cast<int>(hand.size())) {
    std::cerr << "Hand index out of bounds." << std::endl;
    return -1;
  }
  return hand[handIndex]->getCost();
}

int Player::boardCost(int boardIndex) const {
  if (boardIndex < 0 || boardIndex >= static_cast<int>(board.size())) {
    std::cerr << "Board index out of bounds." << std::endl;
    return -1;
  }
  return board[boardIndex]->getCost();
}

const std::string& Player::getName() const { return name; }

int Player::getLife() const { return life; }

int Player::getMagic() const { return magic; }

void Player::adjustLife(int amount) { life += amount; }

void Player::adjustMagic(int amount) { magic += amount; }

void Player::setBoard(int index, std::unique_ptr<Card> card) {
  // todo
}
