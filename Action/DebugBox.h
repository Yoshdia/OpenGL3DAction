#pragma once
#include "GameObject.h"


class DebugBox :
	public GameObject
{
public:
	DebugBox();
	~DebugBox();

	void GameObjectInput(const InputState& _keyState)override;
};

