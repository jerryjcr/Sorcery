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

Player::Player(const std::string& name, std::vector<std::unique_ptr<Card>> deck)
    : playerName{name},
      deck{std::move(deck)},
      life{kInitialLife},
      magic{kInitialMagic} {}

void Player::playCard(int handIndex) {
  if (handIndex < 0 || handIndex >= static_cast<int>(hand.size())) return;

  std::unique_ptr<Card>& card = hand[handIndex];
  int cost = card->getCost();
  if (magic < cost) {
    std::cerr << "Not enough magic to play this card." << std::endl;
    return;
  }

  // detect the type of card by casting to the appropriate pointer
  if (Minion* minionRawPtr = dynamic_cast<Minion*>(card.get())) {
    if (board.size() >= 5) {
      std::cerr << "Board is full. Cannot play minion." << std::endl;
      return;
    }
    std::unique_ptr<Minion> minion(static_cast<Minion*>(card.release()));
    board.push_back(std::move(minion));
  } else if (Ritual* ritualRawPtr = dynamic_cast<Ritual*>(card.get())) {
    std::unique_ptr<Ritual> newRitual(static_cast<Ritual*>(card.release()));
    ritual = std::move(newRitual);
  } else if (Spell* spellRawPtr = dynamic_cast<Spell*>(card.get());
             spellRawPtr && !spellRawPtr->requiresTarget()) {
    std::unique_ptr<Spell> spell(static_cast<Spell*>(card.release()));
    spell->useSpell();  // call the version of the method with no target
  } else {
    std::cerr << "Must specify target player and index to play this card."
              << std::endl;
    return;
  }

  magic -= cost;
  hand.erase(hand.begin() + handIndex);
}

void Player::playCard(int handIndex, Player& targetPlayer, int targetIndex) {
  if (handIndex < 0 || handIndex >= static_cast<int>(hand.size())) {
    std::cerr << "Hand index out of bounds." << std::endl;
    return;
  }
  if (targetIndex < 0 ||
      targetIndex >= static_cast<int>(targetPlayer.board.size() + 1)) {
    std::cerr << "Target index out of bounds." << std::endl;
    return;
  }
  if (targetIndex == 0 && !targetPlayer.ritual) {
    std::cerr << "Target ritual does not exist." << std::endl;
    return;
  }

  std::unique_ptr<Card>& card = hand[handIndex];
  int cost = card->getCost();
  if (magic < cost) {
    std::cerr << "Not enough magic to play this card." << std::endl;
    return;
  }

  // detect the type of card by casting to the appropriate pointer
  if (Spell* spellRawPtr = dynamic_cast<Spell*>(card.get());
      spellRawPtr && spellRawPtr->requiresTarget()) {
    TargetType targetType;
    if (targetIndex == 0) {
      targetType = TargetType::Ritual;
    } else {
      targetType = TargetType::Minion;
    }
    if (spellRawPtr->canTarget(targetType)) {
      std::unique_ptr<Spell> spell(static_cast<Spell*>(card.release()));
      spell->useSpell(targetPlayer, targetIndex);
    } else {
      std::cerr << "This spell cannot target a "
                << (targetType == TargetType::Minion ? "minion." : "ritual.")
                << std::endl;
      return;
    }
  } else {
    std::cerr << "This card does not require a target." << std::endl;
    return;
  }

  magic -= cost;
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
  if (handIndex < 0 || handIndex >= static_cast<int>(hand.size())) {
    std::cerr << "Hand index out of bounds." << std::endl;
    return;
  }

  hand.erase(hand.begin() + handIndex);
}

void Player::attackMinion(int boardIndex, Player& targetPlayer,
                          int targetIndex) {
  if (boardIndex < 0 || boardIndex >= static_cast<int>(board.size())) {
    std::cerr << "Board index out of bounds." << std::endl;
    return;
  }
  if (targetIndex <= 0 ||
      targetIndex >= static_cast<int>(targetPlayer.board.size() + 1)) {
    std::cerr << "Target index out of bounds." << std::endl;
    return;
  }

  board[boardIndex]->attackMinion(*targetPlayer.board[targetIndex]);
}

void Player::attackPlayer(int boardIndex, Player& targetPlayer) {
  if (boardIndex < 0 || boardIndex >= static_cast<int>(board.size())) {
    std::cerr << "Board index out of bounds." << std::endl;
    return;
  }

  board[boardIndex]->attackPlayer(targetPlayer);
}

void Player::use(int boardIndex) {
  if (boardIndex < 0 || boardIndex >= static_cast<int>(board.size())) {
    std::cerr << "Board index out of bounds." << std::endl;
    return;
  }

  if (board[boardIndex]->requiresTarget()) {
    std::cerr << "This ability does not require a target." << std::endl;
    return;
  }

  board[boardIndex]->activateAbility();
}

void Player::use(int boardIndex, Player& targetPlayer, int targetIndex) {
  if (boardIndex < 0 || boardIndex >= static_cast<int>(board.size())) {
    std::cerr << "Board index out of bounds." << std::endl;
    return;
  }
  if (targetIndex < 0 ||
      targetIndex >= static_cast<int>(targetPlayer.board.size() + 1)) {
    std::cerr << "Target index out of bounds." << std::endl;
    return;
  }
  if (targetIndex == 0 && !targetPlayer.ritual) {
    std::cerr << "Target ritual does not exist." << std::endl;
    return;
  }

  TargetType targetType;
  if (targetIndex == 0) {
    targetType = TargetType::Ritual;
  } else {
    targetType = TargetType::Minion;
  }
  if (board[boardIndex]->canTarget(targetType)) {
    board[boardIndex]->activateAbility(targetPlayer, targetIndex);
  } else {
    std::cerr << "This ability cannot target a "
              << (targetType == TargetType::Minion ? "minion." : "ritual.")
              << std::endl;
    return;
  }
}

int Player::getLife() const { return life; }

int Player::getMagic() const { return magic; }

void Player::adjustLife(int amount) { life += amount; }

void Player::adjustMagic(int amount) { magic += amount; }

void Player::setBoard(int index, std::unique_ptr<Card> card) {
  // todo
}
