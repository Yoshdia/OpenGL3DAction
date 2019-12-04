#pragma once
#include "Component.h"
#include "Math.h"

class RotateComponent :
	public Component
{
public:
	RotateComponent(GameObject* _owner, int _updateOrder=100);
	~RotateComponent();

	void SetRotation(const float& _rotate,const Vector3& _axis);
};

