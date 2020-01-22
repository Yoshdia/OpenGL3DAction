#pragma once
#include "GameObject.h"
class RainEnemyWeapon :
	public GameObject
{
public:
	RainEnemyWeapon(const Vector3& _pos);
	~RainEnemyWeapon();

	void UpdateGameObject(float _deltaTime)override;
private:
	int activeCount;
};

