#pragma once
#include "GameObject.h"


class EnemyBase abstract:
	public GameObject
{
public:
	EnemyBase(const std::string& meshName);
	~EnemyBase();

private:
	void OnTriggerStay(ColliderComponent* colliderPair) ;

};

