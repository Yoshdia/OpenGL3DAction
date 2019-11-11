#pragma once
#include "GameObject.h"
#include <string>

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

	static const float NockBackPower;
	Vector3 forceVector;
	void NockBack();
};

