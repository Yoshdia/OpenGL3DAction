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
	class AnimationPlayerComponent* animationComponent;
	class CameraComponent* camera;
	class AttackPlayerComponent* attack;
	class InputMovePlayerComponent* inputMovePlayerComponent;

	float canNotActionTime;

	Vector3 movement;
	Vector3 inputDirection;
	bool attackBottonInput;
};

