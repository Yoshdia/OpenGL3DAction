#include "RangeAttackPlayer.h"
#include "ThrowWeapon.h"



RangeAttackPlayer::RangeAttackPlayer()
{
	canNotActionTime = 20;
	waitTimeForNextAttack = 40;
}


RangeAttackPlayer::~RangeAttackPlayer()
{
}

void RangeAttackPlayer::Attack(const Vector3 & _ownerPosition,const float& _direction)
{
	new ThrowWeapon(_ownerPosition, _direction,20);
}
