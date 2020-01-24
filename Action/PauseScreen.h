#pragma once
#include "GameObject.h"
class PauseScreen :
	public GameObject
{
public:
	PauseScreen();
	~PauseScreen();

	void PausingUpdateGameObject()override;
	void GameObjectInput(const InputState& _keyState)override;
	bool GetEndPause() { return endPause; }
private:
	bool endPause;
};

