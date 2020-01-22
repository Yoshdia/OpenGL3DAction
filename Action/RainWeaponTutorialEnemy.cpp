#include "RainWeaponTutorialEnemy.h"
#include "RainEnemyWeapon.h"

const int RainWeaponTutorialEnemy::Interval = 40;

RainWeaponTutorialEnemy::RainWeaponTutorialEnemy(const Vector3 & _pos)
{
	SetPosition(_pos);
	interval = Interval;
}

RainWeaponTutorialEnemy::~RainWeaponTutorialEnemy()
{
}

void RainWeaponTutorialEnemy::UpdateGameObject(float _deltaTime)
{
	if (interval <= 0)
	{
		interval = Interval;
		new RainEnemyWeapon(position);
	}
	else
	{
		interval--;
	}
}

