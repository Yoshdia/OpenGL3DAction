#include "RotateComponent.h"
#include "GameObject.h"

RotateComponent::RotateComponent(GameObject* _owner,int _updateOrder):
	Component(_owner,_updateOrder)
{
}


RotateComponent::~RotateComponent()
{
}

/*
@brief ��]���s��
@param _rotate �p�x
@param _axis ��]��
*/
void RotateComponent::SetRotation(const float& _rotate, const Vector3& _axis)
{
	//��]
	float radian = Math::ToRadians(_rotate);
	Quaternion rot = owner->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	owner->SetRotation(target);
}
