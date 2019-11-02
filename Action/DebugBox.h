#pragma once
#include "GameObject.h"


class DebugBox :
	public GameObject
{
public:
	DebugBox(Vector3 p);
	~DebugBox();

	void GameObjectInput(const InputState& _keyState)override;
};

