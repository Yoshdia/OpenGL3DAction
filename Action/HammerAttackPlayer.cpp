#include "HammerAttackPlayer.h"
#include "HammerWeapon.h"


HammerAttackPlayer::HammerAttackPlayer(const float& _number):
	AttackBase(),
	number(_number)
{
	if (_number>1.0f)
	{
		canNotActionTime = 40;
		waitTimeForNextAttack = 10;
	}
	else
	{

	canNotActionTime = 40;
	waitTimeForNextAttack = 60;
	}
}


HammerAttackPlayer::~HammerAttackPlayer()
{
}

void HammerAttackPlayer::Attack(const Vector3 & _ownerPosition, const float & _direction)
{
	new HammerWeapon(_ownerPosition,number,_direction,30);
}
