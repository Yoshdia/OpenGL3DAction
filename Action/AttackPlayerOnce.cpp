#include "AttackPlayerOnce.h"
#include"SDL.h"
#include "WeaponRotationAnimationPlayer.h"

AttackPlayerOnce::AttackPlayerOnce() :
	AttackBase()
{
	canNotActionTime = 20;
	waitTimeForNextAttack = 50;
}


AttackPlayerOnce::~AttackPlayerOnce()
{
}

void AttackPlayerOnce::Attack(const Vector3& _ownerPosition,const float& _direction)
{
	new WeaponRotationAnimationPlayer(_ownerPosition, _direction,0,120,0);
}
