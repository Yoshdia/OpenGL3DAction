#include "GravityComponent.h"
#include "GameObject.h"


GravityComponent::GravityComponent(GameObject* _owner, int _updateOrder, int _gravityPower) :
	Component(_owner, updateOrder),
	gravityPower(_gravityPower),
	noGroundTime(0)
{
}


GravityComponent::~GravityComponent()
{
}

void GravityComponent::Update(float _deltaTime)
{
}

void GravityComponent::Gravity(float _deltaTime)
{
	noGroundTime++;
 	float power = (_deltaTime*noGroundTime) * -9.8f;
	owner->SetPosition(owner->GetPosition() + Vector3(0, (float)power, 0));
}

void GravityComponent::IsGround()
{
	noGroundTime = 0;
}
