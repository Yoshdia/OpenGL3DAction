#pragma once
#include "GameObject.h"


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
};

