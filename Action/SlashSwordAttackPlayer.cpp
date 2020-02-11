#include "SlashSwordAttackPlayer.h"
#include "SlashSwordWeapon.h"
#include "ShotSwordWeapon.h"

SlashSwordAttackPlayer::SlashSwordAttackPlayer(const float& _number) :
	AttackBase(),
	number(_number)
{
	if (_number > 2)
	{
		canNotActionTime = 50;
		waitTimeForNextAttack = 10;
	}
	else
	{

	canNotActionTime = 30;
	waitTimeForNextAttack = 50;
	}
}

SlashSwordAttackPlayer::~SlashSwordAttackPlayer()
{
}

void SlashSwordAttackPlayer::Attack(const Vector3& _ownerPosition, const float& _direction)
{
	if (number < 3)
	{
		new SlashSwordWeapon(_ownerPosition, number, _direction, 30);
	}
	else
	{
		new ShotSwordWeapon(_ownerPosition, _direction, 50);
	}
}
