#include "GuardPlayerComponent.h"
#include "ShieldWeapon.h"

const float GuardPlayerComponent::canNotActionTime = 30.0f;
const float GuardPlayerComponent::ShieldSpace = 120.0f;

GuardPlayerComponent::GuardPlayerComponent(GameObject* owner, int updateOrder):
	Component(owner,updateOrder)
{
	rightShield = new ShieldWeapon(std::bind(&GuardPlayerComponent::AddGuardingObjectId, this, std::placeholders::_1));
	leftShield = new ShieldWeapon(std::bind(&GuardPlayerComponent::AddGuardingObjectId, this, std::placeholders::_1));
}

GuardPlayerComponent::~GuardPlayerComponent()
{
	while (!guardingObjectIds.empty())
	{
		guardingObjectIds.pop_back();
	}
}

bool GuardPlayerComponent::SearchObjectId(const int& _id)
{
	for (auto itr : guardingObjectIds)
	{
		if (itr == _id)
		{
			return true;
		}
	}
	return false;
}

float GuardPlayerComponent::Guard()
{
	//盾を生成する座標
	Vector3 shieldPosition = owner->GetPosition();
	//左右間をセットし代入
	shieldPosition.x -= ShieldSpace / 2;
	rightShield->CreateShield(shieldPosition);
	shieldPosition.x += ShieldSpace;
	leftShield->CreateShield(shieldPosition);

	return canNotActionTime;
}

void GuardPlayerComponent::Update(float _deltaTime)
{
	if (rightShield->GetState() == State::Dead || leftShield->GetState() == State::Dead)
	{
		while (!guardingObjectIds.empty())
		{
			guardingObjectIds.pop_back();
		}
	}
}

void GuardPlayerComponent::AddGuardingObjectId(const int& _id)
{
	for (auto itr : guardingObjectIds)
	{
		if (itr == _id)
		{
			return;
		}
	}
	guardingObjectIds.push_back(_id);
}
