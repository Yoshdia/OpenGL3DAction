#pragma once
#include "Component.h"
#include "GameObject.h"


class JumpPlayerComponent :
	public Component
{
public:
	JumpPlayerComponent(GameObject* _owner, int _updateOrder);
	~JumpPlayerComponent();

	void Jump(float _deltaTime);
	void Jumping(float _deltaTime);
private:
	static const float jumpPowerMax;
	 float jumpPower;
	Vector3 jumpPosition;
};

