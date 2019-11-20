#include "AttackPlayerOnce.h"
#include"SDL.h"
#include "WeaponRotationAnimationPlayer.h"

AttackPlayerOnce::AttackPlayerOnce() :
	AttackBase()
{
	canNotActionTime = 20;
	waitTimeForNextAttack = 30;
}


AttackPlayerOnce::~AttackPlayerOnce()
{
}

void AttackPlayerOnce::Attack(const Vector3& _ownerPosition,const int& _direction)
{
	new WeaponRotationAnimationPlayer(_ownerPosition, _direction,0);
}
