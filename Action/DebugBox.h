#pragma once
#include "GameObject.h"


class DebugBox :
	public GameObject
{
public:
	DebugBox(Vector3 p,Vector3 _size=Vector3(50,50,50),Tag _tag=Tag::GroundTag);
	~DebugBox();

	void GameObjectInput(const InputState& _keyState)override;
};

