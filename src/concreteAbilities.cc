#include "concreteAbilities.h"

using namespace std;

void BanishAbility::useAbility(TriggerType type, Player& targetPlayer,int boardIndex){
  if (type==TriggerType::None){
    unique_ptr<Card> p=nullptr;
    targetPlayer.setBoard(boardIndex, move(p));
  }
}

void UnsummonAbility::useAbility(TriggerType type, Player& targetPlayer,int boardIndex){
  if (type==TriggerType::None){
    
  }
}