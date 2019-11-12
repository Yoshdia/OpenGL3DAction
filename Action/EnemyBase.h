#pragma once
#include "GameObject.h"
#include <string>

enum EnemyMoveDirection
{
	right = 1,
	left = -1,
};

class EnemyBase abstract:
	public GameObject
{
public:
	EnemyBase(const std::string& meshName);
	~EnemyBase();
	void UpdateGameObject(float _deltaTime)override;

private:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair)override;
	virtual void UpdateEnemyObject(float _deltaTime) {};
	class GravityComponent* gravityComponent;
	class FootSole* footSole;
	class ForwardGroundCheck* forwardDownGroundCheck;
	class ForwardGroundCheck* forwardGroundCheck;


	static const float GroundCheckPos;
	static const float NockBackPower;
	Vector3 forceVector;
	void NockBack();
	EnemyMoveDirection moveDirection;
};



