#include "JumpPlayerComponent.h"
#include "Math.h"

const float JumpPlayerComponent::jumpPowerMax = 40;

JumpPlayerComponent::JumpPlayerComponent(GameObject * _owner, int _updateOrder) :
	Component(_owner, _updateOrder)
{
	jumpPosition = _owner->GetPosition();
}

JumpPlayerComponent::~JumpPlayerComponent()
{
}

void JumpPlayerComponent::Jump(float _deltaTime)
{
	jumpPower = jumpPowerMax;
	//jumpPosition = owner->GetPosition()+Vector3(0,jumpHeight,0);
	//owner->SetPosition(jumpPosition);
}

void JumpPlayerComponent::Jumping(float _deltaTime)
{
	if (jumpPower < 0)
	{
		return;
	}
	owner->SetPosition(owner->GetPosition() + Vector3(0, jumpPower, 0));
	jumpPower--;
	//Vector3 position = Vector3::Lerp(owner->GetPosition(), jumpPosition,jumpPower);
	//owner->SetPosition(position);
}
