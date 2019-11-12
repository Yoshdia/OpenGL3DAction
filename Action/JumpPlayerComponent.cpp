#include "JumpPlayerComponent.h"
#include "Math.h"


JumpPlayerComponent::JumpPlayerComponent(GameObject * _owner, int _updateOrder,float _jumpPower) :
	Component(_owner, _updateOrder),
	jumpPower(0),
	jumpPowerMax(_jumpPower)
{
}

JumpPlayerComponent::~JumpPlayerComponent()
{
}

void JumpPlayerComponent::Jump(float _deltaTime)
{ 
	jumpPower = jumpPowerMax;
	owner->SetPosition(owner->GetPosition() + Vector3(0, jumpPower, 0));
	//noGroundTime = 0;
}

void JumpPlayerComponent::Update(float _deltaTime)
{
	//if (jumpPower <= 0)
	//{
	//	return;
	//}
	//owner->SetPosition(owner->GetPosition() + Vector3(0, jumpPower, 0));
	//if (noGroundTime < 120)
	{
		//noGroundTime++;

		//owner->SetPosition(owner->GetPosition() + Vector3(0, jumpPower, 0));

	}
	//else
	{

	}
}
