#include "RangeAttackPlayer.h"
#include "ThrowWeapon.h"



RangeAttackPlayer::RangeAttackPlayer()
{
	canNotActionTime = 50;
	waitTimeForNextAttack = 80;
}


RangeAttackPlayer::~RangeAttackPlayer()
{
}

void RangeAttackPlayer::Attack(const Vector3 & _ownerPosition)
{
	new ThrowWeapon(_ownerPosition);
}
