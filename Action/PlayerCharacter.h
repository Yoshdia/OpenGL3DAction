#pragma once
#include "GameObject.h"

struct InputState;

class PlayerCharacter :
	public GameObject
{
public:
	PlayerCharacter();
	~PlayerCharacter();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState & _keyState) override;

private:
	class SpriteComponent* spriteComponent;
	class CameraComponent* camera;
};

