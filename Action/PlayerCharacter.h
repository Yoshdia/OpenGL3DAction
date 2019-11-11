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
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	class AnimationPlayerComponent* animationComponent;
	//class CameraComponent* camera;
	class AttackPlayerComponent* attack;
	class InputMovePlayerComponent* inputMovePlayerComponent;
	class JumpPlayerComponent* jumpPlayerComponent;
	class GravityComponent* gravityComponent;
	class FootSole* footSole;
	float canNotActionTime;

	Vector3 movement;
	Vector3 inputDirection;
	bool attackBottonInput;

	//ジャンプ中か
	bool isJump;
	//ジャンプ力 
	//@sa JumpPlayerComponent
	static const float jumpPower;
};

