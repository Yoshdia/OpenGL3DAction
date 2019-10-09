#pragma once
#include "GameObject.h"

struct InputState;


class PlayerGameObject :
	public GameObject
{
public:
	PlayerGameObject();
	~PlayerGameObject();

	void UpdateGameObject(float _deltaTime) override;
	void GameObjectInput(const InputState& _keyState) override;

private:
	class SpriteComponent* spriteComponent;
};

