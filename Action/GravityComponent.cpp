#include "GravityComponent.h"
#include "GameObject.h"


GravityComponent::GravityComponent(GameObject* _owner,int _updateOrder,int _gravityPower):
	Component(_owner,updateOrder),
	gravityPower(_gravityPower)
{
}


GravityComponent::~GravityComponent()
{
}

void GravityComponent::Update(float _deltaTime)
{
	owner->SetPosition(owner->GetPosition() + Vector3(0, (float)-gravityPower, 0));
}
