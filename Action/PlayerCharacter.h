#pragma once
#include "GameObject.h"

struct InputState;

/*
 @file PlayerCharacter.h
 @brief �v���C���[
	*/
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
	class SkeltonObjectChecker* footChecker;
	float canNotActionTime;

	Vector3 velo;

	Vector3 movement;
	Vector3 inputDirection;
	bool attackBottonInput;
	bool rangeAttackBottonInput;

	//�W�����v����
	bool isJump;
	//�W�����v�� 
	static const float jumpPower;
};

