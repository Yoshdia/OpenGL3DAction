#include "RotateComponent.h"
#include "GameObject.h"

RotateComponent::RotateComponent(GameObject* _owner,int _updateOrder):
	Component(_owner,_updateOrder)
{
}


RotateComponent::~RotateComponent()
{
}

void RotateComponent::SetRotation(const float& _rotate, const Vector3& _axis)
{
	//‰ñ“]
	float radian = Math::ToRadians(_rotate);
	Quaternion rot = owner->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	owner->SetRotation(target);
}
