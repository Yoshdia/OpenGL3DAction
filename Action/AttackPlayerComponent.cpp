#include "AttackPlayerComponent.h"
#include "AttackPlayerOnce.h"
#include "AttackPlayerTwice.h"
#include "AttackPlayerThird.h"
#include "RangeAttackPlayer.h"
#include "GameObject.h"
#include "ComboMeanPlayerBase.h"


AttackPlayerComponent::AttackPlayerComponent(GameObject* _owner, int _updateOrder) :
	Component(_owner, updateOrder)
{

}

AttackPlayerComponent::~AttackPlayerComponent()
{
	if (firstSlotAttack != nullptr)
	{
		delete firstSlotAttack;
	}
	if (secondSlotAttack != nullptr)
	{
		delete secondSlotAttack;
	}
}

void AttackPlayerComponent::Update(float _deltaTime)
{

}

float AttackPlayerComponent::Attack(const int& _direction, const int& _slot,bool& _range)
{
	
}

