#include "AttackPlayerComponent.h"
#include "AttackOnce.h"


AttackPlayerComponent::AttackPlayerComponent(GameObject* _owner, int _updateOrder ):
	Component(_owner,updateOrder)
{
	attack = new AttackOnce();
}


AttackPlayerComponent::~AttackPlayerComponent()
{
	if (attack!=nullptr)
	{
		delete attack;
	}
}

void AttackPlayerComponent::Update(float _deltaTime)
{
}

float AttackPlayerComponent::Attack()
{
	attack->Attack();

	return attack->GetCanNotActionTime();
}
