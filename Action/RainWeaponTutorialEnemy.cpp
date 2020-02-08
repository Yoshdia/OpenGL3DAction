#include "RainWeaponTutorialEnemy.h"
#include "RainEnemyWeapon.h"
#include "ColliderComponent.h"

const int RainWeaponTutorialEnemy::Interval = 40;
/*
@param _pos ç¿ïW
*/
RainWeaponTutorialEnemy::RainWeaponTutorialEnemy(const Vector3 & _pos)
{
	SetPosition(_pos);
	interval = Interval;
	ColliderComponent* collider = new ColliderComponent(this, 100, Vector3(1, 1, 1) ,myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
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

