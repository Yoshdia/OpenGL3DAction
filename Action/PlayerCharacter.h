#pragma once
#include "GameObject.h"



class PlayerCharacter :
	public GameObject
{
public:
	PlayerCharacter();
	~PlayerCharacter();

	void UpdateGameObject(float _deltaTime)override;

private:
	class SpriteComponent* spriteComponent;
	class CameraComponent* camera;
};

