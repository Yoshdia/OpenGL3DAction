#pragma once
#include "GameObject.h"

class RainWeaponTutorialEnemy :
	public GameObject
{
public:
	RainWeaponTutorialEnemy(const Vector3& _pos);
	~RainWeaponTutorialEnemy();

	void UpdateGameObject(float _deltaTime)override;
private:
	int interval;
	static const int Interval;
};

