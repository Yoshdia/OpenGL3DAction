#pragma once
#include "GameObject.h"


class DebugBox :
	public GameObject
{
public:
	DebugBox(Vector3 p);
	DebugBox(Vector3 p,Tag _tag);
	~DebugBox();

	void GameObjectInput(const InputState& _keyState)override;
};

