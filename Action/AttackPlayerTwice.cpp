#include "AttackPlayerTwice.h"
#include "SDL.h"
#include "WeaponRotationAnimationPlayer.h"

AttackPlayerTwice::AttackPlayerTwice():
	AttackBase()
{
	canNotActionTime = 20;
	waitTimeForNextAttack = 30;
}


AttackPlayerTwice::~AttackPlayerTwice()
{
}

void AttackPlayerTwice::Attack(const Vector3& _ownerPosition)
{
	new WeaponRotationAnimationPlayer(_ownerPosition, 1);
}
