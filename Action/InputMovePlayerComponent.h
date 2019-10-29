#pragma once
#include "Component.h"
#include "InputSystem.h"
#include"Math.h"

class InputMovePlayerComponent final:
	public Component
{
public:
	InputMovePlayerComponent(GameObject* owner,int updateOrder);
	~InputMovePlayerComponent() {};

	Vector3 InputMoveMent(const InputState& _state);
};

